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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_ExecQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 char const* V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int WBEM_FLAG_FORWARD_ONLY ; 
 int WBEM_FLAG_RETURN_IMMEDIATELY ; 
 scalar_t__ WBEM_S_NO_ERROR ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char const*) ; 
 char const* wqlW ; 

__attribute__((used)) static HRESULT exec_query( IWbemServices *services, const WCHAR *str, IEnumWbemClassObject **result )
{
    static const WCHAR captionW[] = {'C','a','p','t','i','o','n',0};
    static const WCHAR descriptionW[] = {'D','e','s','c','r','i','p','t','i','o','n',0};
    HRESULT hr;
    IWbemClassObject *obj;
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( str );
    LONG flags = WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY;
    ULONG count;

    hr = IWbemServices_ExecQuery( services, wql, query, flags, NULL, result );
    if (hr == S_OK)
    {
        trace("%s\n", wine_dbgstr_w(str));
        for (;;)
        {
            VARIANT var;

            IEnumWbemClassObject_Next( *result, 10000, 1, &obj, &count );
            if (!count) break;

            if (IWbemClassObject_Get( obj, captionW, 0, &var, NULL, NULL ) == WBEM_S_NO_ERROR)
            {
                trace("caption: %s\n", wine_dbgstr_w(V_BSTR(&var)));
                VariantClear( &var );
            }
            if (IWbemClassObject_Get( obj, descriptionW, 0, &var, NULL, NULL ) == WBEM_S_NO_ERROR)
            {
                trace("description: %s\n", wine_dbgstr_w(V_BSTR(&var)));
                VariantClear( &var );
            }
            IWbemClassObject_Release( obj );
        }
    }
    SysFreeString( wql );
    SysFreeString( query );
    return hr;
}