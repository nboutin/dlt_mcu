
#pragma once

#include <gmock/gmock.h>

using namespace testing;

MATCHER_P(EqBUFS, bufs, "Matches BUFS_t")
{
  return (arg.write_index == bufs.write_index) && (memcmp(arg.data, bufs.data, bufs.write_index) == 0)
         && (arg.read_index == bufs.read_index) && (arg.size == bufs.size);
}

MATCHER_P2(EqCArray, array, size, "Matches C array")
{
  *result_listener << "EqCArray: arg=";
  for (auto i = 0U; i < (std::uint32_t) size; i++)
  {
    *result_listener << PrintToString(((const uint8_t*) arg)[i]) << "|";
  }
  return (memcmp(arg, array, size) == 0);
}
