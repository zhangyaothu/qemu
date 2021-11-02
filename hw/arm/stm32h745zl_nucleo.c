/*
 * stm32h745zl_nucleo.c
 *
 *  Created on: 2021年10月29日
 *      Author: zhangyao
 */

#include <stdio.h>
#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/boards.h"
#include "hw/qdev-properties.h"
#include "qemu/error-report.h"
#include "hw/arm/stm32h7x5_soc.h"
#include "hw/arm/boot.h"

#define SYSCLK_FRQ 480000000ULL // 480MHz

static void stm32h745zl_nucleo_init(MachineState *machine) {
  DeviceState *dev;

  fprintf(stderr, "%s\n", __func__);
  /*
   * armv7m_systick.h in hw/timer
   * Multiplication factor to convert from system clock ticks to qemu timer
   * ticks. This should be set (by board code, usually) to a value
   * equal to NANOSECONDS_PER_SECOND / frq, where frq is the clock frequency
   * in Hz of the CPU.
   *
   * This value is used by the systick device when it is running in
   * its "use the CPU clock" mode (ie when SYST_CSR.CLKSOURCE == 1) to
   * set how fast the timer should tick.
   */
  system_clock_scale = NANOSECONDS_PER_SECOND / SYSCLK_FRQ;

  dev = qdev_new(TYPE_STM32H7X5_SOC);
  qdev_prop_set_string(dev, "cpu-type", ARM_CPU_TYPE_NAME("cortex-m7"));
  sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_fatal);

  fprintf(stderr, "begin to load kernel: %s\n", machine->kernel_filename);
  armv7m_load_kernel(ARM_CPU(first_cpu), machine->kernel_filename, FLASH_BANK_SIZE);
  fprintf(stderr, "kernel loaded\n");
}

static void stm32h745zl_nucleo_machine_init(MachineClass *mc) {
  mc->desc = "ST STM32H745ZL NUCLEO (Cortex-M7 and Cortex-M4)";
  mc->init = stm32h745zl_nucleo_init;
}

DEFINE_MACHINE("stm32h745zl_nucleo", stm32h745zl_nucleo_machine_init)
