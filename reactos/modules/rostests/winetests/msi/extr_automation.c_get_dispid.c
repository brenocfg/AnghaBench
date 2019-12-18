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
typedef  int UINT ;
typedef  int /*<<< orphan*/ * LPOLESTR ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IID_NULL ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static DISPID get_dispid( IDispatch *disp, const char *name )
{
    LPOLESTR str;
    UINT len;
    DISPID id = -1;
    HRESULT r;

    len = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0 );
    str = HeapAlloc(GetProcessHeap(), 0, len*sizeof(WCHAR) );
    if (str)
    {
        MultiByteToWideChar(CP_ACP, 0, name, -1, str, len );
        r = IDispatch_GetIDsOfNames( disp, &IID_NULL, &str, 1, 0, &id );
        HeapFree(GetProcessHeap(), 0, str);
        if (r != S_OK)
            return -1;
    }

    return id;
}