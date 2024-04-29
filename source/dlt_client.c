/**
 * \file dlt_client.c
 * \brief Header file for DLT client library
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "dlt/dlt_client.h"
#include "dlt/dlt_server.h"

// --- Private functions

static bool Dlt_client_parse_args(BUFS_t *buffer, uint32_t args_count, va_list args);

// --- Public functions

bool DLT_client_log(dlt_context_t *context, dlt_log_level_t log_level, uint32_t msg_id, uint16_t msg_len, uint32_t args_count, ...)
{
    bool logged = false;

    if ((context != NULL) && (DLT_server_is_started() == true))
    {
        if ((log_level != DLT_LOG_OFF) && (log_level <= DLT_context_get_log_level(context)))
        {
            DLT_Frame_t frame = {0};
            void *mem_block = NULL;

            DLT_Stat_report_global(DLT_STAT_GLOBAL_LOG_COUNT);

            frame.timestamp = Dlt_Client_get_timestamp();
            frame.log_level = log_level;
            frame.msg_counter = DLT_Context_increment_msg_counter(context);
            frame.msg_id = DLT_Client_offset_message_id(msg_id);

            mem_block = DLT_Mempool_alloc();
            if (mem_block != NULL)
            {
                /* parasoft-begin-suppress ALL "MD_DLT_StdArgStrategy" */
                va_list args = {NULL};
                va_start(args, args_count);

                BUFS_InitEmpty(&frame.payload, (uint8_t *)mem_block, DLT_MEMPOOL_BLOCK_SIZE);

                if (Dlt_client_parse_args(&frame.payload, args_count, args) == true)
                {
                    if (BUFS_GetUsedSize(&frame.payload) == msg_len)
                    {
                        if (DLT_Datalink_copy_log(context, &frame) == true)
                        {
                            logged = true;
                        }
                        else
                        {
                            DLT_Stat_report_error(DLT_STAT_ERROR_DATALINK_COPY);
                        }
                    }
                }
                va_end(args);
                /* parasoft-end-suppress ALL "MD_DLT_StdArgStrategy" */

                DLT_Mempool_free(mem_block);
            }
            else
            {
                DLT_Stat_report_error(DLT_STAT_ERROR_MEMPOOL_ALLOC);
            }
        }
    }
    return logged;
}

// --- Private functions

static bool Dlt_client_parse_args(BUFS_t *buffer, uint32_t args_count, va_list args)
{
    bool valid = true;
    while ((args_count > 0U) && (true == valid))
    {
        dlt_arg_type_t args_type = (dlt_arg_type_t)va_arg(args, uint32_t); /* dlt_arg_type_t pushed was promoted to uint32_t */
        switch (args_type)
        {
        case DLT_ARG_CSTRING:
        {
            /* We are in non verbose mode, the CSTRING is just ignored and will be added by the DLT viewer. */
        }
        break;
        case DLT_ARG_INT8:
        {
            int8_t value = (int8_t)va_arg(args, int32_t); /* int8_t pushed was promoted int32_t */
            BUFS_WriteUint8(buffer, (uint8_t)value);
        }
        break;
        case DLT_ARG_INT16:
        {
            int16_t value = (int16_t)va_arg(args, int32_t); /* int16_t pushed was promoted int32_t */
            BUFS_WriteUint16(buffer, (uint16_t)value);
        }
        break;
        case DLT_ARG_INT32:
        {
            int32_t value = (int32_t)va_arg(args, int32_t); /* int32_t pushed was promoted int32_t */
            BUFS_WriteUint32(buffer, (uint32_t)value);
        }
        break;
        case DLT_ARG_INT64:
        {
            int64_t value = (int64_t)va_arg(args, int64_t); /* int64_t pushed was promoted int64_t */
            BUFS_WriteUint64(buffer, (uint64_t)value);
        }
        break;
        case DLT_ARG_BOOL:
        {
            bool value = (bool)(va_arg(args, uint32_t)); /* boolean pushed was promoted to uint32_t */
            BUFS_WriteUint8(buffer, value);
        }
        break;
        case DLT_ARG_UINT8:
        {
            uint8_t value = (uint8_t)(va_arg(args, uint32_t)); /* uint8_t pushed was promoted to uint32_t */
            BUFS_WriteUint8(buffer, value);
        }
        break;
        case DLT_ARG_UINT16:
        {
            uint16_t value = (uint16_t)(va_arg(args, uint32_t)); /* uint16_t pushed was promoted to uint32_t */
            BUFS_WriteUint16(buffer, value);
        }
        break;
        case DLT_ARG_UINT32:
        {
            uint32_t value = (uint32_t)(va_arg(args, uint32_t));
            BUFS_WriteUint32(buffer, value);
        }
        break;
        case DLT_ARG_UINT64:
        {
            uint64_t value = (uint64_t)(va_arg(args, uint64_t));
            BUFS_WriteUint64(buffer, value);
        }
        break;
#ifdef DLT_WITH_FLOAT
        case DLT_ARG_FLOAT32:
        {
            uint32_t l_data = (uint32_t)(va_arg(args, double)); /* float32 pushed was promoted to double */
            dlt_write_buffer(mem, (const void *)&l_data, FOUR_BYTE);
        }
        break;
        case DLT_ARG_FLOAT64:
        {
            uint64_t l_data = (uint64_t)(va_arg(args, double)); /* float64 pushed was promoted to double */
            dlt_write_buffer(mem, (const void *)&l_data, EIGHT_BYTE);
        }
#endif /* DLT_WITH_FLOAT */
        case DLT_ARG_RAW:
        {
            const uint8_t *data = (const uint8_t *)va_arg(args, void *);
            uint16_t len = (uint16_t)va_arg(args, uint32_t); /* uint16_t pushed was promoted to uint32_t */
            BUFS_WriteUint16(buffer, len);
            BUFS_WriteRaw(buffer, data, len);
        }
        break;
        case DLT_ARG_STRING:
        {
            const char *str = (const char *)va_arg(args, void *);
            uint16_t len = (uint16_t)va_arg(args, uint32_t); /* uint16_t pushed was promoted to uint32_t */
            BUFS_WriteUint16(buffer, len);
            BUFS_WriteString(buffer, str, len);
        }
        break;
        case DLT_ARG_NONE:
        {
            valid = false;
        }
        break;
        }
        args_count--;
    }
    return valid;
}
