/**
 * \file   dlt_datalink.h
 * \brief  DLT Datalink
 * \date   2024-04
 * \author Nicolas BOUTIN
 */

#pragma once

#include <stdbool.h>

#include "dlt/dlt_context.h"
#include "dlt_frame.h"

// --- Public functions

bool DLT_datalink_init();

bool DLT_datalink_copy_log(dlt_context_t* context, DLT_Frame_t* frame);

void DLT_datalink_transmit();
