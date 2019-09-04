#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
struct TYPE_8__ {int nLength; int lpSecurityDescriptor; int bInheritHandle; } ;
struct TYPE_9__ {int cbSize; TYPE_1__ securityAttributes; scalar_t__* szExtraInfo; int /*<<< orphan*/  dwReserved; int /*<<< orphan*/ * pUnk; TYPE_6__ iid; int /*<<< orphan*/  dwCodePage; int /*<<< orphan*/  dwOptionsFlags; int /*<<< orphan*/  dwOptions; int /*<<< orphan*/  cbstgmedData; int /*<<< orphan*/ * szCustomVerb; int /*<<< orphan*/  dwBindVerb; int /*<<< orphan*/  grfBindInfoF; TYPE_6__ stgmedData; } ;
typedef  int /*<<< orphan*/  STGMEDIUM ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/  IID ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ BINDINFO ;

/* Variables and functions */
 scalar_t__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (scalar_t__*) ; 
 int E_INVALIDARG ; 
 int E_POINTER ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int S_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  TYMED_NULL ; 
 int /*<<< orphan*/  memcmp (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCopyBindInfo (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void test_CopyBindInfo(void)
{
    BINDINFO src[2], dest[2];
    SECURITY_DESCRIPTOR sec_desc;
    HRESULT hres;
    int i;

    hres = pCopyBindInfo(NULL, NULL);
    ok(hres == E_POINTER, "CopyBindInfo returned %08x, expected E_POINTER\n", hres);

    memset(src, 0, sizeof(BINDINFO[2]));
    memset(dest, 0xde, sizeof(BINDINFO[2]));
    hres = pCopyBindInfo(src, dest);
    ok(hres == E_INVALIDARG, "CopyBindInfo returned: %08x, expected E_INVALIDARG\n", hres);

    memset(src, 0, sizeof(BINDINFO[2]));
    memset(dest, 0xde, sizeof(BINDINFO[2]));
    src[0].cbSize = sizeof(BINDINFO);
    dest[0].cbSize = 0;
    hres = pCopyBindInfo(src, dest);
    ok(hres == E_INVALIDARG, "CopyBindInfo returned: %08x, expected E_INVALIDARG\n", hres);

    memset(src, 0, sizeof(BINDINFO[2]));
    memset(dest, 0xde, sizeof(BINDINFO[2]));
    src[0].cbSize = 1;
    dest[0].cbSize = sizeof(BINDINFO)+sizeof(DWORD);
    hres = pCopyBindInfo(src, dest);
    ok(hres == S_OK, "CopyBindInfo failed: %08x\n", hres);
    ok(dest[0].cbSize == sizeof(BINDINFO)+sizeof(DWORD), "incorrect cbSize: %d\n", dest[0].cbSize);
    for(i=1; i<dest[0].cbSize/sizeof(int); i++)
        ok(((int*)dest)[i] == 0, "unset values should be set to 0, got %d on %d\n", ((int*)dest)[i], i);

    memset(src, 0, sizeof(BINDINFO[2]));
    memset(dest, 0xde, sizeof(BINDINFO[2]));
    src[0].cbSize = sizeof(BINDINFO)+2*sizeof(DWORD);
    dest[0].cbSize = sizeof(BINDINFO)+sizeof(DWORD);
    hres = pCopyBindInfo(src, dest);
    ok(hres == S_OK, "CopyBindInfo failed: %08x\n", hres);
    ok(dest[1].cbSize == src[1].cbSize, "additional data should be copied\n");
    ok(dest[1].szExtraInfo != src[1].szExtraInfo,
            "data not fitting in destination buffer should not be copied\n");

    memset(src, 0xf0, sizeof(BINDINFO[2]));
    memset(dest, 0xde, sizeof(BINDINFO[2]));
    src[0].cbSize = sizeof(BINDINFO);
    src[0].szExtraInfo = CoTaskMemAlloc(sizeof(WCHAR));
    src[0].szExtraInfo[0] = 0;
    src[0].szCustomVerb = NULL;
    src[0].pUnk = NULL;
    src[0].stgmedData.tymed = TYMED_NULL;
    src[0].stgmedData.pUnkForRelease = NULL;
    dest[0].cbSize = sizeof(BINDINFO);
    hres = pCopyBindInfo(src, dest);
    ok(hres == S_OK, "CopyBindInfo failed: %08x\n", hres);

    ok(dest[0].cbSize == sizeof(BINDINFO), "incorrect cbSize: %d\n", dest[0].cbSize);
    ok(dest[0].szExtraInfo && !dest[0].szExtraInfo[0] && dest[0].szExtraInfo!=src[0].szExtraInfo,
            "incorrect szExtraInfo: (%p!=%p) %d\n", dest[0].szExtraInfo,
            src[0].szExtraInfo, dest[0].szExtraInfo[0]);
    ok(!memcmp(&dest[0].stgmedData, &src[0].stgmedData, sizeof(STGMEDIUM)),
            "incorrect stgmedData value\n");
    ok(src[0].grfBindInfoF == dest[0].grfBindInfoF, "grfBindInfoF = %x, expected %x\n",
            dest[0].grfBindInfoF, src[0].grfBindInfoF);
    ok(src[0].dwBindVerb == dest[0].dwBindVerb, "dwBindVerb = %x, expected %x\n",
            dest[0].dwBindVerb, src[0].dwBindVerb);
    ok(!dest[0].szCustomVerb, "szCustmoVerb != NULL\n");
    ok(src[0].cbstgmedData == dest[0].cbstgmedData, "cbstgmedData = %x, expected %x\n",
            dest[0].cbstgmedData, src[0].cbstgmedData);
    ok(src[0].dwOptions == dest[0].dwOptions, "dwOptions = %x, expected %x\n",
            dest[0].dwOptions, src[0].dwOptions);
    ok(src[0].dwOptionsFlags == dest[0].dwOptionsFlags, "dwOptionsFlags = %x, expected %x\n",
            dest[0].dwOptionsFlags, src[0].dwOptionsFlags);
    ok(src[0].dwCodePage == dest[0].dwCodePage, "dwCodePage = %x, expected %x\n",
            dest[0].dwCodePage, src[0].dwCodePage);
    ok(!dest[0].securityAttributes.nLength,
            "unexpected securityAttributes.nLength value: %d\n",
            dest[0].securityAttributes.nLength);
    ok(!dest[0].securityAttributes.lpSecurityDescriptor,
            "unexpected securityAttributes.lpSecurityDescriptor value: %p\n",
            dest[0].securityAttributes.lpSecurityDescriptor);
    ok(!dest[0].securityAttributes.bInheritHandle,
            "unexpected securityAttributes.bInheritHandle value: %d\n",
            dest[0].securityAttributes.bInheritHandle);
    ok(!memcmp(&dest[0].iid, &src[0].iid, sizeof(IID)),
            "incorrect iid value\n");
    ok(!dest[0].pUnk, "pUnk != NULL\n");
    ok(src[0].dwReserved == dest[0].dwReserved, "dwReserved = %x, expected %x\n",
            dest[0].dwReserved, src[0].dwReserved);

    CoTaskMemFree(src[0].szExtraInfo);
    CoTaskMemFree(dest[0].szExtraInfo);

    src[0].szExtraInfo = NULL;
    src[0].securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    ok(InitializeSecurityDescriptor(&sec_desc, SECURITY_DESCRIPTOR_REVISION),
            "InitializeSecurityDescriptor failed\n");
    src[0].securityAttributes.lpSecurityDescriptor = (void*)&sec_desc;
    src[0].securityAttributes.bInheritHandle = TRUE;
    hres = pCopyBindInfo(src, dest);
    ok(hres == S_OK, "CopyBindInfo failed: %08x\n", hres);
    ok(!dest[0].securityAttributes.nLength,
            "unexpected securityAttributes.nLength value: %d\n",
            dest[0].securityAttributes.nLength);
    ok(!dest[0].securityAttributes.lpSecurityDescriptor,
            "unexpected securityAttributes.lpSecurityDescriptor value: %p\n",
            dest[0].securityAttributes.lpSecurityDescriptor);
    ok(!dest[0].securityAttributes.bInheritHandle,
            "unexpected securityAttributes.bInheritHandle value: %d\n",
            dest[0].securityAttributes.bInheritHandle);
}