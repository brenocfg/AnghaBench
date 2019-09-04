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
typedef  int /*<<< orphan*/  originalGuid ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 scalar_t__ NTE_KEYSET_ENTRY_BAD ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RegSetValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCryptAcquireContextA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  szKeySet ; 

__attribute__((used)) static void test_machine_guid(void)
{
   char originalGuid[40];
   LONG r;
   HKEY key;
   DWORD size;
   HCRYPTPROV hCryptProv;
   BOOL restoreGuid = FALSE, ret;

   r = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Cryptography",
                     0, KEY_ALL_ACCESS, &key);
   if (r != ERROR_SUCCESS)
   {
       skip("couldn't open HKLM\\Software\\Microsoft\\Cryptography\n");
       return;
   }
   /* Cache existing MachineGuid, and delete it */
   size = sizeof(originalGuid);
   r = RegQueryValueExA(key, "MachineGuid", NULL, NULL, (BYTE *)originalGuid,
                        &size);
   if (r == ERROR_SUCCESS)
   {
       restoreGuid = TRUE;
       r = RegDeleteValueA(key, "MachineGuid");
       ok(!r || broken(r == ERROR_ACCESS_DENIED) /*win8*/, "RegDeleteValueA failed: %d\n", r);
       if (r == ERROR_ACCESS_DENIED)
       {
           skip("broken virtualization on HKLM\\Software\\Microsoft\\Cryptography\n");
           RegCloseKey(key);
           return;
       }
   }
   else
       ok(r == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n",
          r);
   /* Create and release a provider */
   ret = pCryptAcquireContextA(&hCryptProv, szKeySet, NULL, PROV_RSA_FULL, 0);
   ok(ret || broken(!ret && GetLastError() == NTE_KEYSET_ENTRY_BAD /* NT4 */),
      "CryptAcquireContextA failed: %08x\n", GetLastError());
   pCryptReleaseContext(hCryptProv, 0);

   if (restoreGuid)
       RegSetValueExA(key, "MachineGuid", 0, REG_SZ, (const BYTE *)originalGuid,
                      strlen(originalGuid)+1);
   RegCloseKey(key);
}