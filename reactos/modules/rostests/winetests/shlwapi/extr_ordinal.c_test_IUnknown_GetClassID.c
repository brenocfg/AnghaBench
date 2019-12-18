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
typedef  int /*<<< orphan*/  clsid3 ;
typedef  int /*<<< orphan*/  clsid2 ;
typedef  int /*<<< orphan*/  clsid ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_NULL ; 
 int E_FAIL ; 
 scalar_t__ IsEqualCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pIUnknown_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testpersist ; 
 int /*<<< orphan*/  testpersist2 ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IUnknown_GetClassID(void)
{
    CLSID clsid, clsid2, clsid3;
    HRESULT hr;

    if (0) /* crashes on native systems */
        hr = pIUnknown_GetClassID(NULL, NULL);

    memset(&clsid, 0xcc, sizeof(clsid));
    memset(&clsid3, 0xcc, sizeof(clsid3));
    hr = pIUnknown_GetClassID(NULL, &clsid);
    ok(hr == E_FAIL, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &CLSID_NULL) || broken(IsEqualCLSID(&clsid, &clsid3)) /* win2k, winxp, win2k3 */,
        "got wrong clsid %s\n", wine_dbgstr_guid(&clsid));

    memset(&clsid, 0xcc, sizeof(clsid));
    memset(&clsid2, 0xab, sizeof(clsid2));
    hr = pIUnknown_GetClassID((IUnknown*)&testpersist, &clsid);
    ok(hr == 0x8fff2222, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &clsid2) || broken(IsEqualCLSID(&clsid, &clsid3)) /* win2k3 */,
        "got wrong clsid %s\n", wine_dbgstr_guid(&clsid));

    /* IPersistFolder is also supported */
    memset(&clsid, 0xcc, sizeof(clsid));
    memset(&clsid2, 0xab, sizeof(clsid2));
    memset(&clsid3, 0xcc, sizeof(clsid3));
    hr = pIUnknown_GetClassID((IUnknown*)&testpersist2, &clsid);
    ok(hr == 0x8fff2222, "got 0x%08x\n", hr);
    ok(IsEqualCLSID(&clsid, &clsid2) || broken(IsEqualCLSID(&clsid, &clsid3)) /* win2k3 */,
        "got wrong clsid %s\n", wine_dbgstr_guid(&clsid));
}