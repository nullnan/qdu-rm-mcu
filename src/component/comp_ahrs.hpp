/*
  开源的AHRS算法。
  MadgwickAHRS
*/

#pragma once

#include "comp_type.hpp"
#include "comp_utils.hpp"
#include "om.hpp"
#include "term.hpp"
#include "thread.hpp"

namespace Component {
class AHRS {
 public:
  AHRS();

  void Update();

  void GetEulr();

  static void ShowCMD(AHRS *ahrs, int argc, char *argv[]);

  float last_update_;
  float dt_;
  float now_;  // TODO:封装

  System::Thread thread_;

  Message::Topic<Type::Quaternion> quat_tp_;

  Message::Topic<Type::Eulr> eulr_tp_;

  Type::Quaternion quat_;
  Type::Eulr eulr_;

  Type::Vector3 accl_;
  Type::Vector3 gyro_;

  System::Term::Command<AHRS *> cmd_;
};
}  // namespace Component
