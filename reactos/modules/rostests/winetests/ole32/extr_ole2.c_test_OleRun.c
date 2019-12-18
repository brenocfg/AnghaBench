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
typedef  int HRESULT ;

/* Variables and functions */
 int OleRun (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  testrunnable ; 
 int /*<<< orphan*/  unknown ; 

__attribute__((used)) static void test_OleRun(void)
{
    HRESULT hr;

    /* doesn't support IRunnableObject */
    hr = OleRun(&unknown);
    ok(hr == S_OK, "OleRun failed 0x%08x\n", hr);

    hr = OleRun((IUnknown*)&testrunnable);
    ok(hr == 0xdeadc0de, "got 0x%08x\n", hr);
}