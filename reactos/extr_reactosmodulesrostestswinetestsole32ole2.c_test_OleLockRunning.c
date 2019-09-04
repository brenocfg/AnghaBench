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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OleLockRunning (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  unknown ; 

__attribute__((used)) static void test_OleLockRunning(void)
{
    HRESULT hr;

    hr = OleLockRunning(&unknown, TRUE, FALSE);
    ok(hr == S_OK, "OleLockRunning failed 0x%08x\n", hr);
}