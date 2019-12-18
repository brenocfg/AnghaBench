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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IFilterMapper2 ;
typedef  int /*<<< orphan*/  IFilterGraph2 ;
typedef  int /*<<< orphan*/  IFilterGraph ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterGraph ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int E_NOINTERFACE ; 
 int IFilterGraph2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterGraph2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterGraph_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterMapper2_AddRef (int /*<<< orphan*/ *) ; 
 int IFilterMapper2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFilterMapper2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFilterGraph ; 
 int /*<<< orphan*/  IID_IFilterGraph2 ; 
 int /*<<< orphan*/  IID_IFilterMapper2 ; 
 int S_OK ; 
 int getRefcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_ifiltermapper_from_filtergraph(void)
{
    IFilterGraph2* pgraph2 = NULL;
    IFilterMapper2 *pMapper2 = NULL;
    IFilterGraph *filtergraph = NULL;
    HRESULT hr;
    ULONG refcount;

    hr = CoCreateInstance(&CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, &IID_IFilterGraph2, (LPVOID*)&pgraph2);
    ok(hr == S_OK, "CoCreateInstance failed with %08x\n", hr);
    if (!pgraph2) goto out;

    hr = IFilterGraph2_QueryInterface(pgraph2, &IID_IFilterMapper2, (LPVOID*)&pMapper2);
    ok(hr == S_OK, "IFilterGraph2_QueryInterface failed with %08x\n", hr);
    if (!pMapper2) goto out;

    refcount = getRefcount((IUnknown*)pgraph2);
    ok(refcount == 2, "unexpected reference count: %u\n", refcount);
    refcount = getRefcount((IUnknown*)pMapper2);
    ok(refcount == 2, "unexpected reference count: %u\n", refcount);

    IFilterMapper2_AddRef(pMapper2);
    refcount = getRefcount((IUnknown*)pgraph2);
    ok(refcount == 3, "unexpected reference count: %u\n", refcount);
    refcount = getRefcount((IUnknown*)pMapper2);
    ok(refcount == 3, "unexpected reference count: %u\n", refcount);
    IFilterMapper2_Release(pMapper2);

    hr = IFilterMapper2_QueryInterface(pMapper2, &IID_IFilterGraph, (LPVOID*)&filtergraph);
    ok(hr == S_OK, "IFilterMapper2_QueryInterface failed with %08x\n", hr);
    if (!filtergraph) goto out;

    IFilterMapper2_Release(pMapper2);
    pMapper2 = NULL;
    IFilterGraph_Release(filtergraph);
    filtergraph = NULL;

    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER, &IID_IFilterMapper2, (LPVOID*)&pMapper2);
    ok(hr == S_OK, "CoCreateInstance failed with %08x\n", hr);
    if (!pMapper2) goto out;

    hr = IFilterMapper2_QueryInterface(pMapper2, &IID_IFilterGraph, (LPVOID*)&filtergraph);
    ok(hr == E_NOINTERFACE, "IFilterMapper2_QueryInterface unexpected result: %08x\n", hr);

    out:

    if (pMapper2) IFilterMapper2_Release(pMapper2);
    if (filtergraph) IFilterGraph_Release(filtergraph);
    if (pgraph2) IFilterGraph2_Release(pgraph2);
}