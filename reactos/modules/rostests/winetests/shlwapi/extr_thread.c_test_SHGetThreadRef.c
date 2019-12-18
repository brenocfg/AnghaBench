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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pSHGetThreadRef (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHGetThreadRef(void)
{
    IUnknown *punk;
    HRESULT hr;

    /* Not present before IE 5 */
    if (!pSHGetThreadRef) {
        win_skip("SHGetThreadRef not found\n");
        return;
    }

    punk = NULL;
    hr = pSHGetThreadRef(&punk);
    ok( (hr == E_NOINTERFACE) && (punk == NULL),
        "got 0x%x and %p (expected E_NOINTERFACE and NULL)\n", hr, punk);

    if (0) {
        /* this crash on Windows */
        pSHGetThreadRef(NULL);
    }
}