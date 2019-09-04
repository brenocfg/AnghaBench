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
struct TYPE_3__ {int wServicePackMajor; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPSERVER_INFO_102 ;
typedef  TYPE_1__* LPOSVERSIONINFOEX ;
typedef  int INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */

INT
GetServicePack(BOOL bLocal, LPOSVERSIONINFOEX osvi, LPSERVER_INFO_102 pBuf102, TCHAR * Server)
{
	INT SPNumber = 255;
	if(!bLocal)
	{
		/* FIXME: Use Registry to get value */
	}
	else
	{
		SPNumber = osvi->wServicePackMajor;
	}
	return SPNumber;
}