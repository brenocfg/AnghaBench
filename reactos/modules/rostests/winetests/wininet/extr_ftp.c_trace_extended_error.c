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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INTERNET_EXTENDED_ERROR ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InternetGetLastResponseInfoA (scalar_t__*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,char*) ; 

__attribute__((used)) static void trace_extended_error(DWORD error)
{
    DWORD code, buflen = 0;

    if (error != ERROR_INTERNET_EXTENDED_ERROR) return;
    if (!InternetGetLastResponseInfoA(&code, NULL, &buflen) && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        char *text = HeapAlloc(GetProcessHeap(), 0, ++buflen);
        InternetGetLastResponseInfoA(&code, text, &buflen);
        trace("%u %s\n", code, text);
        HeapFree(GetProcessHeap(), 0, text);
    }
}