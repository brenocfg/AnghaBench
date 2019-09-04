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
typedef  int /*<<< orphan*/  PSP_INF_INFORMATION ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupQueryInfFileInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcmpiA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_info_filename(PSP_INF_INFORMATION info, LPSTR test)
{
    LPSTR filename;
    DWORD size;
    BOOL ret = FALSE;

    if (!SetupQueryInfFileInformationA(info, 0, NULL, 0, &size))
        return FALSE;

    filename = HeapAlloc(GetProcessHeap(), 0, size);
    if (!filename)
        return FALSE;

    SetupQueryInfFileInformationA(info, 0, filename, size, &size);

    if (!lstrcmpiA(test, filename))
        ret = TRUE;

    HeapFree(GetProcessHeap(), 0, filename);
    return ret;
}