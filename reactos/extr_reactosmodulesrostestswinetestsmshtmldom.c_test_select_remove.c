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
typedef  int /*<<< orphan*/  IHTMLSelectElement ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ IHTMLSelectElement_remove (int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_select_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_select_remove(IHTMLSelectElement *select)
{
    HRESULT hres;

    hres = IHTMLSelectElement_remove(select, 3);
    ok(hres == S_OK, "remove failed: %08x, expected S_OK\n", hres);
    test_select_length(select, 2);

    hres = IHTMLSelectElement_remove(select, -1);
    ok(hres == E_INVALIDARG, "remove failed: %08x, expected E_INVALIDARG\n", hres);
    test_select_length(select, 2);

    hres = IHTMLSelectElement_remove(select, 0);
    ok(hres == S_OK, "remove failed:%08x\n", hres);
    test_select_length(select, 1);
}