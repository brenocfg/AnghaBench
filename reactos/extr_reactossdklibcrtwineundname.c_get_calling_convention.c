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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int UNDNAME_NO_ALLOCATION_LANGUAGE ; 
 unsigned int UNDNAME_NO_LEADING_UNDERSCORES ; 
 unsigned int UNDNAME_NO_MS_KEYWORDS ; 

__attribute__((used)) static BOOL get_calling_convention(char ch, const char** call_conv,
                                   const char** exported, unsigned flags)
{
    *call_conv = *exported = NULL;

    if (!(flags & (UNDNAME_NO_MS_KEYWORDS | UNDNAME_NO_ALLOCATION_LANGUAGE)))
    {
        if (flags & UNDNAME_NO_LEADING_UNDERSCORES)
        {
            if (((ch - 'A') % 2) == 1) *exported = "dll_export ";
            switch (ch)
            {
            case 'A': case 'B': *call_conv = "cdecl"; break;
            case 'C': case 'D': *call_conv = "pascal"; break;
            case 'E': case 'F': *call_conv = "thiscall"; break;
            case 'G': case 'H': *call_conv = "stdcall"; break;
            case 'I': case 'J': *call_conv = "fastcall"; break;
            case 'K': case 'L': break;
            case 'M': *call_conv = "clrcall"; break;
            default: ERR("Unknown calling convention %c\n", ch); return FALSE;
            }
        }
        else
        {
            if (((ch - 'A') % 2) == 1) *exported = "__dll_export ";
            switch (ch)
            {
            case 'A': case 'B': *call_conv = "__cdecl"; break;
            case 'C': case 'D': *call_conv = "__pascal"; break;
            case 'E': case 'F': *call_conv = "__thiscall"; break;
            case 'G': case 'H': *call_conv = "__stdcall"; break;
            case 'I': case 'J': *call_conv = "__fastcall"; break;
            case 'K': case 'L': break;
            case 'M': *call_conv = "__clrcall"; break;
            default: ERR("Unknown calling convention %c\n", ch); return FALSE;
            }
        }
    }
    return TRUE;
}