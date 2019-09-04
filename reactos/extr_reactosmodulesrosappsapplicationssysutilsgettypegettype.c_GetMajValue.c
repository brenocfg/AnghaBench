#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dwMajorVersion; int dwMinorVersion; } ;
struct TYPE_5__ {int sv102_version_major; int sv102_version_minor; } ;
typedef  TYPE_1__* LPSERVER_INFO_102 ;
typedef  TYPE_2__* LPOSVERSIONINFOEX ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */

INT
GetMajValue(BOOL Major, BOOL bLocal, LPOSVERSIONINFOEX osvi, LPSERVER_INFO_102 pBuf102)
{
	INT VersionNumber = 255;
	if(pBuf102 != NULL && !bLocal)
	{
		if(Major)
			VersionNumber = pBuf102->sv102_version_major * 1000;
		else
			VersionNumber = pBuf102->sv102_version_minor * 100;
	}
	else
	{
		if(Major)
			VersionNumber = osvi->dwMajorVersion * 1000;
		else
			VersionNumber = osvi->dwMinorVersion * 100;
	}
	return VersionNumber;
}