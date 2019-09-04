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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_STRING ; 
 int /*<<< orphan*/  CIM_UINT32 ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_SpawnInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PARAM_OUT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  V_UI4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_processW ; 
 scalar_t__ create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ get_owner (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  method_getownerW ; 
 int /*<<< orphan*/  param_domainW ; 
 int /*<<< orphan*/  param_returnvalueW ; 
 int /*<<< orphan*/  param_userW ; 

HRESULT process_get_owner( IWbemClassObject *obj, IWbemClassObject *in, IWbemClassObject **out )
{
    VARIANT user, domain, retval;
    IWbemClassObject *sig, *out_params = NULL;
    HRESULT hr;

    TRACE("%p, %p, %p\n", obj, in, out);

    hr = create_signature( class_processW, method_getownerW, PARAM_OUT, &sig );
    if (hr != S_OK) return hr;

    if (out)
    {
        hr = IWbemClassObject_SpawnInstance( sig, 0, &out_params );
        if (hr != S_OK)
        {
            IWbemClassObject_Release( sig );
            return hr;
        }
    }
    VariantInit( &user );
    VariantInit( &domain );
    hr = get_owner( &user, &domain, &retval );
    if (hr != S_OK) goto done;
    if (out_params)
    {
        if (!V_UI4( &retval ))
        {
            hr = IWbemClassObject_Put( out_params, param_userW, 0, &user, CIM_STRING );
            if (hr != S_OK) goto done;
            hr = IWbemClassObject_Put( out_params, param_domainW, 0, &domain, CIM_STRING );
            if (hr != S_OK) goto done;
        }
        hr = IWbemClassObject_Put( out_params, param_returnvalueW, 0, &retval, CIM_UINT32 );
    }

done:
    VariantClear( &user );
    VariantClear( &domain );
    IWbemClassObject_Release( sig );
    if (hr == S_OK && out)
    {
        *out = out_params;
        IWbemClassObject_AddRef( out_params );
    }
    if (out_params) IWbemClassObject_Release( out_params );
    return hr;
}