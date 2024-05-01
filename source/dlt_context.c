/**
 * \file dlt_context.c
 * \brief Header file for DLT context
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "dlt/dlt_context.h"
#include "dlt_conf.h"

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
