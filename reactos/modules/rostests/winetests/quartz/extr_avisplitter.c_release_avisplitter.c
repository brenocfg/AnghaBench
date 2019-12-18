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
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pAviSplitter ; 

__attribute__((used)) static void release_avisplitter(void)
{
    HRESULT hr;

    Sleep(1000);
    hr = IUnknown_Release(pAviSplitter);

    /* Looks like wine has a reference leak somewhere on test_threads tests,
     * it passes in windows
     */
    ok(hr == 0, "IUnknown_Release failed with %d\n", (INT)hr);

    while (hr > 0)
        hr = IUnknown_Release(pAviSplitter);
    pAviSplitter = NULL;
}