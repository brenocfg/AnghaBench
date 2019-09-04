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
typedef  scalar_t__ (* iterate_fields_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextMatchLineW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_field_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT iterate_section_fields(HINF hinf, PCWSTR section, PCWSTR key,
                                      iterate_fields_func callback, void *arg)
{
    WCHAR static_buffer[200];
    WCHAR *buffer = static_buffer;
    DWORD size = ARRAY_SIZE(static_buffer);
    INFCONTEXT context;
    HRESULT hr = E_FAIL;

    BOOL ok = SetupFindFirstLineW(hinf, section, key, &context);
    while (ok)
    {
        UINT i, count = SetupGetFieldCount(&context);

        for (i = 1; i <= count; i++)
        {
            if (!(buffer = get_field_string(&context, i, buffer, static_buffer, &size)))
                goto done;

            if ((hr = callback(hinf, buffer, arg)) != S_OK)
                goto done;
        }

        ok = SetupFindNextMatchLineW(&context, key, &context);
    }

    hr = S_OK;

 done:
    if (buffer != static_buffer) HeapFree(GetProcessHeap(), 0, buffer);
    return hr;
}