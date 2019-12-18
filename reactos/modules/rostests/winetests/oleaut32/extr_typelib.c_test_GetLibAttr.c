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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  TLIBATTR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ ITypeLib_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ ITypeLib_GetLibAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_ReleaseTLibAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadTypeLib (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wszStdOle2 ; 

__attribute__((used)) static void test_GetLibAttr(void)
{
    ULONG ref1, ref2;
    TLIBATTR *attr;
    ITypeLib *tl;
    HRESULT hr;

    hr = LoadTypeLib(wszStdOle2, &tl);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ref1 = ITypeLib_AddRef(tl);
    ITypeLib_Release(tl);

    hr = ITypeLib_GetLibAttr(tl, &attr);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ref2 = ITypeLib_AddRef(tl);
    ITypeLib_Release(tl);
    ok(ref2 == ref1, "got %d, %d\n", ref2, ref1);

    ITypeLib_ReleaseTLibAttr(tl, attr);
    ITypeLib_Release(tl);
}