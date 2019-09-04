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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CIM_UINT32 ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_SpawnInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PARAM_OUT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  class_systemsecurityW ; 
 int /*<<< orphan*/  create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  method_setsdW ; 
 int /*<<< orphan*/  param_returnvalueW ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT security_set_sd( IWbemClassObject *obj, IWbemClassObject *in, IWbemClassObject **out )
{
    VARIANT retval;
    IWbemClassObject *sig, *out_params = NULL;
    HRESULT hr;

    FIXME("stub\n");

    hr = create_signature( class_systemsecurityW, method_setsdW, PARAM_OUT, &sig );

    if (SUCCEEDED(hr))
    {
        hr = IWbemClassObject_SpawnInstance( sig, 0, &out_params );

        IWbemClassObject_Release( sig );
    }

    if (SUCCEEDED(hr))
    {
        set_variant( VT_UI4, S_OK, NULL, &retval );
        hr = IWbemClassObject_Put( out_params, param_returnvalueW, 0, &retval, CIM_UINT32 );

        if (SUCCEEDED(hr) && out)
        {
            *out = out_params;
            IWbemClassObject_AddRef( out_params );
        }

        IWbemClassObject_Release( out_params );
    }

    return hr;
}