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
struct TYPE_5__ {int dwLength; int /*<<< orphan*/  bCertificate; int /*<<< orphan*/  wCertificateType; int /*<<< orphan*/  wRevision; } ;
typedef  TYPE_1__* LPWIN_CERTIFICATE ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  WIN_CERT_REVISION_1_0 ; 
 int /*<<< orphan*/  WIN_CERT_TYPE_PKCS_SIGNED_DATA ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pImageAddCertificate (scalar_t__,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  test_dll_path ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static DWORD test_add_certificate(const char *cert_data, int len)
{
    HANDLE hFile;
    LPWIN_CERTIFICATE cert;
    DWORD cert_len;
    DWORD index;
    BOOL ret;

    hFile = CreateFileA(test_dll_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        skip("Unable to open %s, skipping test\n", test_dll_path);
        return ~0;
    }

    cert_len = sizeof(WIN_CERTIFICATE) + len;
    cert = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cert_len);

    if (!cert)
    {
        skip("Unable to allocate memory, skipping test\n");
        CloseHandle(hFile);
        return ~0;
    }

    cert->dwLength = cert_len;
    cert->wRevision = WIN_CERT_REVISION_1_0;
    cert->wCertificateType = WIN_CERT_TYPE_PKCS_SIGNED_DATA;
    CopyMemory(cert->bCertificate, cert_data, len);

    ret = pImageAddCertificate(hFile, cert, &index);
    ok(ret, "Unable to add certificate to image, error %x\n", GetLastError());
    trace("added cert index %d\n", index);

    HeapFree(GetProcessHeap(), 0, cert);
    CloseHandle(hFile);
    return index;
}