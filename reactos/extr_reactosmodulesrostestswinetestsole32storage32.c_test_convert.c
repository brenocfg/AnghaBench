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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (char const*) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetConvertStg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int STGM_CREATE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ STG_E_FILENOTFOUND ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ SetConvertStg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ StgCreateDocfile (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_convert(void)
{
    static const WCHAR filename[] = {'s','t','o','r','a','g','e','.','s','t','g',0};
    IStorage *stg;
    HRESULT hr;

    hr = GetConvertStg(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = StgCreateDocfile( filename, STGM_CREATE | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 0, &stg);
    ok(hr == S_OK, "StgCreateDocfile failed\n");
    hr = GetConvertStg(stg);
    ok(hr == STG_E_FILENOTFOUND, "got 0x%08x\n", hr);
    hr = SetConvertStg(stg, TRUE);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = SetConvertStg(stg, TRUE);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = GetConvertStg(stg);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = SetConvertStg(stg, FALSE);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = GetConvertStg(stg);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);

    IStorage_Release(stg);

    DeleteFileW(filename);
}