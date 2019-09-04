#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {scalar_t__ fccHandler; scalar_t__ fccType; int /*<<< orphan*/  szName; } ;
typedef  TYPE_1__ ICINFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int ICInfo (scalar_t__,scalar_t__,TYPE_1__*) ; 
 scalar_t__ ICTYPE_VIDEO ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmioFOURCC (float,char,char,char) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ICInfo(void)
{
    ICINFO info, info2;
    DWORD i, found;
    unsigned char *fcc;

    for (i = found = 0; ICInfo(0, i, &info); i++)
    {
        trace("Codec name: %s, fccHandler: 0x%08x\n", wine_dbgstr_w(info.szName), info.fccHandler);
        ok(info.fccType, "expected nonzero fccType\n");

        ok(ICInfo(info.fccType, info.fccHandler, &info2),
           "ICInfo failed on fcc 0x%08x\n", info.fccHandler);

        fcc = (unsigned char *)&info.fccHandler;
        if (!isalpha(fcc[0])) continue;

        found++;
        /* Test getting info with a different case - bug 41602 */
        fcc[0] ^= 0x20;
        ok(ICInfo(info.fccType, info.fccHandler, &info2),
           "ICInfo failed on fcc 0x%08x\n", info.fccHandler);
    }
    ok(found != 0, "expected at least one codec\n");

    memset(&info, 0, sizeof(info));
    ok(!ICInfo(ICTYPE_VIDEO, mmioFOURCC('f','a','k','e'), &info), "expected failure\n");
    ok(info.fccType == ICTYPE_VIDEO, "got 0x%08x\n", info.fccType);
    ok(info.fccHandler == mmioFOURCC('f','a','k','e'), "got 0x%08x\n", info.fccHandler);
}