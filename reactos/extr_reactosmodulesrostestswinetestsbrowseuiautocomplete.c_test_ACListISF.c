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
typedef  int /*<<< orphan*/  IEnumString ;
typedef  int /*<<< orphan*/  IACList ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC ; 
 int /*<<< orphan*/  CLSID_ACListISF ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IACList_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IACList_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumString_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IEnumString_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IACList ; 
 int /*<<< orphan*/  IID_IEnumString ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void test_ACListISF(void)
{
    IEnumString *enumstring;
    IACList *list, *list2;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_ACListISF, NULL, CLSCTX_INPROC, &IID_IACList, (void**)&list);
    ok(hr == S_OK, "failed to create ACListISF instance, 0x%08x\n", hr);

    hr = IACList_QueryInterface(list, &IID_IEnumString, (void**)&enumstring);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IEnumString_QueryInterface(enumstring, &IID_IACList, (void**)&list2);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(list == list2, "got %p, %p\n", list, list2);
    IACList_Release(list2);

    IEnumString_Release(enumstring);
    IACList_Release(list);
}