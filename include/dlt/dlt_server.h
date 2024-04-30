/**
 * \file dlt_server.h
 * \brief Header file for DLT server library
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#include <stdbool.h>

// --- Public functions

void DLT_server_init();

void DLT_server_start();

void DLT_server_stop();

bool DLT_server_is_started();

void DLT_Server_run();
