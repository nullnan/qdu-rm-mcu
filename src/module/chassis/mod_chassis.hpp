/**
 * @file chassis.h
 * @author Qu Shen (503578404@qq.com)
 * @brief 底盘模组
 * @version 1.0.0
 * @date 2021-04-15
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "comp_actuator.hpp"
#include "comp_filter.hpp"
#include "comp_mixer.hpp"
#include "comp_pid.hpp"
#include "dev_cap.hpp"
#include "dev_motor.hpp"
#include "dev_referee.hpp"
#include "dev_rm_motor.hpp"

namespace Module {
template <typename Motor, typename MotorParam>
class Chassis {
 public:
  /* 底盘运行模式 */
  typedef enum {
    Relax, /* 放松模式，电机不输出。一般情况底盘初始化之后的模式 */
    Break, /* 刹车模式，电机闭环控制保持静止。用于机器人停止状态 */
    FollowGimbal, /* 通过闭环控制使车头方向跟随云台 */
    Rotor, /* 小陀螺模式，通过闭环控制使底盘不停旋转 */
    Indenpendent, /* 独立模式。底盘运行不受云台影响 */
  } Mode;

  typedef enum {
    ChangeModeRelax,
    ChangeModeFollow,
    ChangeModeRotor,
    ChangeModeIndenpendent,
  } ChassisEvent;

  /* 底盘参数的结构体，包含所有初始Component化用的参数，通常是const，存好几组 */
  typedef struct {
    Component::Mixer::Mode type; /* 底盘类型，底盘的机械设计和轮子选型 */

    Component::PID::Param follow_pid_param; /* 跟随云台PID的参数 */

    const std::vector<Component::CMD::EventMapItem> event_map;

    Component::SpeedActuator::Param actuator_param[4];

    MotorParam motor_param[4];
  } Param;

  typedef struct {
    Device::Referee::Status status;
    float chassis_power_limit;
    float chassis_pwr_buff;
    float chassis_watt;
  } RefForChassis;

  Chassis(Param &param, float control_freq);

  void UpdateFeedback();

  void Control();

  void SetMode(Mode mode);

  void PackOutput();

  void PraseRef();

  float CalcWz(const float lo, const float hi);

  Param param_;

  float dt_;

  uint32_t last_wakeup_;

  uint32_t now_;

  RefForChassis ref_;

  Mode mode_ = Relax;

  Component::SpeedActuator *actuator_[4];

  Device::BaseMotor *motor_[4];

  /* 底盘设计 */
  Component::Mixer mixer_;

  Component::Type::MoveVector move_vec_; /* 底盘实际的运动向量 */

  float wz_dir_mult_; /* 小陀螺模式旋转方向乘数 */

  /* PID计算的目标值 */
  struct {
    float *motor_rotational_speed; /* 电机转速的动态数组，单位：RPM */
  } setpoint;

  /* 反馈控制用的PID */

  Component::PID follow_pid_; /* 跟随云台用的PID */

  System::Thread thread_;

  System::Semaphore ctrl_lock_;

  Message::Topic<Device::Cap::Output> cap_out_tp_ =
      Message::Topic<Device::Cap::Output>("cap_out");

  Device::Cap::Output cap_out_;

  float yaw_;
  Device::Referee::Data raw_ref_;
  Device::Cap::Info cap_info_;
  Component::CMD::ChassisCMD cmd_;
};

typedef Chassis<Device::RMMotor, Device::RMMotor::Param> RMChassis;
}  // namespace Module
