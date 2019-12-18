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
struct TYPE_4__ {scalar_t__ dwFlags; scalar_t__ uiCodePage; scalar_t__ uiFamilyCodePage; scalar_t__ bGDICharset; int /*<<< orphan*/  wszProportionalFont; int /*<<< orphan*/  wszFixedWidthFont; int /*<<< orphan*/  wszBodyCharset; int /*<<< orphan*/  wszHeaderCharset; int /*<<< orphan*/  wszWebCharset; int /*<<< orphan*/  wszDescription; } ;
typedef  TYPE_1__ MIMECPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void cpinfo_cmp(MIMECPINFO *cpinfo1, MIMECPINFO *cpinfo2)
{
    ok(cpinfo1->dwFlags == cpinfo2->dwFlags, "dwFlags mismatch: %08x != %08x\n", cpinfo1->dwFlags, cpinfo2->dwFlags);
    ok(cpinfo1->uiCodePage == cpinfo2->uiCodePage, "uiCodePage mismatch: %u != %u\n", cpinfo1->uiCodePage, cpinfo2->uiCodePage);
    ok(cpinfo1->uiFamilyCodePage == cpinfo2->uiFamilyCodePage, "uiFamilyCodePage mismatch: %u != %u\n", cpinfo1->uiFamilyCodePage, cpinfo2->uiFamilyCodePage);
    ok(!lstrcmpW(cpinfo1->wszDescription, cpinfo2->wszDescription), "wszDescription mismatch\n");
    ok(!lstrcmpW(cpinfo1->wszWebCharset, cpinfo2->wszWebCharset), "wszWebCharset mismatch\n");
    ok(!lstrcmpW(cpinfo1->wszHeaderCharset, cpinfo2->wszHeaderCharset), "wszHeaderCharset mismatch\n");
    ok(!lstrcmpW(cpinfo1->wszBodyCharset, cpinfo2->wszBodyCharset), "wszBodyCharset mismatch\n");
    ok(!lstrcmpW(cpinfo1->wszFixedWidthFont, cpinfo2->wszFixedWidthFont), "wszFixedWidthFont mismatch\n");
    ok(!lstrcmpW(cpinfo1->wszProportionalFont, cpinfo2->wszProportionalFont), "wszProportionalFont mismatch\n");
    ok(cpinfo1->bGDICharset == cpinfo2->bGDICharset, "bGDICharset mismatch: %d != %d\n", cpinfo1->bGDICharset, cpinfo2->bGDICharset);
}