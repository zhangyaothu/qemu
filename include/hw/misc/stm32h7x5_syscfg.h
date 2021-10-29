/*
 * stm32h7x5_syscfg.h
 *
 *  Created on: 2021年10月29日
 *      Author: zhangyao
 */

#ifndef INCLUDE_HW_MISC_STM32H7X5_SYSCFG_H_
#define INCLUDE_HW_MISC_STM32H7X5_SYSCFG_H_

#include "hw/sysbus.h"
#include "qom/object.h"

/* implemented according to rm0399-stm32h745755-and-stm32h747757-advanced-armbased-32bit-mcus-stmicroelectronics.pdf */
#define SYSCFG_PMCR    0x04
#define SYSCFG_EXTICR1 0x08
#define SYSCFG_EXTICR2 0x0C
#define SYSCFG_EXTICR3 0x10
#define SYSCFG_EXTICR4 0x14
#define SYSCFG_CFGR    0x18
#define SYSCFG_CCSR    0x20
#define SYSCFG_CCVR    0x24
#define SYSCFG_CCCR    0x28
#define SYSCFG_PWRCR   0x2C
#define SYSCFG_PKGR    0x124
#define SYSCFG_UR0     0x300
#define SYSCFG_UR1     0x304
#define SYSCFG_UR2     0x308
#define SYSCFG_UR3     0x30C
#define SYSCFG_UR4     0x310
#define SYSCFG_UR5     0x314
#define SYSCFG_UR6     0x318
#define SYSCFG_UR7     0x31C
#define SYSCFG_UR8     0x320
#define SYSCFG_UR9     0x324
#define SYSCFG_UR10    0x328
#define SYSCFG_UR11    0x32C
#define SYSCFG_UR12    0x330
#define SYSCFG_UR13    0x334
#define SYSCFG_UR14    0x338
#define SYSCFG_UR15    0x33C
#define SYSCFG_UR16    0x340
#define SYSCFG_UR17    0x344

#define TYPE_STM32H7X5_SYSCFG "stm32h7x5-syscfg"
OBJECT_DECLARE_SIMPLE_TYPE(STM32H7X5SyscfgState, STM32H7X5_SYSCFG)

struct STM32H7X5SyscfgState {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;

    uint32_t syscfg_pmcr;
    uint32_t syscfg_exticr1;
    uint32_t syscfg_exticr2;
    uint32_t syscfg_exticr3;
    uint32_t syscfg_exticr4;
    uint32_t syscfg_cfgr;
    uint32_t syscfg_ccsr;
    uint32_t syscfg_ccvr;
    uint32_t syscfg_cccr;
    uint32_t syscfg_pwrcr;
    uint32_t syscfg_pkgr;
    uint32_t syscfg_ur0;
    uint32_t syscfg_ur1;
    uint32_t syscfg_ur2;
    uint32_t syscfg_ur3;
    uint32_t syscfg_ur4;
    uint32_t syscfg_ur5;
    uint32_t syscfg_ur6;
    uint32_t syscfg_ur7;
    uint32_t syscfg_ur8;
    uint32_t syscfg_ur9;
    uint32_t syscfg_ur10;
    uint32_t syscfg_ur11;
    uint32_t syscfg_ur12;
    uint32_t syscfg_ur13;
    uint32_t syscfg_ur14;
    uint32_t syscfg_ur15;
    uint32_t syscfg_ur16;
    uint32_t syscfg_ur17;
};

#endif /* INCLUDE_HW_MISC_STM32H7X5_SYSCFG_H_ */
