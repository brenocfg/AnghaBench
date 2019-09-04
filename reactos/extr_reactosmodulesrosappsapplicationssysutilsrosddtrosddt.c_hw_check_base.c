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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int MAX_PATH ; 
 int ST_NEUTRAL ; 
 int hw_check_ini (scalar_t__*) ; 
 int /*<<< orphan*/  wcscat (scalar_t__*,scalar_t__*) ; 
 scalar_t__ wcsncmp (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  wcsncpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* wcsstr (scalar_t__*,char*) ; 
 int /*<<< orphan*/  wsprintf (scalar_t__*,char*,scalar_t__*) ; 

__attribute__((used)) static int hw_check_base(wchar_t *hw_id, wchar_t *hw_name)
{
	wchar_t buff[MAX_PATH];
    wchar_t *p = NULL;
	int     status;

	if ( (status = hw_check_ini(hw_id)) != ST_NEUTRAL ) {
		return status;
	}
	if ( (status = hw_check_ini(hw_name)) != ST_NEUTRAL ) {
		return status;
	}

	if (wcsncmp(hw_id, L"PCI\\VEN_", 8) == 0)
	{
		wcsncpy(buff, hw_id, 21); buff[21] = 0;

		if ( (status = hw_check_ini(buff)) != ST_NEUTRAL ) {
			return status;
		}

		if (p == wcsstr(hw_id, L"&REV_")) {
			wcscat(buff, p); status = hw_check_ini(buff);
		}
	} else if ( (wcsncmp(hw_id, L"USB\\", 4) == 0) && (p = wcsstr(hw_id, L"&VID")) )
	{
		wsprintf(buff, L"USB\\%s", p+1);
		
		if ( (status = hw_check_ini(buff)) != ST_NEUTRAL ) {
			return status;
		}

		if (p == wcsstr(buff, L"&REV")) {
			*p = 0; status = hw_check_ini(buff);
		}
	}
	return status;
}