/**
 * \file dlt_context.c
 * \brief Header file for DLT context
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include <string.h>

#include "dlt_conf.h"
#include "dlt_stdlib.h"

#include "dlt/dlt_context.h"

// --- Private functions

static void dlt_context_set_id(dlt_context_t* context, const dlt_ctx_name_t ctx_name);

// --- Public functions

void DLT_context_register(dlt_context_t* context, const dlt_ctx_name_t ctx_name, const char* description)
{
  if ((NULL != context) && (NULL != ctx_name) && (NULL != description))
  {
    if (DLT_mutex_acquire() == true)
    {
      // Double register protection: by default context log level value is 0
      dlt_log_level_t log_level = DLT_LOG_LEVEL_DEFAULT;
      if (context->log_level != log_level)
      {
        dlt_context_set_id(context, ctx_name);
        context->msg_counter = 255U;
        context->log_level   = log_level;
      }
    }
    DLT_mutex_release();
  }
}

void DLT_context_set_log_level(dlt_context_t* context, dlt_log_level_t log_level)
{
  if (NULL != context)
  {
    if (DLT_mutex_acquire() == true)
    {
      if (log_level <= DLT_LOG_VERBOSE)
      {
        context->log_level = log_level;
      }
      else
      {
        context->log_level = DLT_LOG_LEVEL_DEFAULT;
      }
      DLT_mutex_release();
    }
  }
}

dlt_log_level_t DLT_context_get_log_level(dlt_context_t* context)
{
  dlt_log_level_t log_level = DLT_LOG_OFF;

  if (context != NULL)
  {
    DLT_mutex_acquire();
    log_level = context->log_level;
    DLT_mutex_release();
  }
  return log_level;
}

uint8_t DLT_context_increment_msg_counter(dlt_context_t* context)
{
  uint8_t msg_counter = 0;

  if ((context != NULL) && (DLT_mutex_acquire() == true))
  {
    context->msg_counter++;
    msg_counter = context->msg_counter;
    DLT_mutex_release();
  }
  return msg_counter;
}

// --- Private functions

/**
 * \brief Set the context id
 * \details If too long then cut it, if too short then fill with '_' until ctx_id_t size
 */
static void dlt_context_set_id(dlt_context_t* context, const dlt_ctx_name_t ctx_name)
{
  if (context != NULL)
  {
    uint8_t to_copy = (uint8_t) DLT_min(sizeof(context->ctx_name), strlen(ctx_name));
    memset(context->ctx_name, '_', sizeof(context->ctx_name));
    memcpy(context->ctx_name, ctx_name, to_copy);
  }
}
