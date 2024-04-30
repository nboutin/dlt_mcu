/**
 * \file dlt_conf.c
 * \brief Header file for DLT configuration
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include <stddef.h>
#include <stdint.h>

#include "dlt_conf.h"

// --- Private variables

static uint8_t g_mempool[DLT_MEMPOOL_BLOCK_SIZE];
static uint8_t g_mempool_block_used = 0U;

// --- Public functions

bool DLT_mempool_init() { return true; }

void *DLT_mempool_alloc()
{
    void *block = NULL;
    if (g_mempool_block_used < DLT_MEMPOOL_BLOCK_COUNT)
    {
        block = g_mempool;
        g_mempool_block_used++;
    }
    return block;
}

void DLT_mempool_free(void *block)
{
    if (block != NULL)
    {
        g_mempool_block_used--;
    }
}
