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
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ADN_DEL_IF_EMPTY ; 
 scalar_t__ DelNodeW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ E_FAIL ; 
 int MAX_INF_STRING_LENGTH ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetLineTextW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT del_dirs_callback(HINF hinf, PCWSTR field, const void *arg)
{
    INFCONTEXT context;
    HRESULT hr = S_OK;
    DWORD size;

    BOOL ok = SetupFindFirstLineW(hinf, field, NULL, &context);
    
    for (; ok; ok = SetupFindNextLine(&context, &context))
    {
        WCHAR directory[MAX_INF_STRING_LENGTH];

        if (!SetupGetLineTextW(&context, NULL, NULL, NULL, directory,
                               MAX_INF_STRING_LENGTH, &size))
            continue;

        if (DelNodeW(directory, ADN_DEL_IF_EMPTY) != S_OK)
            hr = E_FAIL;
    }

    return hr;
}