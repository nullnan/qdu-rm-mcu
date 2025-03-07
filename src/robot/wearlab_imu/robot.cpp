#include "robot.hpp"

/* clang-format off */
Robot::WearLabIMU::Param param = {
  .bmi088_rot =
  {
    .rot_mat =
    {
      {-1, +0, +0},
      {+0, +1, +0},
      {+0, +0, -1},
    },
  },

  .led = {
    .gpio = BSP_GPIO_LED,
    .timeout = 200,
  }
};
/* clang-format on */

void robot_init() {
  auto init_thread_fn = [](void* arg) {
    RM_UNUSED(arg);

    Robot::WearLabIMU robot(param);

    while (1) {
      System::Thread::Sleep(UINT32_MAX);
    }
  };

  System::Thread init_thread;

  init_thread.Create(init_thread_fn, (void*)0, "init_thread_fn", 512,
                     System::Thread::Realtime);
}
