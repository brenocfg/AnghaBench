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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AtlGetObjectSourceInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 int /*<<< orphan*/  CLSID_HTMLStyle ; 
 int /*<<< orphan*/  DIID_DispHTMLBody ; 
 int /*<<< orphan*/  DIID_HTMLDocumentEvents ; 
 int /*<<< orphan*/  Dispatch ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIBID_MSHTML ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,unsigned short,...) ; 
 int /*<<< orphan*/  persist_clsid ; 
 int /*<<< orphan*/  support_classinfo2 ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_source_iface(void)
{
    unsigned short maj_ver, min_ver;
    IID libid, iid;
    HRESULT hres;

    support_classinfo2 = TRUE;

    maj_ver = min_ver = 0xdead;
    hres = AtlGetObjectSourceInterface((IUnknown*)&Dispatch, &libid, &iid, &maj_ver, &min_ver);
    ok(hres == S_OK, "AtlGetObjectSourceInterface failed: %08x\n", hres);
    ok(IsEqualGUID(&libid, &LIBID_MSHTML), "libid = %s\n", wine_dbgstr_guid(&libid));
    ok(IsEqualGUID(&iid, &DIID_DispHTMLBody), "iid = %s\n", wine_dbgstr_guid(&iid));
    ok(maj_ver == 4 && min_ver == 0, "ver = %d.%d\n", maj_ver, min_ver);

    support_classinfo2 = FALSE;
    persist_clsid = CLSID_HTMLDocument;

    maj_ver = min_ver = 0xdead;
    hres = AtlGetObjectSourceInterface((IUnknown*)&Dispatch, &libid, &iid, &maj_ver, &min_ver);
    ok(hres == S_OK, "AtlGetObjectSourceInterface failed: %08x\n", hres);
    ok(IsEqualGUID(&libid, &LIBID_MSHTML), "libid = %s\n", wine_dbgstr_guid(&libid));
    ok(IsEqualGUID(&iid, &DIID_HTMLDocumentEvents), "iid = %s\n", wine_dbgstr_guid(&iid));
    ok(maj_ver == 4 && min_ver == 0, "ver = %d.%d\n", maj_ver, min_ver);

    persist_clsid = CLSID_HTMLStyle;

    maj_ver = min_ver = 0xdead;
    hres = AtlGetObjectSourceInterface((IUnknown*)&Dispatch, &libid, &iid, &maj_ver, &min_ver);
    ok(hres == S_OK, "AtlGetObjectSourceInterface failed: %08x\n", hres);
    ok(IsEqualGUID(&libid, &LIBID_MSHTML), "libid = %s\n", wine_dbgstr_guid(&libid));
    ok(IsEqualGUID(&iid, &IID_NULL), "iid = %s\n", wine_dbgstr_guid(&iid));
    ok(maj_ver == 4 && min_ver == 0, "ver = %d.%d\n", maj_ver, min_ver);
}