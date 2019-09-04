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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CanUserWritePwrScheme () ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void test_CanUserWritePwrScheme(void)
{
   DWORD error, retval;

   retval = CanUserWritePwrScheme();

   error = GetLastError();

   if (retval)
      ok(retval, "function failed?");
   else
      ok(error == ERROR_ACCESS_DENIED, "function last error wrong expected ERROR_ACCESS_DENIED but got %d\n", (UINT)error);

}