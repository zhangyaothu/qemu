/*
 * stm32h7x5_syscfg.c
 *
 *  Created on: 2021年10月29日
 *      Author: zhangyao
 */

#include "qemu/osdep.h"
#include "hw/misc/stm32h7x5_syscfg.h"
#include "qemu/log.h"
#include "qemu/module.h"

#ifndef STM_SYSCFG_ERR_DEBUG
#define STM_SYSCFG_ERR_DEBUG 0
#endif

#define DB_PRINT_L(lvl, fmt, args...) do { \
    if (STM_SYSCFG_ERR_DEBUG >= lvl) { \
        qemu_log("%s: " fmt, __func__, ## args); \
    } \
} while (0)

#define DB_PRINT(fmt, args...) DB_PRINT_L(1, fmt, ## args)

static void stm32h7x5_syscfg_reset(DeviceState *dev) {
  STM32H7X5SyscfgState *s = STM32H7X5_SYSCFG(dev);

  /* all register reset value are zero */
  s->syscfg_pmcr = 0x00000000;
  s->syscfg_exticr1 = 0x00000000;
  s->syscfg_exticr2 = 0x00000000;
  s->syscfg_exticr3 = 0x00000000;
  s->syscfg_exticr4 = 0x00000000;
  s->syscfg_cfgr = 0x00000000;
  s->syscfg_ccsr = 0x00000000;
  s->syscfg_ccvr = 0x00000000;
  s->syscfg_cccr = 0x00000000;
  s->syscfg_pwrcr = 0x00000000;
  s->syscfg_pkgr = 0x00000000;
  s->syscfg_ur0 = 0x00000000;
  s->syscfg_ur1 = 0x00000000;
  s->syscfg_ur2 = 0x00000000;
  s->syscfg_ur3 = 0x00000000;
  s->syscfg_ur4 = 0x00000000;
  s->syscfg_ur5 = 0x00000000;
  s->syscfg_ur6 = 0x00000000;
  s->syscfg_ur7 = 0x00000000;
  s->syscfg_ur8 = 0x00000000;
  s->syscfg_ur9 = 0x00000000;
  s->syscfg_ur10 = 0x00000000;
  s->syscfg_ur11 = 0x00000000;
  s->syscfg_ur12 = 0x00000000;
  s->syscfg_ur13 = 0x00000000;
  s->syscfg_ur14 = 0x00000000;
  s->syscfg_ur15 = 0x00000000;
  s->syscfg_ur16 = 0x00000000;
  s->syscfg_ur17 = 0x00000000;
}

static uint64_t stm32h7x5_syscfg_read(void *opaque, hwaddr addr,
                                      unsigned int size) {
  STM32H7X5SyscfgState *s = opaque;

  DB_PRINT("0x%"HWADDR_PRIx"\n", addr);

  switch (addr) {
    case SYSCFG_PMCR:
      return s->syscfg_pmcr;
    case SYSCFG_EXTICR1:
      return s->syscfg_exticr1;
    case SYSCFG_EXTICR2:
      return s->syscfg_exticr2;
    case SYSCFG_EXTICR3:
      return s->syscfg_exticr3;
    case SYSCFG_EXTICR4:
      return s->syscfg_exticr4;
    case SYSCFG_CFGR:
      return s->syscfg_cfgr;
    case SYSCFG_CCSR:
      return s->syscfg_ccsr;
    case SYSCFG_CCVR:
      return s->syscfg_ccvr;
    case SYSCFG_CCCR:
      return s->syscfg_cccr;
    case SYSCFG_PWRCR:
      return s->syscfg_pwrcr;
    case SYSCFG_PKGR:
      return s->syscfg_pkgr;
    case SYSCFG_UR0:
      return s->syscfg_ur0;
    case SYSCFG_UR1:
      return s->syscfg_ur1;
    case SYSCFG_UR2:
      return s->syscfg_ur2;
    case SYSCFG_UR3:
      return s->syscfg_ur3;
    case SYSCFG_UR4:
      return s->syscfg_ur4;
    case SYSCFG_UR5:
      return s->syscfg_ur5;
    case SYSCFG_UR6:
      return s->syscfg_ur6;
    case SYSCFG_UR7:
      return s->syscfg_ur7;
    case SYSCFG_UR8:
      return s->syscfg_ur8;
    case SYSCFG_UR9:
      return s->syscfg_ur9;
    case SYSCFG_UR10:
      return s->syscfg_ur10;
    case SYSCFG_UR11:
      return s->syscfg_ur11;
    case SYSCFG_UR12:
      return s->syscfg_ur12;
    case SYSCFG_UR13:
      return s->syscfg_ur13;
    case SYSCFG_UR14:
      return s->syscfg_ur14;
    case SYSCFG_UR15:
      return s->syscfg_ur15;
    case SYSCFG_UR16:
      return s->syscfg_ur16;
    case SYSCFG_UR17:
      return s->syscfg_ur17;
    default:
      qemu_log_mask(LOG_GUEST_ERROR, "%s: Bad offset 0x%"HWADDR_PRIx"\n",
                    __func__, addr);
      return 0;
  }
  return 0;
}

static void stm32h7x5_syscfg_write(void *opaque, hwaddr addr, uint64_t val64,
                                   unsigned int size) {
  STM32H7X5SyscfgState *s = opaque;
  uint32_t value = val64;

  DB_PRINT("0x%x, 0x%"HWADDR_PRIx"\n", value, addr);

  switch (addr) {
    case SYSCFG_PMCR:
      qemu_log_mask(LOG_UNIMP,
                    "%s: Changeing the memory mapping isn't supported "
                    "in QEMU\n",
                    __func__);
      return;
    case SYSCFG_EXTICR1:
      s->syscfg_exticr1 = (value & 0xFFFF);
      return;
    case SYSCFG_EXTICR2:
      s->syscfg_exticr2 = (value & 0xFFFF);
      return;
    case SYSCFG_EXTICR3:
      s->syscfg_exticr3 = (value & 0xFFFF);
      return;
    case SYSCFG_EXTICR4:
      s->syscfg_exticr4 = (value & 0xFFFF);
      return;
    case SYSCFG_CFGR:
      /* bit can be set by software, clear only when reset */
      s->syscfg_cfgr |= (value & 0xFFFF);
      return;
    case SYSCFG_CCSR:
      s->syscfg_ccsr = (value & 0x10102);
      return;
    case SYSCFG_CCVR:
      s->syscfg_ccvr = (value & 0xF);
      return;
    case SYSCFG_CCCR:
      s->syscfg_cccr = (value & 0xF);
      return;
    case SYSCFG_PWRCR:
      s->syscfg_pwrcr = (value & 0x1);
      return;
    case SYSCFG_PKGR:
      s->syscfg_pkgr = (value & 0xF);
      return;
    /* TODO:
     * continue with the ugly writing method
     *  */
    default:
      qemu_log_mask(LOG_GUEST_ERROR, "%s: Bad offset 0x%"HWADDR_PRIx"\n",
                    __func__, addr);
  }
}

/* formatter:off */
static const MemoryRegionOps stm32h7x5_syscfg_ops = {
    .read = stm32h7x5_syscfg_read,
    .write = stm32h7x5_syscfg_write,
    .endianness = DEVICE_NATIVE_ENDIAN, };
/* formatter:on */

static void stm32h7x5_syscfg_init(Object *obj) {
  STM32H7X5SyscfgState *s = STM32H7X5_SYSCFG(obj);

  memory_region_init_io(&s->mmio, obj, &stm32h7x5_syscfg_ops, s,
  TYPE_STM32H7X5_SYSCFG,
                        0x400);
  sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32h7x5_syscfg_class_init(ObjectClass *klass, void *data) {
  DeviceClass *dc = DEVICE_CLASS(klass);

  dc->reset = stm32h7x5_syscfg_reset;
}

/* formatter:off */
static const TypeInfo stm32h7x5_syscfg_info = {
    .name = TYPE_STM32H7X5_SYSCFG,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32H7X5SyscfgState),
    .instance_init = stm32h7x5_syscfg_init,
    .class_init = stm32h7x5_syscfg_class_init,
};
/* formatter:on */

static void stm32h7x5_syscfg_register_types(void) {
  type_register_static(&stm32h7x5_syscfg_info);
}

type_init(stm32h7x5_syscfg_register_types)
