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

#define FLASH_BANK1 0x08000000
#define FLASH_BANK2 0x08100000
#define FLASH_BANK_SIZE (1 * 1024 * 1024)

#define SRAM_AXI 0x24000000
#define SRAM_AXI_SIZE (512 * 1024)
#define SRAM_SRAM1 0x30000000
#define SRAM_SRAM1_SIZE (128 * 1024)
#define SRAM_SRAM2 0x30020000
#define SRAM_SRAM2_SIZE (128 * 1024)
#define SRAM_SRAM3 0x30040000
#define SRAM_SRAM3_SIZE (32 * 1024)
#define SRAM_SRAM4 0x38000000
#define SRAM_SRAM4_SIZE (64 * 1024)
#define SRAM_BACKUP_SRAM 0x38800000
#define SRAM_BACKUP_SIZE (4 * 1024)

#define DTCM 0x20000000
#define DTCM_SIZE (128 * 1024)
#define ITCM 0x00000000
#define ITCM_SIZE (128 * 1024)

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
