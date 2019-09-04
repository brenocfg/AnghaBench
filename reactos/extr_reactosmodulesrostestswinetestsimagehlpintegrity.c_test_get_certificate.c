#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WIN_CERTIFICATE ;
struct TYPE_5__ {int /*<<< orphan*/  bCertificate; } ;
typedef  TYPE_1__* LPWIN_CERTIFICATE ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pImageGetCertificateData (scalar_t__,int,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  test_dll_path ; 

__attribute__((used)) static void test_get_certificate(const char *cert_data, int index)
{
    HANDLE hFile;
    LPWIN_CERTIFICATE cert;
    DWORD cert_len = 0;
    DWORD err;
    BOOL ret;

    hFile = CreateFileA(test_dll_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        skip("Unable to open %s, skipping test\n", test_dll_path);
        return;
    }

    ret = pImageGetCertificateData(hFile, index, NULL, &cert_len);
    err = GetLastError();

    ok ((ret == FALSE) && (err == ERROR_INSUFFICIENT_BUFFER), "ImageGetCertificateData gave unexpected result; ret=%d / err=%x\n", ret, err);

    cert = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cert_len);

    if (!cert)
    {
        skip("Unable to allocate memory, skipping test\n");
        CloseHandle(hFile);
        return;
    }

    ret = pImageGetCertificateData(hFile, index, cert, &cert_len);
    ok(ret, "Unable to retrieve certificate; err=%x\n", GetLastError());
    ok(memcmp(cert->bCertificate, cert_data, cert_len - sizeof(WIN_CERTIFICATE)) == 0, "Certificate retrieved did not match original\n");

    HeapFree(GetProcessHeap(), 0, cert);
    CloseHandle(hFile);
}