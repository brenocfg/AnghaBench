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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ CIMTYPE ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ CIM_STRING ; 
 scalar_t__ IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_CreateInstanceEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 scalar_t__ WBEM_S_FALSE ; 
 scalar_t__ WBEM_S_NO_ERROR ; 
 scalar_t__ WBEM_S_TIMEDOUT ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void test_Win32_PnPEntity( IWbemServices *services )
{
    HRESULT hr;
    IEnumWbemClassObject *enm;
    IWbemClassObject *obj;
    VARIANT val;
    CIMTYPE type;
    ULONG count, i;
    BSTR bstr;

    static WCHAR win32_pnpentityW[] = {'W','i','n','3','2','_','P','n','P','E','n','t','i','t','y',0};
    static const WCHAR deviceidW[] = {'D','e','v','i','c','e','I','d',0};

    bstr = SysAllocString( win32_pnpentityW );

    hr = IWbemServices_CreateInstanceEnum( services, bstr, 0, NULL, &enm );
    ok( hr == S_OK, "got %08x\n", hr );

    SysFreeString( bstr );
    bstr = SysAllocString( deviceidW );

    while (1)
    {
        hr = IEnumWbemClassObject_Next( enm, 1000, 1, &obj, &count );
        ok( (count == 1 && (hr == WBEM_S_FALSE || hr == WBEM_S_NO_ERROR)) ||
                (count == 0 && (hr == WBEM_S_FALSE || hr == WBEM_S_TIMEDOUT)),
                "got %08x with %u objects returned\n", hr, count );

        if (count == 0)
            break;

        for (i = 0; i < count; ++i)
        {
            hr = IWbemClassObject_Get( obj, bstr, 0, &val, &type, NULL );
            ok( hr == S_OK, "got %08x\n", hr );

            if (SUCCEEDED( hr ))
            {
                ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
                ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
                VariantClear( &val );
            }
        }
    }

    SysFreeString( bstr );

    IEnumWbemClassObject_Release( enm );
}