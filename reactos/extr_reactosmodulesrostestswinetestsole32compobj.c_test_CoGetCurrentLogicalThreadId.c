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
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ CoGetCurrentLogicalThreadId (int /*<<< orphan*/ *) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_CoGetCurrentLogicalThreadId(void)
{
    HRESULT hr;
    GUID id;

    hr = CoGetCurrentLogicalThreadId(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    id = GUID_NULL;
    hr = CoGetCurrentLogicalThreadId(&id);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!IsEqualGUID(&id, &GUID_NULL), "got null id\n");
}