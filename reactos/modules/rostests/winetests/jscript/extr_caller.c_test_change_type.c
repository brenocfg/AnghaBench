#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float int_result; float str_result; scalar_t__ bool_result; scalar_t__ double_result; scalar_t__ test_double; } ;
typedef  TYPE_1__ conv_results_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  IVariantChangeType ;
typedef  float INT16 ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ VT_BOOL ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__ VT_EMPTY ; 
 scalar_t__ VT_I2 ; 
 scalar_t__ VT_I4 ; 
 scalar_t__ VT_NULL ; 
 scalar_t__ VT_R4 ; 
 scalar_t__ VT_R8 ; 
 scalar_t__ VT_UI2 ; 
 float V_BOOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 float V_I2 (int /*<<< orphan*/ *) ; 
 float V_I4 (int /*<<< orphan*/ *) ; 
 float V_R4 (int /*<<< orphan*/ *) ; 
 float V_R8 (int /*<<< orphan*/ *) ; 
 float V_UI2 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_change_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  change_type_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,float,float) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,float) ; 
 float wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_change_type(IVariantChangeType *change_type, VARIANT *src, const conv_results_t *ex)
{
    VARIANT v;

    call_change_type(change_type, &v, src, VT_I4);
    ok(V_I4(&v) == ex->int_result, "V_I4(v) = %d, expected %d\n", V_I4(&v), ex->int_result);

    call_change_type(change_type, &v, src, VT_UI2);
    ok(V_UI2(&v) == (UINT16)ex->int_result, "V_UI2(v) = %u, expected %u\n", V_UI2(&v), (UINT16)ex->int_result);

    call_change_type(change_type, &v, src, VT_BSTR);
    ok(!strcmp_wa(V_BSTR(&v), ex->str_result), "V_BSTR(v) = %s, expected %s\n", wine_dbgstr_w(V_BSTR(&v)), ex->str_result);
    VariantClear(&v);

    call_change_type(change_type, &v, src, VT_BOOL);
    ok(V_BOOL(&v) == ex->bool_result, "V_BOOL(v) = %x, expected %x\n", V_BOOL(&v), ex->bool_result);

    if(ex->test_double) {
        call_change_type(change_type, &v, src, VT_R8);
        ok(V_R8(&v) == ex->double_result, "V_R8(v) = %lf, expected %lf\n", V_R8(&v), ex->double_result);

        call_change_type(change_type, &v, src, VT_R4);
        ok(V_R4(&v) == (float)ex->double_result, "V_R4(v) = %f, expected %f\n", V_R4(&v), (float)ex->double_result);
    }

    if(V_VT(src) == VT_NULL)
        call_change_type(change_type, &v, src, VT_NULL);
    else
        change_type_fail(change_type, src, VT_NULL, E_NOTIMPL);

    if(V_VT(src) == VT_EMPTY)
        call_change_type(change_type, &v, src, VT_EMPTY);
    else
        change_type_fail(change_type, src, VT_EMPTY, E_NOTIMPL);

    call_change_type(change_type, &v, src, VT_I2);
    ok(V_I2(&v) == (INT16)ex->int_result, "V_I2(v) = %d, expected %d\n", V_I2(&v), ex->int_result);
}