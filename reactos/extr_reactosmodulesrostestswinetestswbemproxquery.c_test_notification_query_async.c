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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IWbemServices_CancelAsyncCall (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_ExecNotificationQueryAsync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ WBEM_E_INVALID_PARAMETER ; 
 scalar_t__ WBEM_E_NOT_FOUND ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sink ; 
 scalar_t__ sink_refs ; 
 char const* wqlW ; 

__attribute__((used)) static void test_notification_query_async( IWbemServices *services )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'D','e','v','i','c','e','C','h','a','n','g','e','E','v','e','n','t',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    ULONG prev_sink_refs;
    HRESULT hr;

    hr = IWbemServices_ExecNotificationQueryAsync( services, wql, query, 0, NULL, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    prev_sink_refs = sink_refs;
    hr = IWbemServices_ExecNotificationQueryAsync( services, wql, query, 0, NULL, &sink );
    ok( hr == S_OK || broken(hr == WBEM_E_NOT_FOUND), "got %08x\n", hr );
    ok( sink_refs > prev_sink_refs || broken(!sink_refs), "got %u refs\n", sink_refs );

    hr =  IWbemServices_CancelAsyncCall( services, &sink );
    ok( hr == S_OK || broken(hr == WBEM_E_NOT_FOUND), "got %08x\n", hr );

    SysFreeString( wql );
    SysFreeString( query );
}