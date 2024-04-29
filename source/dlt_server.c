/**
 * \file dlt_server.h
 * \brief Header file for DLT server library
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "dlt/dlt_server.h"

#include "dlt_conf.h"

// --- Private variables

static bool g_is_started = false;

// --- Public functions

bool DLT_server_is_started()
{
    bool is_started = false;
    if (DLT_mutex_acquire() == true)
    {
        is_started = g_is_started;
        DLT_mutex_release();
    }
    return is_started;
}
