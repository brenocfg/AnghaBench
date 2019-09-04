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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/  HDEVINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOem (scalar_t__*,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SPDRP_DEVICEDESC ; 
 int /*<<< orphan*/  SPDRP_HARDWAREID ; 
 int ST_DEV_NOTWORK ; 
 int ST_ERROR ; 
 int ST_NEUTRAL ; 
 int ST_ROS_CRASH ; 
 int /*<<< orphan*/  SetupDiGetDeviceRegistryProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (scalar_t__*,char*) ; 
 scalar_t__ _wcsnicmp (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/ * gl_report ; 
 int hw_check_base (scalar_t__*,scalar_t__*) ; 
 scalar_t__ is_check_hw ; 
 scalar_t__ is_show_hw ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  trim (scalar_t__*) ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * wcschr (scalar_t__*,int) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 
 int /*<<< orphan*/  wsprintf (scalar_t__*,char*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int hw_check_device(HDEVINFO h_info, SP_DEVINFO_DATA *d_inf)
{
	wchar_t *hw_id   = NULL;
	wchar_t *hw_name = NULL;
	u_long   type, bytes;
	int      status;
	char     name[MAX_PATH];
	wchar_t  w_name[MAX_PATH];
	
	do
	{
		if ( (hw_id = malloc(4096)) == NULL ) {
			status = ST_ERROR; break;
		}
		if ( (hw_name = malloc(4096)) == NULL ) {
			status = ST_ERROR; break;
		}
		hw_id[0] = 0, hw_name[0] = 0;

		SetupDiGetDeviceRegistryProperty(h_info, d_inf, SPDRP_HARDWAREID, &type, (void*)hw_id, 4096, &bytes);
		SetupDiGetDeviceRegistryProperty(h_info, d_inf, SPDRP_DEVICEDESC, &type, (void*)hw_name, 4096, &bytes);

		if (hw_id[0] == 0 || hw_name[0] == 0) {
			status = ST_NEUTRAL; break;
		}	
		/* trim strings */
		trim(hw_id); trim(hw_name);

		if ( (wcschr(hw_id, L'\\') == NULL) || (_wcsnicmp(hw_id, L"ROOT\\", 5) == 0) ||
			 (_wcsicmp(hw_id, L"STORAGE\\Volume") == 0) || (_wcsicmp(hw_id, L"UMB\\UMBUS") == 0) ||
			 (_wcsnicmp(hw_id, L"SW\\", 3) == 0) )
		{
			status = ST_NEUTRAL; break;
		}

		if (is_show_hw != 0) {
			CharToOem(hw_name, name);
			wprintf(L"%s - [%S]\n", hw_id, name);
		}

		if (gl_report != NULL) {
			wsprintf(w_name, L"%s - [%s]\n", hw_id, hw_name);
			wcscat(gl_report, w_name);
		}

		if (is_check_hw != 0) 
		{
			status = hw_check_base(hw_id, hw_name);

			if (status == ST_DEV_NOTWORK) {
				CharToOem(hw_name, name);
				wprintf(L"Device \"%S\" does not work in ReactOS\n", name);
			}
			if (status == ST_ROS_CRASH) {
				CharToOem(hw_name, name);
				wprintf(L"ReactOS does not work with device \"%S\"\n", name);
			}			
		} else {
			status = ST_NEUTRAL;
		}
	} while (0);

	if (hw_id != NULL) free(hw_id);
	if (hw_name != NULL) free(hw_name);

	return status;
}