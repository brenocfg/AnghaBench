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
typedef  scalar_t__ INT_PTR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int CIM_FLAG_ARRAY ; 
 int CIM_SINT32 ; 
 int CIM_STRING ; 
 int CIM_UINT32 ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_Put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemClassObject_SpawnInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PARAM_OUT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_I4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_stdregprovW ; 
 scalar_t__ create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ enum_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  method_enumvaluesW ; 
 int /*<<< orphan*/  param_defkeyW ; 
 int /*<<< orphan*/  param_namesW ; 
 int /*<<< orphan*/  param_returnvalueW ; 
 int /*<<< orphan*/  param_subkeynameW ; 
 int /*<<< orphan*/  param_typesW ; 

HRESULT reg_enum_values( IWbemClassObject *obj, IWbemClassObject *in, IWbemClassObject **out )
{
    VARIANT defkey, subkey, names, types, retval;
    IWbemClassObject *sig, *out_params = NULL;
    HRESULT hr;

    TRACE("%p, %p\n", in, out);

    hr = IWbemClassObject_Get( in, param_defkeyW, 0, &defkey, NULL, NULL );
    if (hr != S_OK) return hr;
    hr = IWbemClassObject_Get( in, param_subkeynameW, 0, &subkey, NULL, NULL );
    if (hr != S_OK) return hr;

    hr = create_signature( class_stdregprovW, method_enumvaluesW, PARAM_OUT, &sig );
    if (hr != S_OK)
    {
        VariantClear( &subkey );
        return hr;
    }
    if (out)
    {
        hr = IWbemClassObject_SpawnInstance( sig, 0, &out_params );
        if (hr != S_OK)
        {
            VariantClear( &subkey );
            IWbemClassObject_Release( sig );
            return hr;
        }
    }
    VariantInit( &names );
    VariantInit( &types );
    hr = enum_values( (HKEY)(INT_PTR)V_I4(&defkey), V_BSTR(&subkey), &names, &types, &retval );
    if (hr != S_OK) goto done;
    if (out_params)
    {
        if (!V_UI4( &retval ))
        {
            hr = IWbemClassObject_Put( out_params, param_namesW, 0, &names, CIM_STRING|CIM_FLAG_ARRAY );
            if (hr != S_OK) goto done;
            hr = IWbemClassObject_Put( out_params, param_typesW, 0, &types, CIM_SINT32|CIM_FLAG_ARRAY );
            if (hr != S_OK) goto done;
        }
        hr = IWbemClassObject_Put( out_params, param_returnvalueW, 0, &retval, CIM_UINT32 );
    }

done:
    VariantClear( &types );
    VariantClear( &names );
    VariantClear( &subkey );
    IWbemClassObject_Release( sig );
    if (hr == S_OK && out)
    {
        *out = out_params;
        IWbemClassObject_AddRef( out_params );
    }
    if (out_params) IWbemClassObject_Release( out_params );
    return hr;
}