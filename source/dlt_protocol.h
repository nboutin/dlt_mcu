/**
 * \file dlt_protocol.h
 * \brief DLT protocol
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#ifdef DLT_WITH_ECU_ID
#define DLT_SIZE_HEADER_NO_OVERHEAD 16U
#define DLT_HEADER_SIZE DLT_SIZE_HEADER_NO_OVERHEAD
#else
#define DLT_SIZE_HEADER_NO_ECU_ID 12U
#define DLT_HEADER_SIZE DLT_SIZE_HEADER_NO_ECU_ID
#endif
