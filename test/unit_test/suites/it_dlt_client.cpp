//! \file it_dlt_client.cpp
//! \brief DLT MCU test
//! \date  2024-04
//! \author Nicolas Boutin

#include "mock.hpp"
// #include "Cutie/mock.hpp"
#include "mock.hpp"
#include "matcher.h"
#include <gmock/gmock.h>

extern "C" {
#include "datalink/dlt_datalink.h"
#include "dlt/dlt_client.h"
#include "dlt/dlt_server.h"
#include "dlt_conf.h"
}

using namespace testing;

DECLARE_MOCKABLE(DLT_datalink_copy_log, 2);

class DLT_IT_Client : public ::testing::Test {
protected:
  void SetUp()
  {
    DLT_server_init();
  }
};

TEST_F(DLT_IT_Client, register_app)
{
  DLT_REGISTER_APP(app, "app description");
}
TEST_F(DLT_IT_Client, declare_context)
{
  DLT_DECLARE_CONTEXT(declare_context);
  (void) declare_context;
}

TEST_F(DLT_IT_Client, import_context)
{
  DLT_IMPORT_CONTEXT(import_context);
  (void) import_context;
}

TEST_F(DLT_IT_Client, export_context)
{
  DLT_EXPORT_CONTEXT(export_context);
  (void) export_context;
}

TEST_F(DLT_IT_Client, register_context_001)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  ASSERT_THAT(context.ctx_name, ElementsAre('c', 't', 'i', 'd'));
  EXPECT_EQ(context.log_level, DLT_LOG_LEVEL_DEFAULT);
  EXPECT_EQ(context.msg_counter, 255);
}

/**
 * \brief context_id too short
 */
TEST_F(DLT_IT_Client, register_context_002)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ct", "context description");
  ASSERT_THAT(context.ctx_name, ElementsAre('c', 't', '_', '_'));
}

/**
 * \brief context_id too long
 */
TEST_F(DLT_IT_Client, register_context_003)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "context", "context description");
  ASSERT_THAT(context.ctx_name, ElementsAre('c', 'o', 'n', 't'));
}

/**
 * \brief Default log level
 */
TEST_F(DLT_IT_Client, default_log_level)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_EQ(context.log_level, DLT_LOG_LEVEL_DEFAULT);
}

/**
 * \brief Set log level
 */
TEST_F(DLT_IT_Client, set_log_level_001)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  DLT_CONTEXT_SET_LOG_LEVEL(context, DLT_LOG_INFO);
  EXPECT_EQ(context.log_level, DLT_LOG_INFO);
}

/**
 * \brief Set log level
 */
TEST_F(DLT_IT_Client, set_log_level_002)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  DLT_CONTEXT_SET_LOG_LEVEL(context, DLT_LOG_VERBOSE);
  EXPECT_EQ(context.log_level, DLT_LOG_VERBOSE);
}

/**
 * \brief Set log level
 */
TEST_F(DLT_IT_Client, set_log_level_003)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  DLT_CONTEXT_SET_LOG_LEVEL(context, DLT_LOG_FATAL);
  EXPECT_EQ(context.log_level, DLT_LOG_FATAL);
}

/**
 * \brief Set log level
 */
TEST_F(DLT_IT_Client, set_log_level_004)
{
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  DLT_CONTEXT_SET_LOG_LEVEL(context, DLT_LOG_OFF);
  EXPECT_EQ(context.log_level, DLT_LOG_OFF);
}

/**
 * \brief DLT log id
 */
TEST_F(DLT_IT_Client, dlt_log_id)
{
  INSTALL_MOCK(DLT_datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xA5};
  CUTIE_EXPECT_CALL(DLT_datalink_copy_log,
                    AllOf(Field(&dlt_context_t::ctx_name, EqCArray("ctid", 4)),
                          Field(&dlt_context_t::log_level, Eq(DLT_LOG_INFO)),
                          Field(&dlt_context_t::msg_counter, Eq(0))),
                    AllOf(Field(&DLT_Frame_t::log_level, Eq(DLT_LOG_INFO)),
                          Field(&DLT_Frame_t::msg_counter, Eq(0)),
                          Field(&DLT_Frame_t::msg_id, Eq(1)),
                          Field(&DLT_Frame_t::payload, Field(&BUF_t::data, EqCArray(payload.data(), payload.size())))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_U8(0xA5)));
}
#if 0
/**
 * \brief DLT_BOOL
 */
TEST_F(DLT_IT_Client, dlt_bool)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0x01};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_BOOL(true)));
}

/**
 * \brief DLT_U8
 */
TEST_F(DLT_IT_Client, dlt_uint8)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xA5};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_U8(0xA5)));
}

/**
 * \brief DLT_U16
 */
TEST_F(DLT_IT_Client, dlt_uint16)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xAA, 0xBB};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_U16(0xAABB)));
}

/**
 * \brief DLT_U32
 */
TEST_F(DLT_IT_Client, dlt_uint32)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xAA, 0xBB, 0xCC, 0xDD};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_U32(0xAABBCCDD)));
}

/**
 * \brief DLT_U64
 */
TEST_F(DLT_IT_Client, dlt_uint64)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_U64(0xAABBCCDDEEFF1122)));
}

/**
 * \brief DLT_I8
 */
TEST_F(DLT_IT_Client, dlt_i8)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  InSequence s;
  std::vector<std::int8_t> payload_1 = {127};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload_1.data(), payload_1.size()))))
      .WillOnce(Return(true));
  std::vector<std::int8_t> payload_2 = {-128};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload_2.data(), payload_2.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_I8(127)));
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_I8(-128)));
}

/**
 * \brief DLT_I16
 */
TEST_F(DLT_IT_Client, dlt_i16)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::int16_t data                 = 32767;
  std::vector<std::uint8_t> payload = {(std::uint8_t)(data >> 8), (std::uint8_t)(data & 0xFF)};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_I16(data)));
}

/**
 * \brief DLT_I32
 */
TEST_F(DLT_IT_Client, dlt_i32)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0xAA, 0xBB, 0xCC, 0xDD};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_I32(0xAABBCCDD)));
}

/**
 * \brief DLT_RAW
 */
TEST_F(DLT_IT_Client, dlt_raw)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> data    = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22};
  std::vector<std::uint8_t> payload = {0x00, (uint8_t) data.size()};
  payload.insert(payload.end(), data.begin(), data.end());
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_RAW(data.data(), data.size())));
}

/**
 * \brief DLT_STRING
 */
TEST_F(DLT_IT_Client, dlt_string_001)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0x00, 0x08 + 1, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0'};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_STRING("abcdefgh")));
}

/**
 * \brief DLT_STRING
 */
TEST_F(DLT_IT_Client, dlt_string_002)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {0x00, 0x02, 'A', '\0'};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_STRING("A")));
}

/**
 * \brief DLT_CSTRING
 */
TEST_F(DLT_IT_Client, dlt_cstring)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {};
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID1(context, DLT_LOG_INFO, 1, DLT_CSTRING("abcdefgh")));
}

/**
 * \brief DLT_LOG_ID12 with all arguments formatter
 */
TEST_F(DLT_IT_Client, dlt_log_id_all_arg_formatter)
{
  INSTALL_MOCK(DLT_Datalink_copy_log);

  // Expectations
  std::vector<std::uint8_t> payload = {true};
  payload.push_back(0x22);
  std::vector<std::uint8_t> data = {0x33, 0x33};
  payload.insert(payload.end(), data.begin(), data.end());
  data = {0x44, 0x44, 0x44, 0x44};
  payload.insert(payload.end(), data.begin(), data.end());
  data = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
  payload.insert(payload.end(), data.begin(), data.end());
  payload.push_back(127);
  data = {0x7F, 0xFF};
  payload.insert(payload.end(), data.begin(), data.end());
  data = {0x7F, 0xFF, 0xFF, 0xFF};
  payload.insert(payload.end(), data.begin(), data.end());
  data = {0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  payload.insert(payload.end(), data.begin(), data.end());
  payload.push_back(0x00);
  payload.push_back(0x08);
  data = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  payload.insert(payload.end(), data.begin(), data.end());
  payload.push_back(0x00);
  payload.push_back(0x08 + 1);
  data = {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
  payload.insert(payload.end(), data.begin(), data.end());
  CUTIE_EXPECT_CALL(DLT_Datalink_copy_log,
                    _,
                    Field(&DLT_Frame_t::payload, Field(&BUFS_t::data, EqCArray(payload.data(), payload.size()))))
      .WillOnce(Return(true));

  // Test steps
  DLT_DECLARE_CONTEXT(context);
  DLT_REGISTER_CONTEXT(context, "app", "ctid", "context description");
  EXPECT_TRUE(DLT_LOG_ID12(context,
                           DLT_LOG_INFO,
                           1,
                           DLT_BOOL(true),
                           DLT_U8(0x22),
                           DLT_U16(0x3333),
                           DLT_U32(0x44444444),
                           DLT_U64(0x5555555555555555),
                           DLT_I8(127),
                           DLT_I16(32767),
                           DLT_I32(2147483647),
                           DLT_I64(9223372036854775807),
                           DLT_RAW("abcdefgh", 8),
                           DLT_STR("ijklmnop"),
                           DLT_C_STR("qrstuvwx")));
}

#endif
