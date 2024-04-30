/**
 * \file dlt_frame.h
 * \brief DLT frame
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdint.h>

#include "buffer/bufs.h"

#include "dlt/dlt_context.h"

// --- Public types

typedef struct
{
    uint32_t timestamp;
    uint32_t msg_id;
    BUFS_t payload;
    uint8_t msg_counter;
    dlt_log_level_t log_level;
} DLT_Frame_t;
