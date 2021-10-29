/*
 * stm32h7x5_soc.h
 *
 *  Created on: 2021年10月29日
 *      Author: zhangyao
 */

#ifndef INCLUDE_HW_ARM_STM32H7X5_SOC_H_
#define INCLUDE_HW_ARM_STM32H7X5_SOC_H_

#include "hw/arm/armv7m.h"
#include "hw/misc/stm32h7x5_syscfg.h"
#include "hw/or-irq.h"
#include "hw/timer/stm32h7x5_timer.h"
#include "qom/object.h"

#define TYPE_STM32H7X5_SOC "stm32h7x5-soc"
OBJECT_DECLARE_SIMPLE_TYPE(STM32H7X5State, STM32H7X5_SOC)

#define STM_NUM_TIMERS 4

#define FLASH_BASE_ADDRESS 0x80000000
#define FLASH_SIZE (2 * 1024 * 1024)
#define SRAM_BASE_ADDRESS 0x20000000
#define SRAM_SIZE (864 * 1024)

struct STM32H7X5State {
  /*< private >*/
  SysBusDevice parent_obj;

  /*< public >*/
  char *cpu_type;
  ARMv7MState armv7m;
  STM32H7X5SyscfgState syscfg;
  STM32H7X5TimerState timer[STM_NUM_TIMERS];
  qemu_or_irq *adc_irqs;
};

#endif /* INCLUDE_HW_ARM_STM32H7X5_SOC_H_ */
