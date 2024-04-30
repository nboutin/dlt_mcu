/**
 * \file dlt_datalink_serial.c
 * \brief Datalink layer for DLT over serial
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "buffer/bufs.h"
#include "ring_buffer/rbufs.h"

#include "dlt_conf.h"
#include "dlt_protocol.h"
#include "dlt_uart.h"

#include "dlt_datalink_serial.h"

// --- Private constants

#define DLT_SERIAL_HEADER_SIZE 4U
#define DLT_SERIAL_HEADER "DLS\1"

// --- Private variables

static uint8_t g_tx_data[DLT_SERIAL_TX_BUFFER_SIZE];
static RBUFS_t g_tx_buffer;

static uint8_t g_tx_chunk_data[DLT_SERIAL_TX_CHUNK_SIZE_MAX];
static BUFS_t g_tx_chunk_buffer;

static uint16_t g_last_transfer_size;

// --- Public functions

bool DLT_datalink_serial_init()
{
    RBUFS_InitEmpty(&g_tx_data, g_tx_buffer, DLT_SERIAL_TX_BUFFER_SIZE);
    BUFS_InitEmpty(&g_tx_chunk_buffer, g_tx_chunk_data, DLT_SERIAL_TX_CHUNK_SIZE_MAX);

    g_last_transfer_size = 0U;
    return true;
}

bool DLT_datalink_serial_copy_log(dlt_context_t *context, DLT_Frame_t *frame)
{
    bool copied = false;

    if ((frame == NULL) || (context == NULL))
    {
        return copied;
    }

    // Serial Datalink filter on context log level
    if ((frame->log_level > DLT_Context_get_log_level(context)) || (frame->log_level == DLT_LOG_OFF))
    {
        // DLT_Stat_report_datalink(DLT_STAT_DATALINK_SERIAL, DLT_STAT_DATALINK_SKIPPED, 1);
        copied = true; // skip log
    }
    else
    {
        // Protect g_tx_buffer
        if (DLT_mutex_acquire() == true)
        {
            // Check for frame size max and enough free space in tx buffer
            uint16_t frame_size = DLT_SERIAL_HEADER_SIZE + DLT_HEADER_SIZE + BUFS_GetUsedSize(&frame->payload);
            if ((frame_size < DLT_FRAME_SIZE_MAX) && (RBUFS_GetFreeSize(&g_tx_buffer) >= frame_size))
            {
                copied = true;

                // Serial header (DLS1)
                copied &= RBUFS_WriteString(&g_tx_buffer, DLT_SERIAL_HEADER, DLT_SERIAL_HEADER_SIZE);
                // Frame Header
                copied &= DLT_frame_make_header(&g_tx_buffer,
                                                frame->msg_counter,
                                                frame->timestamp,
                                                frame->msg_id,
                                                DLT_HEADER_SIZE + BUFS_GetUsedSize(&frame->payload));
                // Payload
                copied &= RBUFS_WriteCopy(&g_tx_buffer, &frame->payload, BUFS_GetToReadCount(&frame->payload));

                if (copied == true)
                {
                    // DLT_Stat_report_datalink(DLT_STAT_DATALINK_SERIAL, DLT_STAT_DATALINK_COPIED, frame_size);
                }
            }
            else
            {
                // DLT_Stat_report_error(DLT_STAT_ERROR_SERIAL_FULL);
            }

            // DLT_Stat_report_usage(DLT_STAT_DATALINK_SERIAL, RBUFS_GetUsedSize(&g_tx_buffer), DLT_SERIAL_TX_BUFFER_SIZE);

            DLT_mutex_release();
        }
    }
    return copied;
}

void DLT_datalink_serial_transmit()
{
    DLT_uart_status_t dlt_uart_status = 0U;

    if (DLT_mutex_acquire() == true)
    {
        dlt_uart_status = DLT_uart_get_status();

        if ((dlt_uart_status & DLT_UART_STATUS_TX_BUSY) != DLT_UART_STATUS_TX_BUSY)
        {
            BUFS_Reset(&g_tx_chunk_buffer);

            g_last_transfer_size = RBUFS_ReadCopyRaw(&g_tx_chunk_buffer, &g_serial_tx_buffer, DLT_SERIAL_TX_CHUNK_SIZE_MAX);

            if (g_last_transfer_size > 0U)
            {
                if (DLT_uart_transmit(&g_tx_chunk_buffer) == false)
                {
                    g_last_transfer_size = 0U;
                }
                else
                {
                    // DLT_Stat_report_datalink(DLT_STAT_DATALINK_SERIAL, DLT_STAT_DATALINK_TRANSMITTED, g_last_transfer_size);
                }
            }
        }
        DLT_mutex_release();
    }
}

void DLT_uart_event_callback(DLT_uart_event_t event)
{
    if ((event & DLT_UART_EVENT_TRANSMIT_COMPLETE) == DLT_UART_EVENT_TRANSMIT_COMPLETE)
    {
        g_last_transfer_size = 0U;
    }
}
