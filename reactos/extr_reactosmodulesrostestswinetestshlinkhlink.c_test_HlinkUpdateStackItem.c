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
typedef  char WCHAR ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  HBC_UpdateHlink ; 
 int /*<<< orphan*/  HLF_UpdateHlink ; 
 int /*<<< orphan*/  HLID_CURRENT ; 
 int /*<<< orphan*/  HlinkBrowseContext ; 
 scalar_t__ HlinkUpdateStackItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Moniker ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  testframe ; 

__attribute__((used)) static void test_HlinkUpdateStackItem(void)
{
    static const WCHAR location[] = {'l','o','c','a','t','i','o','n',0};
    HRESULT hr;

    hr = HlinkUpdateStackItem(NULL, NULL, HLID_CURRENT, &Moniker, location, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    SET_EXPECT(HBC_UpdateHlink);
    hr = HlinkUpdateStackItem(NULL, &HlinkBrowseContext, HLID_CURRENT, &Moniker, location, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    CHECK_CALLED(HBC_UpdateHlink);

    SET_EXPECT(HLF_UpdateHlink);
    hr = HlinkUpdateStackItem(&testframe, &HlinkBrowseContext, HLID_CURRENT, &Moniker, location, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    CHECK_CALLED(HLF_UpdateHlink);
}