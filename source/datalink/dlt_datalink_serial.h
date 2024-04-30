/**
 * \file dlt_datalink_serial.h
 * \brief Datalink layer for DLT over serial
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>

#include "dlt/dlt_context.h"
#include "dlt_frame.h"

// --- Public functions

bool DLT_datalink_serial_init();

bool DLT_datalink_serial_copy_log(dlt_context_t *context, DLT_Frame_t *frame);

void DLT_datalink_serial_transmit();
