//! \file it_dlt_server.cpp
//! \brief DLT integration tests
//! \date  2023-10
//! \author Nicolas Boutin

#include "mock.hpp"

#include "matcher.h"

extern "C" {

#include "dlt_client.h"
#include "dlt_server.h"
// #include "dlt_datalink.h"
// #include "dlt_server_config.h"

extern void Dlt_Server_log_application_software_version(void);
}

using namespace testing;
using namespace std;

class DLT_IT_Server : public ::testing::Test
{
protected:
  void SetUp()
  {
    DLT_Server_init();
  }
};

TEST_F(DLT_IT_Server, log_application_software_version)
{
  Dlt_Server_log_application_software_version();
}
