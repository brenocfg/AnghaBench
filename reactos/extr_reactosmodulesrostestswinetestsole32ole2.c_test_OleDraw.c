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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ OleDraw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  viewobject ; 

__attribute__((used)) static void test_OleDraw(void)
{
    HRESULT hr;
    RECT rect;

    hr = OleDraw((IUnknown*)&viewobject, 0, (HDC)0x1, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = OleDraw(NULL, 0, (HDC)0x1, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = OleDraw(NULL, 0, (HDC)0x1, &rect);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
}