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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IWbemServices_CancelAsyncCall (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_ExecQueryAsync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ WBEM_E_INVALID_PARAMETER ; 
 scalar_t__ WBEM_E_NOT_FOUND ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sink ; 
 char const* wqlW ; 

__attribute__((used)) static void test_query_async( IWbemServices *services )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'P','r','o','c','e','s','s',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    HRESULT hr;

    hr = IWbemServices_ExecQueryAsync( services, wql, query, 0, NULL, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    hr = IWbemServices_ExecQueryAsync( services, wql, query, 0, NULL, &sink );
    ok( hr == S_OK || broken(hr == WBEM_E_NOT_FOUND), "got %08x\n", hr );

    hr =  IWbemServices_CancelAsyncCall( services, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    hr =  IWbemServices_CancelAsyncCall( services, &sink );
    ok( hr == S_OK, "got %08x\n", hr );

    SysFreeString( wql );
    SysFreeString( query );
}