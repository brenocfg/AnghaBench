#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* rfc1766; int broken_lcid; int lcid; int /*<<< orphan*/  hr; } ;
typedef  int LCID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  S_FALSE ; 
 scalar_t__ broken (int) ; 
 TYPE_1__* lcid_table ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 int /*<<< orphan*/  pRfc1766ToLcidA (int*,char*) ; 

__attribute__((used)) static void test_Rfc1766ToLcid(void)
{
    LCID lcid;
    HRESULT ret;
    DWORD i;

    for(i = 0; i < ARRAY_SIZE(lcid_table); i++) {
        lcid = -1;
        ret = pRfc1766ToLcidA(&lcid, lcid_table[i].rfc1766);

        /* IE <6.0 guess 0x412 (ko) from "kok" */
        ok( (ret == lcid_table[i].hr) ||
            broken(lcid_table[i].broken_lcid && (ret == S_FALSE)),
            "#%02d: HRESULT 0x%x (expected 0x%x)\n", i, ret, lcid_table[i].hr);

        ok( (lcid == lcid_table[i].lcid) ||
            broken(lcid == lcid_table[i].broken_lcid),  /* IE <6.0 */
            "#%02d: got LCID 0x%x (expected 0x%x)\n", i, lcid, lcid_table[i].lcid);
    }

    ret = pRfc1766ToLcidA(&lcid, NULL);
    ok(ret == E_INVALIDARG, "got 0x%08x (expected E_INVALIDARG)\n", ret);

    ret = pRfc1766ToLcidA(NULL, "en");
    ok(ret == E_INVALIDARG, "got 0x%08x (expected E_INVALIDARG)\n", ret);
}