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
typedef  int /*<<< orphan*/  IOleObject ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IEnumSTATDATA ;
typedef  int /*<<< orphan*/  IAdviseSink ;
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AdviseSink ; 
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IOleObject ; 
 int IOleObject_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int IOleObject_EnumAdvise (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IOleObject_Release (int /*<<< orphan*/ *) ; 
 int IOleObject_Unadvise (int /*<<< orphan*/ *,int) ; 
 int OLE_E_NOCONNECTION ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_Advise(IHTMLDocument2 *doc)
{
    IOleObject *oleobj = NULL;
    IEnumSTATDATA *enum_advise = (void*)0xdeadbeef;
    DWORD conn;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IOleObject, (void**)&oleobj);
    ok(hres == S_OK, "QueryInterface(IID_IOleObject) failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IOleObject_Unadvise(oleobj, 0);
    ok(hres == OLE_E_NOCONNECTION, "Unadvise returned: %08x\n", hres);

    hres = IOleObject_EnumAdvise(oleobj, &enum_advise);
    ok(hres == S_OK, "EnumAdvise returned: %08x\n", hres);
    ok(enum_advise == NULL, "enum_advise != NULL\n");

    conn = -1;
    hres = IOleObject_Advise(oleobj, NULL, &conn);
    /* Old IE returns S_OK and sets conn to 1 */
    ok(hres == E_INVALIDARG || hres == S_OK, "Advise returned: %08x\n", hres);
    ok(conn == 0 || conn == 1, "conn = %d\n", conn);

    hres = IOleObject_Advise(oleobj, (IAdviseSink*)&AdviseSink, NULL);
    ok(hres == E_INVALIDARG, "Advise returned: %08x\n", hres);

    hres = IOleObject_Advise(oleobj, (IAdviseSink*)&AdviseSink, &conn);
    ok(hres == S_OK, "Advise returned: %08x\n", hres);
    ok(conn == 1, "conn = %d\n", conn);

    hres = IOleObject_Advise(oleobj, (IAdviseSink*)&AdviseSink, &conn);
    ok(hres == S_OK, "Advise returned: %08x\n", hres);
    ok(conn == 2, "conn = %d\n", conn);

    hres = IOleObject_Unadvise(oleobj, 1);
    ok(hres == S_OK, "Unadvise returned: %08x\n", hres);

    hres = IOleObject_Unadvise(oleobj, 1);
    ok(hres == OLE_E_NOCONNECTION, "Unadvise returned: %08x\n", hres);

    hres = IOleObject_Unadvise(oleobj, 2);
    ok(hres == S_OK, "Unadvise returned: %08x\n", hres);

    IOleObject_Release(oleobj);
}