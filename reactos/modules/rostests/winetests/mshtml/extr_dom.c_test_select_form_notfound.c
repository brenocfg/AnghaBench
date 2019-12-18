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
typedef  int /*<<< orphan*/  IHTMLFormElement ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLSelectElement_get_form (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_select_form_notfound(IHTMLSelectElement *select)
{
    IHTMLFormElement *form;
    HRESULT hres;

    form = (IHTMLFormElement*)0xdeadbeef;
    hres = IHTMLSelectElement_get_form(select, &form);
    ok(hres == S_OK, "get_form failed: %08x\n", hres);
    ok(form == NULL, "got %p\n", form);
}