/**
 * \file dlt_conf.h
 * \brief Header file for DLT configuration
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>

#include "dlt/dlt_context.h"

// --- Public constants

#define DLT_ECU_ID "ECU1"
#define DLT_LOG_LEVEL_DEFAULT DLT_LOG_DEBUG

#define DLT_FRAME_SIZE_MAX 128U

#define DLT_BOOTLOADER_BOOT_TIME_OFFSET_100us 1000U // TODO measure the real value

#define DLT_MEMPOOL_BLOCK_SIZE 128U
#define DLT_MEMPOOL_BLOCK_COUNT 1U

#define DLT_SERIAL_TX_BUFFER_SIZE 512U
#define DLT_SERIAL_TX_CHUNK_SIZE_MAX 100U

// --- Public functions

#define DLT_get_system_time_100us() (10) // (HAL_GetTick() * 10U)

static inline bool DLT_mutex_init() { return true; }
static inline bool DLT_mutex_acquire() { return true; }
static inline bool DLT_mutex_release() { return true; }

bool DLT_mempool_init();
void *DLT_mempool_alloc();
void DLT_mempool_free(void *block);
