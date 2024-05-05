/**
 * \file it_dlt_helper.h
 */

#pragma once

inline std::vector<std::uint8_t> make_msg_id(uint32_t msg_id)
{
  std::vector<std::uint8_t> msg_id_vec;
  msg_id_vec.push_back((uint8_t) (msg_id >> 24U));
  msg_id_vec.push_back((uint8_t) (msg_id >> 16U));
  msg_id_vec.push_back((uint8_t) (msg_id >> 8U));
  msg_id_vec.push_back((uint8_t) (msg_id >> 0U));
  return msg_id_vec;
}

std::vector<std::uint8_t>
make_serial_frame(uint8_t msg_counter, std::uint32_t msg_id, std::vector<std::uint8_t> payload, char phud_id = '0')
{
  static const std::vector<uint8_t> DLS1           = {0x44, 0x4C, 0x53, 0x01};
  static const std::uint8_t type                   = 0x36;
  const std::vector<std::uint8_t> PHDx             = {'P', 'H', 'D', (uint8_t) phud_id}; // PHUD0
  static const std::vector<std::uint8_t> timestamp = {0x00, 0x00, 0x00, 0x00};
  std::vector<std::uint8_t> frame_size             = {0x00, (uint8_t) (0x10U + payload.size())};
  auto msg_id_vec                                  = make_msg_id(msg_id);

  std::vector<std::uint8_t> frame = DLS1;
  frame.push_back(type);
  frame.push_back(msg_counter);
  frame.insert(frame.end(), frame_size.begin(), frame_size.end());
  frame.insert(frame.end(), PHDx.begin(), PHDx.end());
  frame.insert(frame.end(), timestamp.begin(), timestamp.end());
  frame.insert(frame.end(), msg_id_vec.begin(), msg_id_vec.end());
  frame.insert(frame.end(), payload.begin(), payload.end());
  return frame;
}

/**
 * \brief stream operator for std::vector<std::uint8_t>
 */
std::ostream& operator<<(std::ostream& output, const std::vector<std::uint8_t>& values)
{
  for (auto const& value : values)
  {
    output << +value << ' ';
  }
  return output;
}
