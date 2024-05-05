//! \file it_dlt_serial.cpp
//! \brief DLT integration tests
//! \date  2023-10
//! \author Nicolas Boutin

#include "mock.hpp"

#include "it_dlt_helper.h"
#include "matcher.h"

extern "C" {
#include "scid.h"

#include "dlt_client.h"
#include "dlt_datalink.h"
#include "dlt_server.h"
}

DECLARE_MOCKABLE(SCID_GetStatus, 0);
DECLARE_MOCKABLE(SCID_Transmit, 2);

using namespace testing;
using namespace std;

class DLT_IT_Serial : public ::testing::Test
{
protected:
  void SetUp()
  {
    DLT_Server_init();
    DLT_Datalink_init(); // Flush DLT log "lifecycle start"
  }
};

/**
 * \brief Add one log then transmit
 */
TEST_F(DLT_IT_Serial, send_one_log)
{
  INSTALL_MOCK(SCID_GetStatus);
  INSTALL_MOCK(SCID_Transmit);
  INSTALL_MOCK(DLT_Client_offset_message_id);
  INSTALL_MOCK(Dlt_Client_get_timestamp);

  // Default behavior
  CUTIE_EXPECT_CALL(SCID_GetStatus).WillRepeatedly(Return(0));
  CUTIE_EXPECT_CALL(DLT_Client_offset_message_id, _).WillRepeatedly(Invoke([](uint32_t msg_id) { return msg_id; }));
  CUTIE_EXPECT_CALL(Dlt_Client_get_timestamp).WillRepeatedly(Return(0x00));

  // Expectations
  const uint32_t msg_id = 0x123;
  auto frame            = make_serial_frame(0x00, msg_id, {0xA5});

  CUTIE_EXPECT_CALL(SCID_Transmit, EqCArray(frame.data(), frame.size()), frame.size()).WillOnce(Return(TRUE));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, msg_id, DLT_U8(0xA5)));
  DLT_Server_task();
}

/**
 * \brief Add two logs then transmit
 */
TEST_F(DLT_IT_Serial, send_two_logs)
{
  INSTALL_MOCK(SCID_GetStatus);
  INSTALL_MOCK(SCID_Transmit);
  INSTALL_MOCK(DLT_Client_offset_message_id);
  INSTALL_MOCK(Dlt_Client_get_timestamp);

  // Default behavior
  CUTIE_EXPECT_CALL(SCID_GetStatus).WillRepeatedly(Return(0));
  CUTIE_EXPECT_CALL(DLT_Client_offset_message_id, _).WillRepeatedly(Invoke([](uint32_t msg_id) { return msg_id; }));
  CUTIE_EXPECT_CALL(Dlt_Client_get_timestamp).WillRepeatedly(Return(0x00));

  // Expectations
  auto frame    = make_serial_frame(0x00, 11, {0xAA});
  auto frame_22 = make_serial_frame(0x01, 22, {0xBB, 0xBB, 0xCC, 0xCC, 0xCC, 0xCC});
  frame.insert(frame.end(), frame_22.begin(), frame_22.end());

  CUTIE_EXPECT_CALL(SCID_Transmit, EqCArray(frame.data(), frame.size()), frame.size()).WillOnce(Return(TRUE));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 11, DLT_U8(0xAA)));
  EXPECT_TRUE(DLT_LOG_ID2(context, DLT_LOG_INFO, 22, DLT_U16(0xBBBB), DLT_U32(0xCCCCCCCC)));
  DLT_Server_task();
}
