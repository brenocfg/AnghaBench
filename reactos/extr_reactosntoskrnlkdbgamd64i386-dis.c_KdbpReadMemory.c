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
typedef  scalar_t__ ULONG_PTR ;

/* Variables and functions */
 int KdbpSafeReadMemory (unsigned char*,void*,unsigned int) ; 

__attribute__((used)) static int
KdbpReadMemory(ULONG_PTR Addr, unsigned char* Data, unsigned int Length,
	       struct disassemble_info * Ignored)
{
  return KdbpSafeReadMemory(Data, (void *)Addr, Length); /* 0 means no error */
}