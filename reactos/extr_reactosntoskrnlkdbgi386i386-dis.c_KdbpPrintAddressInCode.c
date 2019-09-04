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
struct disassemble_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,unsigned int) ; 
 int /*<<< orphan*/  KdbSymPrintAddress (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
KdbpPrintAddressInCode(unsigned int Addr, struct disassemble_info * Ignored)
{
    if (!KdbSymPrintAddress((void*)Addr, NULL))
    {
      DbgPrint("<%08x>", Addr);
    }
}