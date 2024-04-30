/**
 * \file dlt_frame.c
 * \brief DLT frame_rbuf
 * \date 2024-04
 * \author Nicolas Boutin
 */

#include "dlt_frame.h"

// --- Private functions

static uint8_t Dlt_frame_make_header_type();

// --- Public functions

bool DLT_frame_make_header(RBUFS_t *frame_rbuf, uint8_t msg_counter, uint32_t timestamp, uint32_t msg_id, uint16_t msg_len)
{
    bool written = true;
    uint8_t type = 0U;

    /* Header Type */
    type = Dlt_frame_make_header_type();
    written &= RBUFS_WriteUint8(frame_rbuf, type);

    /* counter context */
    written &= RBUFS_WriteUint8(frame_rbuf, msg_counter);

    /* length 1 && 2 */
    written &= RBUFS_WriteUint16(frame_rbuf, msg_len);

    /* ENAF */
#ifdef DLT_WITH_ECU_ID
    written &= DLT_Client_get_ecu_id(frame_rbuf);
#endif

    /* timestamp */
    written &= RBUFS_WriteUint32(frame_rbuf, timestamp);

    /* message id */
    written &= RBUFS_WriteUint32(frame_rbuf, msg_id);
    return written;
}

// --- Private functions

static uint8_t Dlt_frame_make_header_type()
{
    return ((uint8_t)(((uint32_t)DLT_HTYP_PROTOCOL_VERSION1)
#ifdef DLT_WITH_ECU_ID
                      | ((uint32_t)DLT_HTYP_WEID)
#endif
                      | ((uint32_t)DLT_HTYP_WTMS) | ((uint32_t)DLT_HTYP_MSBF)));
}
