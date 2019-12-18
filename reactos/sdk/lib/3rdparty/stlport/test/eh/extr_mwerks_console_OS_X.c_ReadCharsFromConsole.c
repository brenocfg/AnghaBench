#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long (* theRead ) (int /*<<< orphan*/ ,char*,long) ;} ;

/* Variables and functions */
 TYPE_1__ __msl_os_x ; 
 long read (int /*<<< orphan*/ ,char*,long) ; 
 long stub1 (int /*<<< orphan*/ ,char*,long) ; 

long ReadCharsFromConsole(char *buffer, long n)
{
#if __MACH__
  return read(0, buffer, n);
#else
  /* Call the function if it was found */
  if (__msl_os_x.theRead == NULL)
    return -1;
  else
    return __msl_os_x.theRead(0, buffer, n);
#endif
}