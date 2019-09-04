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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  MYSTRUCT ;
typedef  int /*<<< orphan*/  IWidget ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int EqualRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWidget_mystruct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWidget_mystruct_ptr_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IWidget_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWidget_thin_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_mystruct1 ; 
 int /*<<< orphan*/  test_mystruct2 ; 
 int /*<<< orphan*/  test_mystruct3 ; 
 int /*<<< orphan*/  test_mystruct4 ; 
 int /*<<< orphan*/  test_mystruct5 ; 
 int /*<<< orphan*/  test_mystruct7 ; 
 int /*<<< orphan*/  test_rect1 ; 
 int /*<<< orphan*/  test_rect2 ; 
 int /*<<< orphan*/  test_rect3 ; 
 int /*<<< orphan*/  test_rect4 ; 
 int /*<<< orphan*/  test_rect5 ; 
 int /*<<< orphan*/  test_rect7 ; 
 int /*<<< orphan*/  test_thin_struct ; 

__attribute__((used)) static void test_marshal_struct(IWidget *widget, IDispatch *disp)
{
    MYSTRUCT out, in_ptr, in_out, *in_ptr_ptr;
    RECT rect_out, rect_in_ptr, rect_in_out;
    HRESULT hr;

    memcpy(&out, &test_mystruct2, sizeof(MYSTRUCT));
    memcpy(&in_ptr, &test_mystruct3, sizeof(MYSTRUCT));
    memcpy(&in_out, &test_mystruct4, sizeof(MYSTRUCT));
    hr = IWidget_mystruct(widget, test_mystruct1, &out, &in_ptr, &in_out);
    ok(hr == S_OK, "Got hr %#x.\n", hr);
    ok(!memcmp(&out, &test_mystruct5, sizeof(MYSTRUCT)), "Structs didn't match.\n");
    ok(!memcmp(&in_ptr, &test_mystruct3, sizeof(MYSTRUCT)), "Structs didn't match.\n");
    ok(!memcmp(&in_out, &test_mystruct7, sizeof(MYSTRUCT)), "Structs didn't match.\n");

    memcpy(&in_ptr, &test_mystruct1, sizeof(MYSTRUCT));
    in_ptr_ptr = &in_ptr;
    hr = IWidget_mystruct_ptr_ptr(widget, &in_ptr_ptr);
    ok(hr == S_OK, "Got hr %#x.\n", hr);

    /* Make sure that "thin" structs (<=8 bytes) are handled correctly in x86-64. */

    hr = IWidget_thin_struct(widget, test_thin_struct);
    ok(hr == S_OK, "Got hr %#x.\n", hr);

    /* Make sure we can handle an imported type. */

    rect_out = test_rect2;
    rect_in_ptr = test_rect3;
    rect_in_out = test_rect4;
    hr = IWidget_rect(widget, test_rect1, &rect_out, &rect_in_ptr, &rect_in_out);
    ok(hr == S_OK, "Got hr %#x.\n", hr);
    ok(EqualRect(&rect_out, &test_rect5), "Rects didn't match.\n");
    ok(EqualRect(&rect_in_ptr, &test_rect3), "Rects didn't match.\n");
    ok(EqualRect(&rect_in_out, &test_rect7), "Rects didn't match.\n");
}