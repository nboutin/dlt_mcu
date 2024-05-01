/**
 * \file   dlt_datalink.c
 * \brief  DLT Datalink
 * \date   2024-04
 * \author Nicolas BOUTIN
 */

#include "dlt_datalink.h"

// --- Public functions

bool DLT_datalink_init()
{
  bool init = true;
#ifdef DLT_WITH_SERIAL
  init &= DLT_datalink_serial_init();
#endif
  return init;
}

bool DLT_datalink_copy_log(dlt_context_t* context, DLT_Frame_t* frame)
{
  bool copied = false;

  if (frame == NULL)
  {
    return copied;
  }

#ifdef DLT_WITH_SERIAL
  BUF_ResetReadIndex(&frame->payload);
  copied |= DLT_datalink_serial_copy_log(context, frame);
#endif

  (void) context;
  (void) frame;
  return copied;
}

void DLT_datalink_transmit()
{
#ifdef DLT_WITH_SERIAL
  DLT_datalink_serial_transmit();
#endif
}
