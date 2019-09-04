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
typedef  int /*<<< orphan*/  PSID ;
typedef  char* LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidA (int /*<<< orphan*/ ,char**) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 size_t SID_SLOTS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 size_t debugsid_index ; 
 char** debugsid_str ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char* debugstr_sid(PSID sid)
{
    LPSTR sidstr;
    DWORD le = GetLastError();
    char* res = debugsid_str[debugsid_index];
    debugsid_index = (debugsid_index + 1) % SID_SLOTS;

    if (!ConvertSidToStringSidA(sid, &sidstr))
        sprintf(res, "ConvertSidToStringSidA failed le=%u", GetLastError());
    else if (strlen(sidstr) > sizeof(*debugsid_str) - 1)
    {
        memcpy(res, sidstr, sizeof(*debugsid_str) - 4);
        strcpy(res + sizeof(*debugsid_str) - 4, "...");
        LocalFree(sidstr);
    }
    else
    {
        strcpy(res, sidstr);
        LocalFree(sidstr);
    }
    /* Restore the last error in case ConvertSidToStringSidA() modified it */
    SetLastError(le);
    return res;
}