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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  ITfThreadMgr ;
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  IEnumTfDocumentMgrs ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IEnumTfDocumentMgrs_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumTfDocumentMgrs_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfDocumentMgr_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfThreadMgr_EnumDocumentMgrs (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_EnumDocumentMgr(ITfThreadMgr *tm, ITfDocumentMgr *search, ITfDocumentMgr *absent)
{
    HRESULT hr;
    IEnumTfDocumentMgrs* pEnum;
    BOOL found = FALSE;
    BOOL notfound = TRUE;

    hr = ITfThreadMgr_EnumDocumentMgrs(tm,&pEnum);
    ok(SUCCEEDED(hr),"EnumDocumentMgrs failed\n");
    if (SUCCEEDED(hr))
    {
        ULONG fetched;
        ITfDocumentMgr *dm;
        while (IEnumTfDocumentMgrs_Next(pEnum, 1, &dm, &fetched) == S_OK)
        {
            if (!search)
                found = TRUE;
            else if (search == dm)
                found = TRUE;
            if (absent && dm == absent)
                notfound = FALSE;
            ITfDocumentMgr_Release(dm);
        }
        IEnumTfDocumentMgrs_Release(pEnum);
    }
    if (search)
        ok(found,"Did not find proper ITfDocumentMgr\n");
    else
        ok(!found,"Found an ITfDocumentMgr we should should not have\n");
    if (absent)
        ok(notfound,"Found an ITfDocumentMgr we believe should be absent\n");
}