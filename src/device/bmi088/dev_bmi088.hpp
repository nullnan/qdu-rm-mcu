#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "comp_ahrs.hpp"
#include "dev.hpp"
#include "term.hpp"

namespace Device {
class BMI088 {
 public:
  typedef struct {
    Component::Type::Vector3 gyro_offset; /* 陀螺仪偏置 */
  } Calibration;                          /* BMI088校准数据 */

  typedef struct {
    float rot_mat[3][3]; /* 旋转矩阵 */
  } Rotation;

  typedef enum {
    BMI_ACCL,
    BMI_GYRO,
  } DeviceType;

  BMI088(BMI088::Rotation &rot);

  bool Init();

  void ParseGyro();

  void ParseAccel();

  bool StartRecvGyro();

  bool StartRecvAccel();

  void Select(DeviceType type);

  void Unselect(DeviceType type);

  void WriteSingle(DeviceType type, uint8_t reg, uint8_t data);

  uint8_t ReadSingle(DeviceType type, uint8_t reg);

  void Read(DeviceType type, uint8_t reg, uint8_t *data, uint8_t len);

  static void CaliCMD(BMI088 *bmi088, int argc, char *argv[]);

  Calibration cali;
  Rotation &rot;

  System::Semaphore gyro_raw_;
  System::Semaphore accl_raw_;
  System::Semaphore gyro_new_;
  System::Semaphore accl_new_;
  System::Semaphore new_;

  float temp_; /* 温度 */

  System::Thread thread_;

  Message::Topic<Component::Type::Vector3> accl_tp_;
  Message::Topic<Component::Type::Vector3> gyro_tp_;

  Component::Type::Vector3 accl_;
  Component::Type::Vector3 gyro_;

  System::Term::Command<BMI088 *> cmd_;
};
}  // namespace Device
