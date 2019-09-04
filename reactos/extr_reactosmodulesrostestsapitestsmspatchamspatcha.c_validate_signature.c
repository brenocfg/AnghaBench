#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  signatureW ;
typedef  int /*<<< orphan*/  signature ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ bin_file ;
typedef  char WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetFilePatchSignatureA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int GetFilePatchSignatureByHandle (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int GetFilePatchSignatureW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 char* GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _countof (char*) ; 
 int /*<<< orphan*/  _stricmp (char const*,char*) ; 
 int /*<<< orphan*/  extract (char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 

__attribute__((used)) static void validate_signature(const char* casename, const char* fieldname, const bin_file* bin, const char* expected)
{
    char filename[MAX_PATH];
    WCHAR filenameW[MAX_PATH];
    HANDLE hFile;
    unsigned char data[0x100];
    char signature[0x20] = {0};
    WCHAR signatureW[0x20] = {0};
    BOOL bResult;

    memset(signature, 0xaa, sizeof(signature));
    memcpy(data, bin->data, bin->len);

    if (!extract(filename, bin))
        return;

    memset(signature, 0xaa, sizeof(signature)-1);
    bResult = GetFilePatchSignatureA(filename, 0, NULL, 0, NULL, 0, NULL, sizeof(signature), signature);
    ok(bResult, "GetFilePatchSignatureA failed %lu, %s.%s\n", GetLastError(), casename, fieldname);
    if (bResult)
    {
        // Signature is crc32 of data
        ok(!_stricmp(expected, signature), "Got %s for %s.%s\n", signature, casename, fieldname);
    }

    memset(signature, 0xaa, sizeof(signature)-1);
    memset(signatureW, 0xaa, sizeof(signatureW)-sizeof(WCHAR));
    // Widechar version has a widechar signature
    MultiByteToWideChar(CP_ACP, 0, filename, -1, filenameW, _countof(filenameW));
    bResult = GetFilePatchSignatureW(filenameW, 0, NULL, 0, NULL, 0, NULL, sizeof(signatureW), signatureW);
    ok(bResult, "GetFilePatchSignatureW failed %lu, %s.%s\n", GetLastError(), casename, fieldname);
    if (bResult)
    {
        WideCharToMultiByte(CP_ACP, 0, signatureW, -1, signature, _countof(signature), NULL, NULL);
        // Signature is crc32 of data
        ok(!_stricmp(expected, signature), "Got %s for %s.%s\n", signature, casename, fieldname);
    }

    memset(signature, 0xaa, sizeof(signature)-1);
    // 'Handle' version has ansi signature
    hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hFile != INVALID_HANDLE_VALUE, "Unable to open file %lu\n", GetLastError());
    if (hFile != INVALID_HANDLE_VALUE)
    {
        bResult = GetFilePatchSignatureByHandle(hFile, 0, NULL, 0, NULL, 0, NULL, sizeof(signature), signature);
        ok(bResult, "GetFilePatchSignatureByHandle failed %lu, %s.%s\n", GetLastError(), casename, fieldname);
        if (bResult)
        {
            // Signature is crc32 of data
            ok(!_stricmp(expected, signature), "Got %s for %s.%s\n", signature, casename, fieldname);
        }

        CloseHandle(hFile);
    }

    DeleteFileA(filename);
}