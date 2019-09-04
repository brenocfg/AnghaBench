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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ HCERTSTORE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BogusPathW ; 
 char const* BogusW ; 
 int /*<<< orphan*/  CERT_LOCAL_MACHINE_SYSTEM_STORE_REGPATH ; 
 int CERT_STORE_CREATE_NEW_FLAG ; 
 int CERT_STORE_DELETE_FLAG ; 
 int CERT_STORE_OPEN_EXISTING_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 int /*<<< orphan*/  CERT_STORE_PROV_SYSTEM ; 
 int CERT_SYSTEM_STORE_CURRENT_USER ; 
 int CERT_SYSTEM_STORE_LOCAL_MACHINE ; 
 int /*<<< orphan*/  CertAddStoreToCollection (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertCloseStore (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 char const* MyA ; 
 char const* MyW ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void testSystemStore(void)
{
    static const WCHAR baskslashW[] = { '\\',0 };
    HCERTSTORE store;
    WCHAR keyName[MAX_PATH];
    HKEY key;
    LONG rc;

    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, 0, NULL);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_LOCAL_MACHINE | CERT_SYSTEM_STORE_CURRENT_USER, MyA);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_LOCAL_MACHINE | CERT_SYSTEM_STORE_CURRENT_USER, MyW);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    /* The name is expected to be UNICODE, first check with an ASCII name */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, MyA);
    ok(!store && GetLastError() == ERROR_FILE_NOT_FOUND,
     "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    /* Create the expected key */
    lstrcpyW(keyName, CERT_LOCAL_MACHINE_SYSTEM_STORE_REGPATH);
    lstrcatW(keyName, baskslashW);
    lstrcatW(keyName, MyW);
    rc = RegCreateKeyExW(HKEY_CURRENT_USER, keyName, 0, NULL, 0, KEY_READ,
     NULL, &key, NULL);
    ok(!rc, "RegCreateKeyEx failed: %d\n", rc);
    if (!rc)
        RegCloseKey(key);
    /* Check opening with a UNICODE name, specifying the create new flag */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_CREATE_NEW_FLAG, MyW);
    ok(!store && GetLastError() == ERROR_FILE_EXISTS,
     "Expected ERROR_FILE_EXISTS, got %08x\n", GetLastError());
    /* Now check opening with a UNICODE name, this time opening existing */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, MyW);
    ok(store != 0, "CertOpenStore failed: %08x\n", GetLastError());
    if (store)
    {
        HCERTSTORE memStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0,
         CERT_STORE_CREATE_NEW_FLAG, NULL);

        /* Check that it's a collection store */
        if (memStore)
        {
            BOOL ret = CertAddStoreToCollection(store, memStore, 0, 0);
            ok(ret, "CertAddStoreToCollection failed: %08x\n", GetLastError());
            CertCloseStore(memStore, 0);
        }
        CertCloseStore(store, 0);
    }

    /* Check opening a bogus store */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_OPEN_EXISTING_FLAG, BogusW);
    ok(!store, "Expected ERROR_FILE_NOT_FOUND, got %08x\n", GetLastError());
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER, BogusW);
    ok(store != 0, "CertOpenStore failed: %08x\n", GetLastError());
    if (store)
        CertCloseStore(store, 0);
    /* Now check whether deleting is allowed */
    store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0,
     CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_DELETE_FLAG, BogusW);
    ok(!store, "Didn't expect a store to be returned when deleting\n");
    RegDeleteKeyW(HKEY_CURRENT_USER, BogusPathW);
}