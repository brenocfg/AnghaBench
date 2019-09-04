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
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IInternetSecurityManager ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CoMarshalInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IInternetSecurityManager ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IInternetSecurityManager_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IInternetSecurityManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_INPROC ; 
 int /*<<< orphan*/  MSHLFLAGS_NORMAL ; 
 scalar_t__ REGDB_E_IIDNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInternetCreateSecurityManager (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_InternetSecurityMarshalling(void)
{
    IInternetSecurityManager *secmgr = NULL;
    IUnknown *unk;
    IStream *stream;
    HRESULT hres;

    trace("testing marshalling...\n");

    hres = pCoInternetCreateSecurityManager(NULL, &secmgr, 0);
    ok(hres == S_OK, "CoInternetCreateSecurityManager failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IInternetSecurityManager_QueryInterface(secmgr, &IID_IUnknown, (void**)&unk);
    ok(hres == S_OK, "QueryInterface returned: %08x\n", hres);

    hres = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hres == S_OK, "CreateStreamOnHGlobal returned: %08x\n", hres);

    hres = CoMarshalInterface(stream, &IID_IInternetSecurityManager, unk, MSHCTX_INPROC, NULL, MSHLFLAGS_NORMAL);
    /* Not supported in W98 */
    ok(hres == S_OK || broken(hres == REGDB_E_IIDNOTREG),
        "CoMarshalInterface returned: %08x\n", hres);

    IStream_Release(stream);
    IUnknown_Release(unk);
    IInternetSecurityManager_Release(secmgr);
}