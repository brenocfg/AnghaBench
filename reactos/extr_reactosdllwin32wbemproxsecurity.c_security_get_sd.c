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
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CIM_FLAG_ARRAY ; 
 int CIM_UINT32 ; 
 int CIM_UINT8 ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_SpawnInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PARAM_OUT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_systemsecurityW ; 
 int /*<<< orphan*/  create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_sd (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  method_getsdW ; 
 int /*<<< orphan*/  param_returnvalueW ; 
 int /*<<< orphan*/  param_sdW ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_byte_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT security_get_sd( IWbemClassObject *obj, IWbemClassObject *in, IWbemClassObject **out )
{
    VARIANT var_sd, retval;
    IWbemClassObject *sig, *out_params = NULL;
    HRESULT hr, ret;
    SECURITY_DESCRIPTOR *sd;
    DWORD sd_size;

    TRACE("%p, %p\n", in, out);

    hr = create_signature( class_systemsecurityW, method_getsdW, PARAM_OUT, &sig );

    if (SUCCEEDED(hr))
    {
        hr = IWbemClassObject_SpawnInstance( sig, 0, &out_params );

        IWbemClassObject_Release( sig );
    }

    if (SUCCEEDED(hr))
    {
        ret = get_sd( &sd, &sd_size );

        if (SUCCEEDED(ret))
        {
            VariantInit( &var_sd );

            hr = to_byte_array( sd, sd_size, &var_sd );

            if (SUCCEEDED(hr))
                hr = IWbemClassObject_Put( out_params, param_sdW, 0, &var_sd, CIM_UINT8|CIM_FLAG_ARRAY );

            HeapFree( GetProcessHeap(), 0, sd );
            VariantClear( &var_sd );
        }

        if (SUCCEEDED(hr))
        {
            set_variant( VT_UI4, ret, NULL, &retval );
            hr = IWbemClassObject_Put( out_params, param_returnvalueW, 0, &retval, CIM_UINT32 );
        }

        if (SUCCEEDED(hr) && out)
        {
            *out = out_params;
            IWbemClassObject_AddRef( out_params );
        }

        IWbemClassObject_Release( out_params );
    }

    return hr;
}