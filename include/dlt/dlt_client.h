/**
 * \file dlt_client.h
 * \brief Header file for DLT client library
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "dlt/dlt_context.h"
#include "dlt/private/dlt_client_private.h"

// --- Public types

#define DLT_DECLARE_CONTEXT(context) dlt_context_t context
#define DLT_IMPORT_CONTEXT(context)  extern dlt_context_t context
#define DLT_EXPORT_CONTEXT(context)  extern dlt_context_t context

// --- Public functions

/**
 * \brief DLT register application
 * \details Used by dlt-parser
 */
#define DLT_REGISTER_APP(application_name, application_description)

/**
 * \brief Register context
 * \param[in] context Context to register
 * \param[in] context_name Context name
 * \param[in] context_description Context description
 * \code {.c}
 * DLT_DECLARE_CONTEXT(context);
 * DLT_REGISTER_CONTEXT(context, "application name", "context name", "context description");
 * \endcode
 */
#define DLT_REGISTER_CONTEXT(context, application_name, context_name, context_description)                             \
  DLT_context_register(&(context), (context_name), (context_description))

/**
 * \brief Set log level
 * \param[in] context Context to set log level
 * \param[in] log_level Log level
 */
#define DLT_CONTEXT_SET_LOG_LEVEL(context, log_level) DLT_context_set_log_level(&(context), (log_level))

/**
 * DLT argument formatter type
 */
#define DLT_BOOL(BOOL_VAR) LEN_DLT_BOOL, DLT_ARG_BOOL, (BOOL_VAR)

#define DLT_UINT8(INT_VAR)  LEN_DLT_UINT8, DLT_ARG_UINT8, (uint8_t) (INT_VAR)
#define DLT_UINT16(INT_VAR) LEN_DLT_UINT16, DLT_ARG_UINT16, (uint16_t) (INT_VAR)
#define DLT_UINT32(INT_VAR) LEN_DLT_UINT32, DLT_ARG_UINT32, (uint32_t) (INT_VAR)
#define DLT_UINT64(INT_VAR) LEN_DLT_UINT64, DLT_ARG_UINT64, (uint64_t) (INT_VAR)

#define DLT_INT8(INT_VAR)  LEN_DLT_INT8, DLT_ARG_INT8, (int8_t) (INT_VAR)
#define DLT_INT16(INT_VAR) LEN_DLT_INT16, DLT_ARG_INT16, (int16_t) (INT_VAR)
#define DLT_INT32(INT_VAR) LEN_DLT_INT32, DLT_ARG_INT32, (int32_t) (INT_VAR)
#define DLT_INT64(INT_VAR) LEN_DLT_INT64, DLT_ARG_INT64, (int64_t) (INT_VAR)

#ifdef DLT_WITH_FLOAT
#define DLT_FLOAT32(FLOAT32_VAR) LEN_DLT_FLOAT32, DLT_ARG_FLOAT32, (FLOAT32_VAR)
#define DLT_FLOAT64(FLOAT64_VAR)   LEN_DLT_FLOAT64, DLT_ARG_FLOAT64, (FLOAT64_VAR)
#endif

#define DLT_RAW(BUF, LEN) LEN_DLT_RAW((BUF), (LEN)), DLT_ARG_RAW, (const void*) (BUF), (uint16_t) (LEN)

#define DLT_CSTRING(TEXT) LEN_DLT_CSTRING, DLT_ARG_CSTRING
#define DLT_STRING(TEXT)  LEN_DLT_STRING(TEXT), DLT_ARG_STRING, (TEXT), (uint16_t) (strlen(TEXT) + 1U)

/**
 * \brief Log a DLT message with 1 argument
 * \param[in] context Context to log
 * \param[in] log_level Log level
 * \param[in] msg_id Message ID
 * \param[in] args1 Argument 1
 * \return true if log is taken into account by the module otherwise return false
 */
#define DLT_LOG_ID1(context, log_level, msg_id, args1)                                                                 \
  DLT_client_log(&(context), (log_level), (uint32_t) (msg_id), DLT_LEN(args1), (uint8_t) 1, DLT_CHK(args1))

/**
 * \brief Log a DLT message with 2 arguments
 */
#define DLT_LOG_ID2(context, log_level, msg_id, args1, args2)                                                          \
  DLT_client_log(&(context),                                                                                           \
                 (log_level),                                                                                          \
                 (uint32_t) (msg_id),                                                                                  \
                 DLT_LEN(args1) + DLT_LEN(args2),                                                                      \
                 (uint8_t) 2,                                                                                          \
                 DLT_CHK(args1),                                                                                       \
                 DLT_CHK(args2))

#define DLT_LOG_ID3(context, log_level, msg_id, args1, args2, args3)                                                   \
  DLT_client_log(&(context),                                                                                           \
                 (log_level),                                                                                          \
                 (uint32_t) (msg_id),                                                                                  \
                 DLT_LEN(args1) + DLT_LEN(args2) + DLT_LEN(args3),                                                     \
                 (uint8_t) 3,                                                                                          \
                 DLT_CHK(args1),                                                                                       \
                 DLT_CHK(args2),                                                                                       \
                 DLT_CHK(args3))

#define DLT_LOG_ID4(context, log_level, msg_id, args1, args2, args3, args4)                                            \
  DLT_client_log(&(context),                                                                                           \
                 (log_level),                                                                                          \
                 (uint32_t) (msg_id),                                                                                  \
                 DLT_LEN(args1) + DLT_LEN(args2) + DLT_LEN(args3) + DLT_LEN(args4),                                    \
                 (uint8_t) 4,                                                                                          \
                 DLT_CHK(args1),                                                                                       \
                 DLT_CHK(args2),                                                                                       \
                 DLT_CHK(args3),                                                                                       \
                 DLT_CHK(args4))

#define DLT_LOG_ID5(context, log_level, msg_id, args1, args2, args3, args4, args5)                                     \
  DLT_client_log(&(context),                                                                                           \
                 (log_level),                                                                                          \
                 (uint32_t) (msg_id),                                                                                  \
                 DLT_LEN(args1) + DLT_LEN(args2) + DLT_LEN(args3) + DLT_LEN(args4) + DLT_LEN(args5),                   \
                 (uint8_t) 5,                                                                                          \
                 DLT_CHK(args1),                                                                                       \
                 DLT_CHK(args2),                                                                                       \
                 DLT_CHK(args3),                                                                                       \
                 DLT_CHK(args4),                                                                                       \
                 DLT_CHK(args5))

/**
 * \brief Log a DLT message
 * \param[in] context Context to log
 * \param[in] log_level Log level
 * \param[in] msg_id Message ID
 * \param[in] msg_len Message length
 * \param[in] args_count Number of arguments
 * \param[in] ... Arguments
 * \return true if message is logged, false otherwise
 */
bool DLT_client_log(dlt_context_t* context,
                    dlt_log_level_t log_level,
                    uint32_t msg_id,
                    uint16_t msg_len,
                    uint32_t args_count,
                    ...);
