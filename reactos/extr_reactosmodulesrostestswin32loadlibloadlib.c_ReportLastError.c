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
typedef  int /*<<< orphan*/ * PSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 scalar_t__ FormatMessageA (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  dprintf (char*,scalar_t__,...) ; 

DWORD ReportLastError(void)
{
    DWORD dwError = GetLastError();
    if (dwError != ERROR_SUCCESS) {
        PSTR msg = NULL;
        if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
            0, dwError, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT), (PSTR)&msg, 0, NULL)) {
            if (msg != NULL) {
                dprintf("ReportLastError() %d - %s\n", dwError, msg);
            } else {
                dprintf("ERROR: ReportLastError() %d - returned TRUE but with no msg string!\n", dwError);
            }
        } else {
            dprintf("ReportLastError() %d - unknown error\n", dwError);
        }
        if (msg != NULL) {
            LocalFree(msg);
        }
    }
    return dwError;
}