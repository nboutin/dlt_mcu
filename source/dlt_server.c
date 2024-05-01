/**
 * \file dlt_server.h
 * \brief Header file for DLT server library
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "dlt/dlt_server.h"

#include "dlt_conf.h"
#include "dlt_datalink.h"

// --- Private variables

static bool g_is_started = false;

// --- Public functions

void DLT_server_init()
{
  bool start = true;

  if (DLT_mutex_init() == false)
  {
    start = false;
  }

  if (DLT_mempool_init() == false)
  {
    start = false;
  }

  if (DLT_datalink_init() == false)
  {
    start = false;
  }

  g_is_started = start;
}

void DLT_server_start()
{
  if (DLT_mutex_acquire() == true)
  {
    g_is_started = true;
    DLT_mutex_release();
  }
}

void DLT_server_stop()
{
  if (DLT_mutex_acquire() == true)
  {
    g_is_started = false;
    DLT_mutex_release();
  }
}

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

void DLT_Server_run()
{
  if (DLT_server_is_started() == true)
  {
    DLT_datalink_transmit();
  }
}
