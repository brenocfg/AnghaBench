#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lcid; } ;
typedef  TYPE_1__ TLIBATTR ;
typedef  int /*<<< orphan*/  ITypeLib ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLibAttr (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeLib_GetLibAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeLib_ReleaseTLibAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LIBID_TestTypelib ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int /*<<< orphan*/  LoadRegTypeLib (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **)) ; 

__attribute__((used)) static void test_libattr(void)
{
    ITypeLib *pTypeLib;
    HRESULT hr;
    TLIBATTR *pattr;

    hr = LoadRegTypeLib(&LIBID_TestTypelib, 2, 5, LOCALE_NEUTRAL, &pTypeLib);
    ok_ole_success(hr, LoadRegTypeLib);
    if (FAILED(hr))
        return;

    hr = ITypeLib_GetLibAttr(pTypeLib, &pattr);
    ok_ole_success(hr, GetLibAttr);
    if (SUCCEEDED(hr))
    {
        ok(pattr->lcid == MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), "lcid %x\n", pattr->lcid);

        ITypeLib_ReleaseTLibAttr(pTypeLib, pattr);
    }

    ITypeLib_Release(pTypeLib);
}