#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;

/* Variables and functions */
 int APICRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APICWrite (int /*<<< orphan*/ ,int) ; 
 int APIC_DIVISOR ; 
 int /*<<< orphan*/  APIC_ICRT ; 
 int /*<<< orphan*/  APIC_INTEGRATED (int) ; 
 int /*<<< orphan*/  APIC_LVTT ; 
 int APIC_LVT_PERIODIC ; 
 int /*<<< orphan*/  APIC_TDCR ; 
 int APIC_TDCR_1 ; 
 int APIC_TDCR_16 ; 
 int APIC_TIMER_BASE_DIV ; 
 int /*<<< orphan*/  APIC_VER ; 
 int GET_APIC_VERSION (int) ; 
 int LOCAL_TIMER_VECTOR ; 
 int SET_APIC_TIMER_BASE (int) ; 

VOID APICSetupLVTT(ULONG ClockTicks)
{
   ULONG tmp;

   tmp = GET_APIC_VERSION(APICRead(APIC_VER));
   if (!APIC_INTEGRATED(tmp))
   {
      tmp = SET_APIC_TIMER_BASE(APIC_TIMER_BASE_DIV) | APIC_LVT_PERIODIC | LOCAL_TIMER_VECTOR;
   }
   else
   {
      /* Periodic timer */
      tmp = APIC_LVT_PERIODIC | LOCAL_TIMER_VECTOR;
   }
   APICWrite(APIC_LVTT, tmp);

   tmp = APICRead(APIC_TDCR);
   tmp &= ~(APIC_TDCR_1 | APIC_TIMER_BASE_DIV);
   tmp |= APIC_TDCR_16;
   APICWrite(APIC_TDCR, tmp);
   APICWrite(APIC_ICRT, ClockTicks / APIC_DIVISOR);
}