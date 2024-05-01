/**
 * \file dlt_uart.h
 * \brief DLT UART interface
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>

#include "buffer/buffer.h"

// --- Public types

typedef enum
{
    DLT_UART_STATUS_TX_BUSY = 1,
} DLT_uart_status_t;

typedef enum
{
    DLT_UART_EVENT_TRANSMIT_COMPLETE = 1,
} DLT_uart_event_t;

// --- Public functions

DLT_uart_status_t DLT_uart_get_status();

bool DLT_uart_transmit(BUF_t *tx_buffer);

extern void DLT_uart_event_callback(DLT_uart_event_t event);
