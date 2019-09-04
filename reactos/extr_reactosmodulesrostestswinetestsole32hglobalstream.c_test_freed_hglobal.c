#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teststring ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int ULONG ;
struct TYPE_3__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * HGLOBAL ;

/* Variables and functions */
 int CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int GMEM_NODISCARD ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * GlobalAlloc (int,scalar_t__) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 char* GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 int IStream_Read (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int IStream_SetSize (int /*<<< orphan*/ *,TYPE_1__) ; 
 int IStream_Write (int /*<<< orphan*/ *,char*,int,int*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_ole_success (int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void test_freed_hglobal(void)
{
    static const char teststring[] = "this is a test string";
    HRESULT hr;
    IStream *pStream;
    HGLOBAL hglobal;
    char *p;
    char buffer[sizeof(teststring) + 8];
    ULARGE_INTEGER ull;
    ULONG read, written;

    hglobal = GlobalAlloc(GMEM_DDESHARE|GMEM_NODISCARD|GMEM_MOVEABLE, strlen(teststring) + 1);
    ok(hglobal != NULL, "GlobalAlloc failed with error %d\n", GetLastError());
    p = GlobalLock(hglobal);
    strcpy(p, teststring);
    GlobalUnlock(hglobal);

    hr = CreateStreamOnHGlobal(hglobal, FALSE, &pStream);
    ok_ole_success(hr, "CreateStreamOnHGlobal");

    hr = IStream_Read(pStream, buffer, sizeof(buffer), &read);
    ok_ole_success(hr, "IStream_Read");
    ok(!strcmp(buffer, teststring), "buffer data %s differs\n", buffer);
    ok(read == sizeof(teststring) ||
       broken(read == ((sizeof(teststring) + 3) & ~3)), /* win9x rounds the size */
       "read should be sizeof(teststring) instead of %d\n", read);

    GlobalFree(hglobal);

    memset(buffer, 0, sizeof(buffer));
    read = -1;
    hr = IStream_Read(pStream, buffer, sizeof(buffer), &read);
    ok_ole_success(hr, "IStream_Read");
    ok(buffer[0] == 0, "buffer data should be untouched\n");
    ok(read == 0, "read should be 0 instead of %d\n", read);

    ull.QuadPart = sizeof(buffer);
    hr = IStream_SetSize(pStream, ull);
    ok(hr == E_OUTOFMEMORY, "IStream_SetSize with invalid HGLOBAL should return E_OUTOFMEMORY instead of 0x%08x\n", hr);

    hr = IStream_Write(pStream, buffer, sizeof(buffer), &written);
    ok(hr == E_OUTOFMEMORY, "IStream_Write with invalid HGLOBAL should return E_OUTOFMEMORY instead of 0x%08x\n", hr);
    ok(written == 0, "written should be 0 instead of %d\n", written);

    IStream_Release(pStream);
}