
#include <cstdint>
#include <iostream>

#include "mock.hpp"

#include "matcher.h"

extern "C" {
#include "apxd.h"
#include "dltm.h"

#include "dlt_client_config.h"
#include "dlt_datalink.h"

extern uint32_t Dlt_Client_get_timestamp(void);
}

static const uint32_t DRIVER_MSG_ID_OFFSET   = 28000U;
static const uint32_t MID_MSG_ID_OFFSET      = 32000U;
static const uint32_t CODRIVER_MSG_ID_OFFSET = 36000U;

DECLARE_MOCKABLE(DLTM_EventDlt, 4);
DECLARE_MOCKABLE(APXD_GetPhudPosition, 0);

DECLARE_MOCKABLE(DLT_Datalink_copy_log, 2);
DECLARE_MOCKABLE(DLT_Client_offset_message_id, 1);
DECLARE_MOCKABLE(Dlt_Client_get_timestamp, 0);

/**
 * Include sources files here to share mockable declarations
 */
#include "it_dlt_client.cpp"
#include "it_dlt_gdcn.cpp"
#include "it_dlt_serial.cpp"
#include "it_dlt_server.cpp"
