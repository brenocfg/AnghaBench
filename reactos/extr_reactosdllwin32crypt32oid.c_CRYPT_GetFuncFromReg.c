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
struct FuncAddr {int /*<<< orphan*/ * currentDll; int /*<<< orphan*/  dllList; scalar_t__ lib; } ;
typedef  scalar_t__ LSTATUS ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  char const* LPCSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  struct FuncAddr* HCRYPTOIDFUNCADDR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char* CRYPT_GetKeyName (scalar_t__,char const*,char const*) ; 
 void* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (char*) ; 
 int /*<<< orphan*/  DllW ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetProcAddress (scalar_t__,char const*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ LoadLibraryW (char*) ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_GetFuncFromReg(DWORD dwEncodingType, LPCSTR pszOID,
 LPCSTR szFuncName, LPVOID *ppvFuncAddr, HCRYPTOIDFUNCADDR *phFuncAddr)
{
    BOOL ret = FALSE;
    char *keyName;
    const char *funcName;
    HKEY key;
    LSTATUS rc;

    keyName = CRYPT_GetKeyName(dwEncodingType, szFuncName, pszOID);
    rc = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_READ, &key);
    if (!rc)
    {
        DWORD type, size = 0;

        rc = RegQueryValueExA(key, "FuncName", NULL, &type, NULL, &size);
        if ((!rc || rc == ERROR_MORE_DATA) && type == REG_SZ)
        {
            funcName = CryptMemAlloc(size);
            rc = RegQueryValueExA(key, "FuncName", NULL, &type,
             (LPBYTE)funcName, &size);
        }
        else
            funcName = szFuncName;
        rc = RegQueryValueExW(key, DllW, NULL, &type, NULL, &size);
        if ((!rc || rc == ERROR_MORE_DATA) && type == REG_SZ)
        {
            LPWSTR dllName = CryptMemAlloc(size);

            if (dllName)
            {
                rc = RegQueryValueExW(key, DllW, NULL, NULL,
                 (LPBYTE)dllName, &size);
                if (!rc)
                {
                    HMODULE lib;

                    /* This is a bit of a hack; MSDN describes a more
                     * complicated unload routine than this will allow.
                     * Still, this seems to suffice for now.
                     */
                    lib = LoadLibraryW(dllName);
                    if (lib)
                    {
                        *ppvFuncAddr = GetProcAddress(lib, funcName);
                        if (*ppvFuncAddr)
                        {
                            struct FuncAddr *addr =
                             CryptMemAlloc(sizeof(struct FuncAddr));

                            if (addr)
                            {
                                addr->lib = lib;
                                addr->dllList = addr->currentDll = NULL;
                                *phFuncAddr = addr;
                                ret = TRUE;
                            }
                            else
                            {
                                *phFuncAddr = NULL;
                                FreeLibrary(lib);
                            }
                        }
                        else
                        {
                            /* Unload the library, the caller doesn't want
                             * to unload it when the return value is NULL.
                             */
                            FreeLibrary(lib);
                        }
                    }
                }
                else
                    SetLastError(rc);
                CryptMemFree(dllName);
            }
        }
        else
            SetLastError(rc);
        if (funcName != szFuncName)
            CryptMemFree((char *)funcName);
        RegCloseKey(key);
    }
    else
        SetLastError(rc);
    CryptMemFree(keyName);
    return ret;
}