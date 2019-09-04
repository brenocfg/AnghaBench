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
typedef  int /*<<< orphan*/  expectedhash ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTempFileNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pCryptCATAdminCalcHashFromFileHandle (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/ * selfname ; 

__attribute__((used)) static void test_calchash(void)
{
    BOOL ret;
    HANDLE file;
    DWORD hashsize = 0;
    BYTE* hash;
    BYTE expectedhash[20] = {0x3a,0xa1,0x19,0x08,0xec,0xa6,0x0d,0x2e,0x7e,0xcc,0x7a,0xca,0xf5,0xb8,0x2e,0x62,0x6a,0xda,0xf0,0x19};
    CHAR temp[MAX_PATH];
    DWORD written;

    /* All NULL */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(NULL, NULL, NULL, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* NULL filehandle, rest is legal */
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(NULL, &hashsize, NULL, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Correct filehandle, rest is NULL */
    file = CreateFileA(selfname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(file, NULL, NULL, 0);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    CloseHandle(file);

    /* All OK, but dwFlags set to 1 */
    file = CreateFileA(selfname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(file, &hashsize, NULL, 1);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    CloseHandle(file);

    /* All OK, requesting the size of the hash */
    file = CreateFileA(selfname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed %u\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(file, &hashsize, NULL, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    ok(hashsize == 20," Expected a hash size of 20, got %d\n", hashsize);
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "Expected ERROR_INSUFFICIENT_BUFFER, got %d\n", GetLastError());
    CloseHandle(file);

    /* All OK, retrieve the hash
     * Double the hash buffer to see what happens to the size parameter
     */
    file = CreateFileA(selfname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    hashsize *= 2;
    hash = HeapAlloc(GetProcessHeap(), 0, hashsize);
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(file, &hashsize, hash, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    ok(hashsize == 20," Expected a hash size of 20, got %d\n", hashsize);
    ok(GetLastError() == ERROR_SUCCESS,
       "Expected ERROR_SUCCESS, got %d\n", GetLastError());
    CloseHandle(file);
    HeapFree(GetProcessHeap(), 0, hash);

    /* Do the same test with a file created and filled by ourselves (and we thus
     * have a known hash for).
     */
    GetTempFileNameA(CURR_DIR, "hsh", 0, temp); 
    file = CreateFileA(temp, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    WriteFile(file, "Text in this file is needed to create a know hash", 49, &written, NULL);
    CloseHandle(file);

    /* All OK, first request the size and then retrieve the hash */
    file = CreateFileA(temp, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    hashsize = 0;
    pCryptCATAdminCalcHashFromFileHandle(file, &hashsize, NULL, 0);
    hash = HeapAlloc(GetProcessHeap(), 0, hashsize);
    SetLastError(0xdeadbeef);
    ret = pCryptCATAdminCalcHashFromFileHandle(file, &hashsize, hash, 0);
    ok(ret, "Expected success, got FALSE with %d\n", GetLastError());
    ok(GetLastError() == ERROR_SUCCESS,
       "Expected ERROR_SUCCESS, got %d\n", GetLastError());
    ok(hashsize == sizeof(expectedhash) &&
       !memcmp(hash, expectedhash, sizeof(expectedhash)),
       "Hashes didn't match\n");
    CloseHandle(file);

    HeapFree(GetProcessHeap(), 0, hash);
    DeleteFileA(temp);
}