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
typedef  int /*<<< orphan*/  ITfDocumentMgr ;
typedef  int /*<<< orphan*/  ITfContext ;
typedef  int /*<<< orphan*/  IEnumTfContexts ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IEnumTfContexts_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumTfContexts_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfContext_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITfDocumentMgr_EnumContexts (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_EnumContexts(ITfDocumentMgr *dm, ITfContext *search)
{
    HRESULT hr;
    IEnumTfContexts* pEnum;
    BOOL found = FALSE;

    hr = ITfDocumentMgr_EnumContexts(dm,&pEnum);
    ok(SUCCEEDED(hr),"EnumContexts failed\n");
    if (SUCCEEDED(hr))
    {
        ULONG fetched;
        ITfContext *cxt;
        while (IEnumTfContexts_Next(pEnum, 1, &cxt, &fetched) == S_OK)
        {
            if (!search)
                found = TRUE;
            else if (search == cxt)
                found = TRUE;
            ITfContext_Release(cxt);
        }
        IEnumTfContexts_Release(pEnum);
    }
    if (search)
        ok(found,"Did not find proper ITfContext\n");
    else
        ok(!found,"Found an ITfContext we should should not have\n");
}