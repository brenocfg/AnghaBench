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
typedef  int /*<<< orphan*/  IClassFactory ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_MkProtocol ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IClassFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  MK_PROTOCOL ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  blank_url3 ; 
 int /*<<< orphan*/  blank_url7 ; 
 int /*<<< orphan*/  blank_url8 ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  cache_file ; 
 int /*<<< orphan*/  cache_file1 ; 
 int /*<<< orphan*/  cache_file2 ; 
 int /*<<< orphan*/  cache_file3 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_protocol ; 
 int /*<<< orphan*/  test_protocol_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_mk_protocol(void)
{
    IClassFactory *cf;
    HRESULT hres;

    test_protocol = MK_PROTOCOL;

    hres = CoGetClassObject(&CLSID_MkProtocol, CLSCTX_INPROC_SERVER, NULL, &IID_IClassFactory,
                            (void**)&cf);
    ok(hres == S_OK ||
       broken(hres == REGDB_E_CLASSNOTREG), /* Some W95 and NT4 */
       "CoGetClassObject failed: %08x\n", hres);
    if(FAILED(hres))
        return;

    cache_file = cache_file1;
    test_protocol_url(cf, blank_url3, TRUE);
    cache_file = cache_file2;
    test_protocol_url(cf, blank_url7, TRUE);
    cache_file = cache_file3;
    test_protocol_url(cf, blank_url8, FALSE);

    IClassFactory_Release(cf);
}