#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* parens; int /*<<< orphan*/  const* cp; } ;
typedef  TYPE_3__ match_state_t ;
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  size_t UINT ;
struct TYPE_14__ {int skipped; scalar_t__ stateStackTop; scalar_t__ cursz; int /*<<< orphan*/  backTrackStack; int /*<<< orphan*/  backTrackSP; TYPE_2__* regexp; int /*<<< orphan*/  ok; int /*<<< orphan*/  const* cpend; } ;
struct TYPE_12__ {size_t parenCount; int flags; } ;
struct TYPE_11__ {int index; } ;
typedef  TYPE_4__ REGlobalData ;

/* Variables and functions */
 TYPE_3__* ExecuteREBytecode (TYPE_4__*,TYPE_3__*) ; 
 int REG_STICKY ; 

__attribute__((used)) static match_state_t *MatchRegExp(REGlobalData *gData, match_state_t *x)
{
    match_state_t *result;
    const WCHAR *cp = x->cp;
    const WCHAR *cp2;
    UINT j;

    /*
     * Have to include the position beyond the last character
     * in order to detect end-of-input/line condition.
     */
    for (cp2 = cp; cp2 <= gData->cpend; cp2++) {
        gData->skipped = cp2 - cp;
        x->cp = cp2;
        for (j = 0; j < gData->regexp->parenCount; j++)
            x->parens[j].index = -1;
        result = ExecuteREBytecode(gData, x);
        if (!gData->ok || result || (gData->regexp->flags & REG_STICKY))
            return result;
        gData->backTrackSP = gData->backTrackStack;
        gData->cursz = 0;
        gData->stateStackTop = 0;
        cp2 = cp + gData->skipped;
    }
    return NULL;
}