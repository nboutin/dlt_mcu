/**
 * \file dlt_conf.h
 * \brief Header file for DLT configuration
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>

// --- Public constants

#define DLT_BOOTLOADER_BOOT_TIME_OFFSET_100us 1000U // TODO measure the real value

#define DLT_MEMPOOL_BLOCK_SIZE 128U
#define DLT_MEMPOOL_BLOCK_COUNT 1U

// --- Public functions

#define DLT_get_system_time_100us() (HAL_GetTick() * 10U)

bool DLT_mutex_init() { return true; }
bool DLT_mutex_acquire() { return true; }
bool DLT_mutex_release() { return true; }

bool DLT_mempool_init();
void *DLT_mempool_alloc();
void DLT_Mempool_free(void *block);
