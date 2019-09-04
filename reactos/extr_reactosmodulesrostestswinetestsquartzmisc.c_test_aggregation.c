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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IID ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  ADDREF_EXPECT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IGraphConfig ; 
 int /*<<< orphan*/  const IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  QI_FAIL (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QI_SUCCEED (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  RELEASE_EXPECT (int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_aggregation(const CLSID clsidOuter, const CLSID clsidInner,
                             const IID iidOuter, const IID iidInner)
{
    HRESULT hr;
    ULONG refCount;
    IUnknown *pUnkOuter = NULL;
    IUnknown *pUnkInner = NULL;
    IUnknown *pUnkInnerFail = NULL;
    IUnknown *pUnkOuterTest = NULL;
    IUnknown *pUnkInnerTest = NULL;
    IUnknown *pUnkAggregatee = NULL;
    IUnknown *pUnkAggregator = NULL;
    IUnknown *pUnkTest = NULL;

    hr = CoCreateInstance(&clsidOuter, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IUnknown, (LPVOID*)&pUnkOuter);
    ok(hr == S_OK, "CoCreateInstance failed with %x\n", hr);
    ok(pUnkOuter != NULL, "pUnkOuter is NULL\n");

    if (!pUnkOuter)
    {
        skip("pUnkOuter is NULL\n");
        return;
    }

    /* for aggregation, we should only be able to request IUnknown */
    hr = CoCreateInstance(&clsidInner, pUnkOuter, CLSCTX_INPROC_SERVER,
                          &iidInner, (LPVOID*)&pUnkInnerFail);
    if (hr == REGDB_E_CLASSNOTREG)
    {
        skip("Class not registered\n");
        return;
    }
    ok(hr == E_NOINTERFACE, "CoCreateInstance returned %x\n", hr);
    ok(pUnkInnerFail == NULL, "pUnkInnerFail is not NULL\n");

    /* aggregation, request IUnknown */
    hr = CoCreateInstance(&clsidInner, pUnkOuter, CLSCTX_INPROC_SERVER,
                          &IID_IUnknown, (LPVOID*)&pUnkInner);
    ok(hr == S_OK, "CoCreateInstance returned %x\n", hr);
    ok(pUnkInner != NULL, "pUnkInner is NULL\n");

    if (!pUnkInner)
    {
        skip("pUnkInner is NULL\n");
        return;
    }

    ADDREF_EXPECT(pUnkOuter, 2);
    ADDREF_EXPECT(pUnkInner, 2);
    RELEASE_EXPECT(pUnkOuter, 1);
    RELEASE_EXPECT(pUnkInner, 1);

    QI_FAIL(pUnkOuter, iidInner, pUnkAggregatee);
    QI_FAIL(pUnkInner, iidOuter, pUnkAggregator);

    /* these QueryInterface calls should work */
    QI_SUCCEED(pUnkOuter, iidOuter, pUnkAggregator);
    QI_SUCCEED(pUnkOuter, IID_IUnknown, pUnkOuterTest);
    /* IGraphConfig interface comes with DirectShow 9 */
    if(IsEqualGUID(&IID_IGraphConfig, &iidInner))
    {
        hr = IUnknown_QueryInterface(pUnkInner, &iidInner, (LPVOID*)&pUnkAggregatee);
        ok(hr == S_OK || broken(hr == E_NOINTERFACE), "IUnknown_QueryInterface returned %x\n", hr);
        ok(pUnkAggregatee != NULL || broken(!pUnkAggregatee), "Pointer is NULL\n");
    }
    else
    {
        QI_SUCCEED(pUnkInner, iidInner, pUnkAggregatee);
    }
    QI_SUCCEED(pUnkInner, IID_IUnknown, pUnkInnerTest);

    if (!pUnkAggregator || !pUnkOuterTest || !pUnkAggregatee
                    || !pUnkInnerTest)
    {
        skip("One of the required interfaces is NULL\n");
        return;
    }

    ADDREF_EXPECT(pUnkAggregator, 5);
    ADDREF_EXPECT(pUnkOuterTest, 6);
    ADDREF_EXPECT(pUnkAggregatee, 7);
    ADDREF_EXPECT(pUnkInnerTest, 3);
    RELEASE_EXPECT(pUnkAggregator, 6);
    RELEASE_EXPECT(pUnkOuterTest, 5);
    RELEASE_EXPECT(pUnkAggregatee, 4);
    RELEASE_EXPECT(pUnkInnerTest, 2);

    QI_SUCCEED(pUnkAggregator, IID_IUnknown, pUnkTest);
    QI_SUCCEED(pUnkOuterTest, IID_IUnknown, pUnkTest);
    QI_SUCCEED(pUnkAggregatee, IID_IUnknown, pUnkTest);
    QI_SUCCEED(pUnkInnerTest, IID_IUnknown, pUnkTest);

    QI_FAIL(pUnkAggregator, iidInner, pUnkTest);
    QI_FAIL(pUnkOuterTest, iidInner, pUnkTest);
    QI_FAIL(pUnkAggregatee, iidInner, pUnkTest);
    QI_SUCCEED(pUnkInnerTest, iidInner, pUnkTest);

    QI_SUCCEED(pUnkAggregator, iidOuter, pUnkTest);
    QI_SUCCEED(pUnkOuterTest, iidOuter, pUnkTest);
    QI_SUCCEED(pUnkAggregatee, iidOuter, pUnkTest);
    QI_FAIL(pUnkInnerTest, iidOuter, pUnkTest);

    RELEASE_EXPECT(pUnkAggregator, 10);
    RELEASE_EXPECT(pUnkOuterTest, 9);
    RELEASE_EXPECT(pUnkAggregatee, 8);
    RELEASE_EXPECT(pUnkInnerTest, 2);
    RELEASE_EXPECT(pUnkOuter, 7);
    RELEASE_EXPECT(pUnkInner, 1);

    do
    {
        refCount = IUnknown_Release(pUnkInner);
    } while (refCount);

    do
    {
        refCount = IUnknown_Release(pUnkOuter);
    } while (refCount);
}