#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  size_t ULONG ;
struct TYPE_12__ {int cb; int /*<<< orphan*/  lpb; } ;
struct TYPE_13__ {char* lpszA; char* lpszW; TYPE_1__ bin; } ;
struct TYPE_14__ {int ulPropTag; TYPE_2__ Value; } ;
typedef  TYPE_3__ SPropValue ;
typedef  scalar_t__ SCODE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  ALLOCATEMORE ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 scalar_t__ FAILED (scalar_t__) ; 
#define  PT_BINARY 130 
#define  PT_STRING8 129 
#define  PT_UNICODE 128 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pMAPIAllocateBuffer (int,TYPE_3__**) ; 
 scalar_t__ pMAPIAllocateMore (int,TYPE_3__*,TYPE_3__**) ; 
 scalar_t__ pMAPIFreeBuffer (TYPE_3__*) ; 
 scalar_t__ pPropCopyMore (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int* ptTypes ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  strcmpW (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_PropCopyMore(void)
{
    static char szHiA[] = "Hi!";
    static WCHAR szHiW[] = { 'H', 'i', '!', '\0' };
    SPropValue *lpDest = NULL, *lpSrc = NULL;
    ULONG i;
    SCODE scode;

    if (!pPropCopyMore)
    {
        win_skip("PropCopyMore is not available\n");
        return;
    }

    scode = pMAPIAllocateBuffer(sizeof(SPropValue), &lpDest);
    ok(scode == S_OK, "Expected MAPIAllocateBuffer to return S_OK, got 0x%x\n", scode);
    if (FAILED(scode))
    {
        skip("MAPIAllocateBuffer failed\n");
        return;
    }

    scode = pMAPIAllocateMore(sizeof(SPropValue), lpDest, &lpSrc);
    ok(scode == S_OK, "Expected MAPIAllocateMore to return S_OK, got 0x%x\n", scode);
    if (FAILED(scode))
    {
        skip("MAPIAllocateMore failed\n");
        return;
    }

    for (i = 0; i < ARRAY_SIZE(ptTypes); i++)
    {
        lpSrc->ulPropTag = ptTypes[i];

        switch (ptTypes[i])
        {
        case PT_STRING8:
            lpSrc->Value.lpszA = szHiA;
            break;
        case PT_UNICODE:
            lpSrc->Value.lpszW = szHiW;
            break;
        case PT_BINARY:
            lpSrc->Value.bin.cb = 4;
            lpSrc->Value.bin.lpb = (LPBYTE)szHiA;
            break;
        }

        memset(lpDest, 0xff, sizeof(SPropValue));

        scode = pPropCopyMore(lpDest, lpSrc, (ALLOCATEMORE*)pMAPIAllocateMore, lpDest);
        ok(!scode && lpDest->ulPropTag == lpSrc->ulPropTag,
           "PropCopyMore: Expected 0x0,%d, got 0x%08x,%d\n",
           lpSrc->ulPropTag, scode, lpDest->ulPropTag);
        if (SUCCEEDED(scode))
        {
            switch (ptTypes[i])
            {
            case PT_STRING8:
                ok(lstrcmpA(lpDest->Value.lpszA, lpSrc->Value.lpszA) == 0,
                   "PropCopyMore: Ascii string differs\n");
                break;
            case PT_UNICODE:
                ok(strcmpW(lpDest->Value.lpszW, lpSrc->Value.lpszW) == 0,
                   "PropCopyMore: Unicode string differs\n");
                break;
            case PT_BINARY:
                ok(lpDest->Value.bin.cb == 4 &&
                   !memcmp(lpSrc->Value.bin.lpb, lpDest->Value.bin.lpb, 4),
                   "PropCopyMore: Binary array  differs\n");
                break;
            }
        }
    }

    /* Since all allocations are linked, freeing lpDest frees everything */
    scode = pMAPIFreeBuffer(lpDest);
    ok(scode == S_OK, "Expected MAPIFreeBuffer to return S_OK, got 0x%x\n", scode);
}