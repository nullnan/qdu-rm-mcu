#pragma once

#include <string.h>

#include "term.hpp"

namespace Device {
class BaseMotor {
 public:
  typedef struct {
    float rotor_abs_angle;  /* 转子绝对角度 单位：rad */
    float rotational_speed; /* 转速 单位：rpm */
    float torque_current;   /* 转矩电流 单位：A*/
    float temp;             /* 电机温度 单位：℃*/
  } Feedback;

  BaseMotor(const char *name)
      : cmd_(this, BaseMotor::ShowCMD, this->name_, System::Term::DevDir()) {
    strncpy(this->name_, name, sizeof(this->name_));
    memset(&(this->feedback_), 0, sizeof(this->feedback_));
  }

  virtual void Control(float output) = 0;

  virtual bool Update() = 0;

  virtual void Relax() = 0;

  float GetAngle() { return this->feedback_.rotor_abs_angle; }

  float GetSpeed() { return this->feedback_.rotational_speed; }

  float GetCurrent() { return this->feedback_.torque_current; }

  static void ShowCMD(BaseMotor *motor, int argc, char *argv[]) {
    RM_UNUSED(argc);
    RM_UNUSED(argv);

    ms_printf("电机 [%s] 反馈数据:", motor->name_);
    ms_enter();
    ms_printf("最近一次反馈时间:%fs.", motor->last_online_tick_ / 1000.0f);
    ms_enter();
    ms_printf("角度:%frad 速度:%frpm 电流:%fA 温度:%f℃",
              motor->feedback_.rotor_abs_angle,
              motor->feedback_.rotational_speed,
              motor->feedback_.torque_current, motor->feedback_.temp);
    ms_enter();
  }

  char name_[20];

  Feedback feedback_;

  uint32_t last_online_tick_ = 0;

  System::Term::Command<BaseMotor *> cmd_;
};
}  // namespace Device
