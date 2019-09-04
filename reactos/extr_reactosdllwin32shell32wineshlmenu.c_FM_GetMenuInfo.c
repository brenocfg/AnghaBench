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
struct TYPE_3__ {int cbSize; scalar_t__ dwMenuData; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUINFO ;
typedef  int /*<<< orphan*/ * LPFMINFO ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetMenuInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MIM_MENUDATA ; 

__attribute__((used)) static LPFMINFO FM_GetMenuInfo(HMENU hmenu)
{
	MENUINFO	MenuInfo;
	LPFMINFO	menudata;

	MenuInfo.cbSize = sizeof(MENUINFO);
	MenuInfo.fMask = MIM_MENUDATA;

	if (! GetMenuInfo(hmenu, &MenuInfo))
	  return NULL;

	menudata = (LPFMINFO)MenuInfo.dwMenuData;

	if ((menudata == 0) || (MenuInfo.cbSize != sizeof(MENUINFO)))
	{
	  ERR("menudata corrupt: %p %u\n", menudata, MenuInfo.cbSize);
	  return 0;
	}

	return menudata;

}