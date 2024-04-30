/**
 * \file dlt_context.h
 * \brief Header file for DLT context
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdint.h>

// --- Public constant

#define DLT_NAME_LENGTH 4U /*!< Maximum length of DLT application and context names */

// --- Public types

typedef enum
{
    DLT_LOG_OFF = 0x00,    /*!< Log level off */
    DLT_LOG_FATAL = 0x01,  /*!< fatal system error */
    DLT_LOG_ERROR = 0x02,  /*!< error with impact to correct functionality */
    DLT_LOG_WARN = 0x03,   /*!< warning, correct behaviour could not be ensured */
    DLT_LOG_INFO = 0x04,   /*!< informational */
    DLT_LOG_DEBUG = 0x05,  /*!< debug */
    DLT_LOG_VERBOSE = 0x06 /*!< highest grade of information */
} dlt_log_level_t;

/**
 * \brief DLT application name type
 */
typedef char dlt_app_name_t[DLT_NAME_LENGTH];

/**
 * \brief DLT context name type
 */
typedef char dlt_ctx_name_t[DLT_NAME_LENGTH];

/**
 * \brief DLT context type
 * \warning Do not use directly, use DLT_CONTEXT macro instead
 * \details Must be read/write under OS protected section (mutex)
 */
typedef struct
{
    dlt_ctx_name_t ctx_name;   /*!< context name */
    uint8_t msg_counter;       /*!< message counter */
    dlt_log_level_t log_level; /*!< log level */
} dlt_context_t;

// --- Public functions

dlt_log_level_t DLT_context_get_log_level(dlt_context_t *context);

uint8_t DLT_context_increment_msg_counter(dlt_context_t *context);
