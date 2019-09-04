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
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int /*<<< orphan*/  IWidget ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IWidget_safearray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_safearray (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * make_safearray (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_marshal_safearray(IWidget *widget, IDispatch *disp)
{
    SAFEARRAY *in, *out, *out2, *in_ptr, *in_out;
    HRESULT hr;

    in = make_safearray(3);
    out = out2 = make_safearray(5);
    in_ptr = make_safearray(7);
    in_out = make_safearray(9);
    hr = IWidget_safearray(widget, in, &out, &in_ptr, &in_out);
    ok(hr == S_OK, "Got hr %#x.\n", hr);
    check_safearray(in, 3);
    check_safearray(out, 4);
    check_safearray(out2, 5);
    check_safearray(in_ptr, 7);
    check_safearray(in_out, 6);

    SafeArrayDestroy(in);
    SafeArrayDestroy(out);
    SafeArrayDestroy(out2);
    SafeArrayDestroy(in_ptr);
    SafeArrayDestroy(in_out);
}