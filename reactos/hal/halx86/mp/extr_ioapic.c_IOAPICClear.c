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
 int /*<<< orphan*/  IOAPICClearPin (int,int) ; 

__attribute__((used)) static VOID 
IOAPICClear(ULONG Apic)
{
   ULONG Pin;

   for (Pin = 0; Pin < /*IOAPICMap[Apic].EntryCount*/24; Pin++)
   {
     IOAPICClearPin(Apic, Pin);
   }
}