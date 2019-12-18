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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 scalar_t__ MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static BOOL is_in_strarray(const WCHAR *needle, const char *hay)
{
    WCHAR wstr[MAX_PATH];

    if(!needle && !hay)
        return TRUE;

    while(hay && *hay)
    {
        DWORD ret;

        if(strcmp(hay, "(null)") == 0 && !needle)
            return TRUE;

        ret = MultiByteToWideChar(CP_ACP, 0, hay, -1, wstr, ARRAY_SIZE(wstr));
        if(ret == 0)
        {
            ok(0, "Failed to convert string\n");
            return FALSE;
        }

        if(lstrcmpW(wstr, needle) == 0)
            return TRUE;

        hay += strlen(hay) + 1;
    }

    return FALSE;
}