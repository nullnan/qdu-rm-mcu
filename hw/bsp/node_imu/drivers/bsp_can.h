#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"

#define BSP_CAN_MAILBOX_NUM (3)

typedef enum {
  BSP_CAN_1,
  BSP_CAN_NUM,
  BSP_CAN_ERR,
} bsp_can_t;

typedef enum {
  CAN_RX_MSG_CALLBACK,
  CAN_TX_CPLT_CALLBACK,
  BSP_CAN_CB_NUM
} bsp_can_callback_t;

void bsp_can_init(void);
int8_t bsp_can_register_callback(bsp_can_t can, bsp_can_callback_t type,
                                 void (*callback)(bsp_can_t can, void *),
                                 void *callback_arg);
int8_t bsp_can_trans_packet(bsp_can_t can, uint32_t StdId, uint8_t *data);
int8_t bsp_can_get_msg(bsp_can_t can, uint8_t *data, uint32_t *index);

#ifdef __cplusplus
}
#endif
