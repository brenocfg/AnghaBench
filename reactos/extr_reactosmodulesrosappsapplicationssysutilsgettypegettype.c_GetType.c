#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dwMajorVersion; int dwMinorVersion; int wSuiteMask; } ;
typedef  int /*<<< orphan*/  LPSERVER_INFO_102 ;
typedef  TYPE_1__* LPOSVERSIONINFOEX ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int VER_SUITE_BLADE ; 
 int VER_SUITE_DATACENTER ; 
 int VER_SUITE_ENTERPRISE ; 
 int VER_SUITE_PERSONAL ; 

INT GetType(BOOL bLocal, LPOSVERSIONINFOEX osvi, LPSERVER_INFO_102 pBuf102)
{
	if(bLocal)
	{
		if(osvi->dwMajorVersion == 5)
		{
			if(osvi->dwMinorVersion == 1)
			{
				if(osvi->wSuiteMask & VER_SUITE_PERSONAL)
					return 1;
				else
					return 2;
			}
			else if(osvi->dwMinorVersion == 2)
			{
				if(osvi->wSuiteMask & VER_SUITE_BLADE)
					return 6;
				else if(osvi->wSuiteMask & VER_SUITE_DATACENTER)
					return 5;
				else if(osvi->wSuiteMask & VER_SUITE_ENTERPRISE)
					return 4;
				else
					return 3;
			}
		}
	}
	else
	{
		/* FIXME: Get this value from registry */
	}
	return 255;
}