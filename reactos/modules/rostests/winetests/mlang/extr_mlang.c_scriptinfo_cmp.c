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
struct TYPE_4__ {scalar_t__ ScriptId; scalar_t__ uiCodePage; int /*<<< orphan*/  wszProportionalFont; int /*<<< orphan*/  wszFixedWidthFont; int /*<<< orphan*/  wszDescription; } ;
typedef  TYPE_1__ SCRIPTINFO ;

/* Variables and functions */
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void scriptinfo_cmp(SCRIPTINFO *sinfo1, SCRIPTINFO *sinfo2)
{
    ok(sinfo1->ScriptId == sinfo2->ScriptId, "ScriptId mismatch: %d != %d\n", sinfo1->ScriptId, sinfo2->ScriptId);
    ok(sinfo1->uiCodePage == sinfo2->uiCodePage, "uiCodePage mismatch: %u != %u\n", sinfo1->uiCodePage, sinfo2->uiCodePage);
    ok(!lstrcmpW(sinfo1->wszDescription, sinfo2->wszDescription), "wszDescription mismatch\n");
    ok(!lstrcmpW(sinfo1->wszFixedWidthFont, sinfo2->wszFixedWidthFont), "wszFixedWidthFont mismatch\n");
    ok(!lstrcmpW(sinfo1->wszProportionalFont, sinfo2->wszProportionalFont), "wszProportionalFont mismatch\n");
}