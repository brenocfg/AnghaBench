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
typedef  int /*<<< orphan*/  VARIANTARG ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  unsigned int HRESULT ;
typedef  int /*<<< orphan*/  DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_VARARG (int /*<<< orphan*/ *) ; 
 unsigned int DISP_E_BADVARTYPE ; 
 unsigned int DISP_E_OVERFLOW ; 
 unsigned int DISP_E_PARAMNOTFOUND ; 
 unsigned int DISP_E_TYPEMISMATCH ; 
 unsigned int DispGetParam (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,unsigned int*) ; 
 unsigned int E_INVALIDARG ; 
 int /*<<< orphan*/  INIT_DISPPARAMS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_VARARG (int /*<<< orphan*/ *) ; 
 unsigned int S_OK ; 
 unsigned int VT_BSTR ; 
 unsigned int VT_EMPTY ; 
 unsigned int VT_I2 ; 
 unsigned int VT_I4 ; 
 unsigned int VT_ILLEGAL ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 unsigned int V_I2 (int /*<<< orphan*/ *) ; 
 unsigned int V_I4 (int /*<<< orphan*/ *) ; 
 unsigned int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int) ; 
 int /*<<< orphan*/  ok_bstr (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void test_DispGetParam(void)
{
    HRESULT hr;
    DISPPARAMS dispparams;
    VARIANTARG vararg[3];
    VARIANT result;
    unsigned int err_index;

    VariantInit(&result);

    /* DispGetParam crashes on Windows if pdispparams is NULL. */

    /* pdispparams has zero parameters. */
    INIT_DISPPARAMS(dispparams, NULL, NULL, 0, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_I2, &result, &err_index);
    ok(hr == DISP_E_PARAMNOTFOUND,
       "Expected DISP_E_PARAMNOTFOUND, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* pdispparams has zero parameters, position is invalid. */
    INIT_DISPPARAMS(dispparams, NULL, NULL, 0, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 1, VT_I2, &result, &err_index);
    ok(hr == DISP_E_PARAMNOTFOUND,
       "Expected DISP_E_PARAMNOTFOUND, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* pdispparams has zero parameters, pvarResult is NULL. */
    INIT_DISPPARAMS(dispparams, NULL, NULL, 0, 0);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_I2, NULL, &err_index);
    ok(hr == DISP_E_PARAMNOTFOUND,
       "Expected DISP_E_PARAMNOTFOUND, got %08x\n", hr);
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* pdispparams has zero parameters, puArgErr is NULL. */
    INIT_DISPPARAMS(dispparams, NULL, NULL, 0, 0);
    VariantInit(&result);
    hr = DispGetParam(&dispparams, 0, VT_I2, &result, NULL);
    ok(hr == DISP_E_PARAMNOTFOUND,
       "Expected DISP_E_PARAMNOTFOUND, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));

    /* pdispparams.cArgs is 1, yet pdispparams.rgvarg is NULL. */
    INIT_DISPPARAMS(dispparams, NULL, NULL, 1, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_I2, &result, &err_index);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 0, "Expected 0, got %d\n", err_index);

    /* pdispparams.cNamedArgs is 1, yet pdispparams.rgdispidNamedArgs is NULL.
     *
     * This crashes on Windows.
     */

    /* {42, 1234567890, "Sunshine"} */
    INIT_VARARG(vararg);

    /* Get the first param.  position is end-based, so 2 is the first parameter
     * of 3 parameters.
     */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 2, VT_I2, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_I2, "Expected VT_I2, got %08x\n", V_VT(&result));
    ok(V_I2(&result) == 42, "Expected 42, got %d\n", V_I2(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* Get the second param. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 1, VT_I4, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_I4, "Expected VT_I4, got %08x\n", V_VT(&result));
    ok(V_I4(&result) == 1234567890,
       "Expected 1234567890, got %d\n", V_I4(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* Get the third param. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_BSTR, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_BSTR, "Expected VT_BSTR, got %08x\n", V_VT(&result));
    ok_bstr(V_BSTR(&result), "Sunshine", "Expected %s, got %s\n");
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);
    VariantClear(&result);

    /* position is out of range. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 3, VT_I2, &result, &err_index);
    ok(hr == DISP_E_PARAMNOTFOUND,
       "Expected DISP_E_PARAMNOTFOUND, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* pvarResult is NULL. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 2, VT_I2, NULL, &err_index);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    ok(err_index == 0, "Expected 0, got %d\n", err_index);

    /* puArgErr is NULL. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    hr = DispGetParam(&dispparams, 2, VT_I2, &result, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_I2, "Expected VT_I2, got %08x\n", V_VT(&result));
    ok(V_I2(&result) == 42, "Expected 42, got %d\n", V_I2(&result));

    /* Coerce the first param to VT_I4. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 2, VT_I4, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_I4, "Expected VT_I4, got %08x\n", V_VT(&result));
    ok(V_I4(&result) == 42, "Expected 42, got %d\n", V_I4(&result));
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);

    /* Coerce the first param to VT_BSTR. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 2, VT_BSTR, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_BSTR, "Expected VT_BSTR, got %08x\n", V_VT(&result));
    ok_bstr(V_BSTR(&result), "42", "Expected %s, got %s\n");
    ok(err_index == 0xdeadbeef,
       "Expected err_index to be unchanged, got %d\n", err_index);
    VariantClear(&result);

    /* Coerce the second (VT_I4) param to VT_I2. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 1, VT_I2, &result, &err_index);
    ok(hr == DISP_E_OVERFLOW, "Expected DISP_E_OVERFLOW, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 1, "Expected 1, got %d\n", err_index);

    /* Coerce the third (VT_BSTR) param to VT_I2. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_I2, &result, &err_index);
    ok(hr == DISP_E_TYPEMISMATCH,
       "Expected DISP_E_TYPEMISMATCH, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 2, "Expected 2, got %d\n", err_index);

    /* Coerce the first parameter to an invalid type. */
    INIT_DISPPARAMS(dispparams, vararg, NULL, 3, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 2, VT_ILLEGAL, &result, &err_index);
    ok(hr == DISP_E_BADVARTYPE, "Expected DISP_E_BADVARTYPE, got %08x\n", hr);
    ok(V_VT(&result) == VT_EMPTY,
       "Expected VT_EMPTY, got %08x\n", V_VT(&result));
    ok(err_index == 0, "Expected 0, got %d\n", err_index);

    CLEAR_VARARG(vararg);

    /* Coerce the first parameter, which is of type VT_EMPTY, to VT_BSTR. */
    VariantInit(&vararg[0]);
    INIT_DISPPARAMS(dispparams, vararg, NULL, 1, 0);
    VariantInit(&result);
    err_index = 0xdeadbeef;
    hr = DispGetParam(&dispparams, 0, VT_BSTR, &result, &err_index);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(V_VT(&result) == VT_BSTR, "Expected VT_BSTR, got %08x\n", V_VT(&result));
    ok(err_index == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", err_index);
    VariantClear(&result);
}