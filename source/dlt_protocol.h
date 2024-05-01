/**
 * \file dlt_protocol.h
 * \brief DLT protocol
 * \date 2024-04
 * \author Nicolas Boutin
 */

#pragma once

#ifdef DLT_WITH_ECU_ID
#define DLT_SIZE_HEADER_NO_OVERHEAD 16U
#define DLT_HEADER_SIZE             DLT_SIZE_HEADER_NO_OVERHEAD
#else
#define DLT_SIZE_HEADER_NO_ECU_ID 12U
#define DLT_HEADER_SIZE           DLT_SIZE_HEADER_NO_ECU_ID
#endif

/**
 * \name Definitions of the htyp parameter in standard header.
 */
#define DLT_HTYP_UEH  0x01U /**< use extended header */
#define DLT_HTYP_MSBF 0x02U /**< MSB first */
#define DLT_HTYP_WEID 0x04U /**< with ECU ID */
#define DLT_HTYP_WSID 0x08U /**< with session ID */
#define DLT_HTYP_WTMS 0x10U /**< with timestamp */
#define DLT_HTYP_VERS 0xE0U /**< version number, 0x1 */

#define DLT_HTYP_PROTOCOL_VERSION1 0x20U
