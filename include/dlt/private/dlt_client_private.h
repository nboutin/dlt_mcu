/**
 * \file dlt_client_private.h
 * \brief Header file for DLT client library
 * \date 2024-04
 * \author Nicolas Boutin
 */

// --- Public constant

#define DLT_MAX_RAW_SIZE    128U
#define DLT_MAX_STRING_SIZE 128U

// --- Public functions

typedef enum {
  DLT_ARG_CSTRING = 0x00U,
  DLT_ARG_STRING  = 0x01U,
  DLT_ARG_INT8    = 0x02U,
  DLT_ARG_INT16   = 0x03U,
  DLT_ARG_INT32   = 0x04U,
  DLT_ARG_INT64   = 0x05U,
  DLT_ARG_UINT8   = 0x06U,
  DLT_ARG_UINT16  = 0x07U,
  DLT_ARG_UINT32  = 0x08U,
  DLT_ARG_UINT64  = 0x09U,
#ifdef DLT_WITH_FLOAT
  DLT_ARG_FLOAT32 = 0x0AU,
  DLT_ARG_FLOAT64 = 0x0BU,
#endif
  DLT_ARG_RAW  = 0x0CU,
  DLT_ARG_BOOL = 0x0DU,
  DLT_ARG_NONE = 0xFFU
} dlt_arg_type_t;

/**
 * DLT argument formatter length
 */
#define DLT_LEN(FIRST_ARG_DLT_TYPE, ...) (FIRST_ARG_DLT_TYPE)

#define LEN_DLT_BOOL    1U
#define LEN_DLT_UINT8   1U
#define LEN_DLT_UINT16  2U
#define LEN_DLT_UINT32  4U
#define LEN_DLT_UINT64  8U
#define LEN_DLT_INT8    1U
#define LEN_DLT_INT16   2U
#define LEN_DLT_INT32   4U
#define LEN_DLT_INT64   8U
#define LEN_DLT_FLOAT32 4U
#define LEN_DLT_FLOAT64 8U
#define LEN_DLT_CSTRING 0U
#define LEN_DLT_STRING(TEXT)                                                                                           \
  2U + (((strlen(TEXT) + 1U) > DLT_MAX_STRING_SIZE) ? DLT_MAX_STRING_SIZE : ((uint16_t) strlen(TEXT) + 1U))
#define LEN_DLT_RAW(BUF, LEN) 2U + (((LEN) > DLT_MAX_RAW_SIZE) ? DLT_MAX_RAW_SIZE : (LEN))

#define DLT_CHK(REMOVE_FIRST_ARG, ...) __VA_ARGS__
