/*
 * stm32h7x5_soc.c
 *
 *  Created on: 2021年10月29日
 *      Author: zhangyao
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/module.h"
#include "exec/address-spaces.h"
#include "hw/arm/stm32h7x5_soc.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-core.h"
#include "hw/misc/unimp.h"
#include "hw/sysbus.h"

/* general purpose timers: TIM2/TIM3/TIM4/TIM5 */
static const uint32_t timer_addr[STM_NUM_TIMERS] = { 0x40000000, 0x40000400,
    0x40000800, 0x40000C00 };
static const int timer_irq[STM_NUM_TIMERS] = {28, 29, 30, 50};

static void stm32h7x5_soc_initfn(Object *obj) {
  STM32H7X5State *s = STM32H7X5_SOC(obj);
  int i;

  object_initialize_child(obj, "armv7m", &s->armv7m, TYPE_ARMV7M);

  object_initialize_child(obj, "syscfg", &s->syscfg, TYPE_STM32H7X5_SYSCFG);

  for (i = 0; i < STM_NUM_TIMERS; i++) {
    object_initialize_child(obj, "timer[*]", &s->timer[i],
                            TYPE_STM32H7X5_TIMER);
  }

  s->adc_irqs = OR_IRQ(object_new(TYPE_OR_IRQ));
}

/* formatter:off */
static Property stm32h7x5_soc_properties[] = {
  DEFINE_PROP_STRING("cpu-type", STM32H7X5State, cpu_type),
  DEFINE_PROP_END_OF_LIST(),
};
/* formatter:on */

static void stm32h7x5_soc_realize(DeviceState *dev_soc, Error **errp) {
  STM32H7X5State *s = STM32H7X5_SOC(dev_soc);
  DeviceState *dev, *armv7m;
  SysBusDevice *busdev;
  int i;

  /* static declared system memory, new memory should be associated with it */
  MemoryRegion *system_memory = get_system_memory();
  MemoryRegion *sram = g_new(MemoryRegion, 1);
  MemoryRegion *flash = g_new(MemoryRegion, 1);
  MemoryRegion *flash_alias = g_new(MemoryRegion, 1);

  memory_region_init_rom(flash, OBJECT(dev_soc), "STM32H7X5.flash", FLASH_BANK_SIZE, &error_fatal);
  memory_region_init_alias(flash_alias, OBJECT(dev_soc), "STM32H7X5.flash.alias", flash, 0, FLASH_BANK_SIZE);

  memory_region_add_subregion(system_memory, FLASH_BANK1, flash);
  memory_region_add_subregion(system_memory, 0, flash_alias);

  memory_region_init_ram(sram, NULL, "STM32H7X5.sram", SRAM_AXI_SIZE, &error_fatal);
  memory_region_add_subregion(system_memory, SRAM_AXI, sram);

  armv7m = DEVICE(&s->armv7m);
  qdev_prop_set_uint32(armv7m, "num-irq", 96);
  qdev_prop_set_string(armv7m, "cpu-type", s->cpu_type);
  qdev_prop_set_bit(armv7m, "enable-bitband", true);
  object_property_set_link(OBJECT(&s->armv7m), "memory",
                           OBJECT(get_system_memory()), &error_abort);
  if (!sysbus_realize(SYS_BUS_DEVICE(&s->armv7m), errp)) {
    return;
  }

  /* System configuration controller */
  dev = DEVICE(&s->syscfg);
  if (!sysbus_realize(SYS_BUS_DEVICE(&s->syscfg), errp)) {
    return;
  }
  busdev = SYS_BUS_DEVICE(dev);
  sysbus_mmio_map(busdev, 0, 0x40013800);

  /* Timer 2 to 5 */
  for (i = 0; i < STM_NUM_TIMERS; i++) {
    dev = DEVICE(&(s->timer[i]));
    qdev_prop_set_uint64(dev, "clock-frequency", 1000000000);
    if (!sysbus_realize(SYS_BUS_DEVICE(&s->timer[i]), errp)) {
      return;
    }
    busdev = SYS_BUS_DEVICE(dev);
    sysbus_mmio_map(busdev, 0, timer_addr[i]);
    sysbus_connect_irq(busdev, 0, qdev_get_gpio_in(armv7m, timer_irq[i]));
  }

//  create_unimplemented_device("RCC",       0x58024400, 0x400);
//  create_unimplemented_device("FLASH_REG",       0x52002000, 0x1000);
//  create_unimplemented_device("EXTI",      0x58000000, 0x400);
//  create_unimplemented_device("DBGMCU",      0x5C001000, 0x400);
  create_unimplemented_device("PERIPHERALS", 0x40000000, 0x1FFFFFFF);
}

static void stm32h7x5_soc_class_init(ObjectClass *klass, void *data) {
  DeviceClass *dc = DEVICE_CLASS(klass);

  dc->realize = stm32h7x5_soc_realize;
  device_class_set_props(dc, stm32h7x5_soc_properties);
}

/* formatter:off */
static const TypeInfo stm32h7x5_soc_info = {
  .name = TYPE_STM32H7X5_SOC,
  .parent = TYPE_SYS_BUS_DEVICE,
  .instance_size = sizeof(STM32H7X5State),
  .instance_init = stm32h7x5_soc_initfn,
  .class_init = stm32h7x5_soc_class_init,
};
/* formatter:on */

static void stm32h7x5_soc_types(void) {
  type_register_static(&stm32h7x5_soc_info);
}

type_init(stm32h7x5_soc_types)
