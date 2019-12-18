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
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int HRESULT ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pSHCreateThreadRef (int*,int /*<<< orphan*/ **) ; 
 int pSHGetThreadRef (int /*<<< orphan*/ **) ; 
 int pSHSetThreadRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHCreateThreadRef(void)
{
    IUnknown *pobj;
    IUnknown *punk;
    LONG refcount;
    HRESULT hr;

    /* Not present before IE 6_XP_sp2 */
    if (!pSHCreateThreadRef) {
        win_skip("SHCreateThreadRef not found\n");
        return;
    }

    /* start with a clean state */
    hr = pSHSetThreadRef(NULL);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    pobj = NULL;
    refcount = 0xdeadbeef;
    hr = pSHCreateThreadRef(&refcount, &pobj);
    ok((hr == S_OK) && pobj && (refcount == 1),
        "got 0x%x and %p with %d (expected S_OK and '!= NULL' with 1)\n",
        hr, pobj, refcount);

    /* the object is not automatic set as ThreadRef */
    punk = NULL;
    hr = pSHGetThreadRef(&punk);
    ok( (hr == E_NOINTERFACE) && (punk == NULL),
        "got 0x%x and %p (expected E_NOINTERFACE and NULL)\n", hr, punk);

    /* set the object */
    hr = pSHSetThreadRef(pobj);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    /* read back */
    punk = NULL;
    hr = pSHGetThreadRef(&punk);
    ok( (hr == S_OK) && (punk == pobj) && (refcount == 2),
        "got 0x%x and %p with %d (expected S_OK and %p with 2)\n",
        hr, punk, refcount, pobj);

    /* free the ref from SHGetThreadRef */
    if (SUCCEEDED(hr)) {
        hr = IUnknown_Release(pobj);
        ok((hr == 1) && (hr == refcount),
            "got %d with %d (expected 1 with 1)\n", hr, refcount);
    }

    /* free the object */
    if (pobj) {
        hr = IUnknown_Release(pobj);
        ok((hr == 0) && (hr == refcount),
            "got %d with %d (expected 0 with 0)\n", hr, refcount);
    }

    if (0) {
        /* the ThreadRef has still the pointer,
           but the object no longer exist after the *_Release */
        punk = NULL;
        hr = pSHGetThreadRef(&punk);
        trace("got 0x%x and %p with %d\n", hr, punk, refcount);
    }

    /* remove the dead object pointer */
    hr = pSHSetThreadRef(NULL);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    /* parameter check */
    if (0) {
        /* vista: E_INVALIDARG, XP: crash */
        pobj = NULL;
        hr = pSHCreateThreadRef(NULL, &pobj);
        ok(hr == E_INVALIDARG, "got 0x%x (expected E_INVALIDARG)\n", hr);

        refcount = 0xdeadbeef;
        /* vista: E_INVALIDARG, XP: crash */
        hr = pSHCreateThreadRef(&refcount, NULL);
        ok( (hr == E_INVALIDARG) && (refcount == 0xdeadbeef),
            "got 0x%x with 0x%x (expected E_INVALIDARG and oxdeadbeef)\n",
            hr, refcount);
    }
}