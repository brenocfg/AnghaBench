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
typedef  int /*<<< orphan*/  unit ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  IDS_UNIT_GB ; 
 int /*<<< orphan*/  IDS_UNIT_KB ; 
 int /*<<< orphan*/  IDS_UNIT_MB ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ ,char const*,float,...) ; 

__attribute__((used)) static void format_bytes(LPWSTR buffer, LONGLONG bytes)
{
	static const WCHAR sFmtSmall[]  = {'%', 'u', 0};
	static const WCHAR sFmtBig[] = {'%', '.', '1', 'f', ' ', '%', 's', '\0'};

	if (bytes < 1024)
		sprintfW(buffer, sFmtSmall, (DWORD)bytes);
	else
	{
		WCHAR unit[64];
		UINT resid;
		float fBytes;
		if (bytes >= 1073741824)	/* 1 GB */
		{
			fBytes = ((float)bytes)/1073741824.f+.5f;
			resid = IDS_UNIT_GB;
		}
		else if (bytes >= 1048576)	/* 1 MB */
		{
			fBytes = ((float)bytes)/1048576.f+.5f;
			resid = IDS_UNIT_MB;
		}
		else /* bytes >= 1024 */	/* 1 kB */
		{
			fBytes = ((float)bytes)/1024.f+.5f;
			resid = IDS_UNIT_KB;
		}
		LoadStringW(Globals.hInstance, resid, unit, sizeof(unit)/sizeof(*unit));
		sprintfW(buffer, sFmtBig, fBytes, unit);
	}
}