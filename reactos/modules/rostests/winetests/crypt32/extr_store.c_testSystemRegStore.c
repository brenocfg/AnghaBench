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
typedef  scalar_t__ HCERTSTORE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BogusPathW ; 
 int /*<<< orphan*/ * BogusW ; 
 int CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_DELETE_FLAG ; 
 int CERT_STORE_OPEN_EXISTING_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CERT_STORE_PROV_SYSTEM_REGISTRY ; 
 int CERT_SYSTEM_STORE_CURRENT_USER ; 
 int CERT_SYSTEM_STORE_LOCAL_MACHINE ; 
 int /*<<< orphan*/  CertAddStoreToCollection (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * MyA ; 
 int /*<<< orphan*/ * MyW ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void testSystemRegStore(void)
{
    HCERTSTORE store, memStore;

    /* Check with a UNICODE name */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, MyW);
    /* Not all OSes support CERT_STORE_PROV_SYSTEM_REGISTRY, so don't continue
     * testing if they don't.
     */
    if (!store)
        return;

    /* Check that it isn't a collection store */
    memStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    if (memStore)
    {
        BOOL ret = CertAddStoreToCollection(store, memStore, 0, 0);
        ok(!ret && GetLastError() == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", GetLastError());
        CertCloseStore(memStore, 0);
    }
    CertCloseStore(store, 0);

    /* Check opening a bogus store */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, BogusW);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER, BogusW);
    ok(store != 0, "CertOpenStore failed: %08x\n", GetLastError());
    if (store)
        CertCloseStore(store, 0);
    /* Now check whether deleting is allowed */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_DELETE_FLAG, BogusW);
    ok(!store, "CertOpenStore failed: %08x\n", GetLastError());
    RegDeleteKeyW(HKEY_CURRENT_USER, BogusPathW);

    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0, 0, NULL);
    ok(!store && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_LOCAL_MACHINE | CERT_SYSTEM_STORE_CURRENT_USER, MyA);
    ok(!store && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_LOCAL_MACHINE | CERT_SYSTEM_STORE_CURRENT_USER, MyW);
    ok(!store && GetLastError() == E_INVALIDARG,
     "Expected E_INVALIDARG, got %08x\n", GetLastError());
    /* The name is expected to be UNICODE, check with an ASCII name */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM_REGISTRY, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, MyA);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
}