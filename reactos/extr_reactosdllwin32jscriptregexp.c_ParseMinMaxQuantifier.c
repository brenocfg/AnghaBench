#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ max; scalar_t__ min; } ;
struct TYPE_9__ {TYPE_1__ range; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
struct TYPE_10__ {char* cp; int /*<<< orphan*/  progLength; TYPE_5__* result; } ;
typedef  int INT ;
typedef  TYPE_3__ CompilerState ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ GetCompactIndexWidth (scalar_t__) ; 
 scalar_t__ GetDecimalValue (char,int,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ JS7_ISDEC (char) ; 
 int JSMSG_MAX_TOO_BIG ; 
 int JSMSG_MIN_TOO_BIG ; 
 int JSMSG_OUT_OF_MEMORY ; 
 int JSMSG_OUT_OF_ORDER ; 
 TYPE_5__* NewRENode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OVERFLOW_VALUE ; 
 int /*<<< orphan*/  REOP_QUANT ; 

__attribute__((used)) static INT
ParseMinMaxQuantifier(CompilerState *state, BOOL ignoreValues)
{
    UINT min, max;
    WCHAR c;
    const WCHAR *errp = state->cp++;

    c = *state->cp;
    if (JS7_ISDEC(c)) {
        ++state->cp;
        min = GetDecimalValue(c, 0xFFFF, NULL, state);
        c = *state->cp;

        if (!ignoreValues && min == OVERFLOW_VALUE)
            return JSMSG_MIN_TOO_BIG;

        if (c == ',') {
            c = *++state->cp;
            if (JS7_ISDEC(c)) {
                ++state->cp;
                max = GetDecimalValue(c, 0xFFFF, NULL, state);
                c = *state->cp;
                if (!ignoreValues && max == OVERFLOW_VALUE)
                    return JSMSG_MAX_TOO_BIG;
                if (!ignoreValues && min > max)
                    return JSMSG_OUT_OF_ORDER;
            } else {
                max = (UINT)-1;
            }
        } else {
            max = min;
        }
        if (c == '}') {
            state->result = NewRENode(state, REOP_QUANT);
            if (!state->result)
                return JSMSG_OUT_OF_MEMORY;
            state->result->u.range.min = min;
            state->result->u.range.max = max;
            /*
             * QUANT, <min>, <max>, <next> ... <ENDCHILD>
             * where <max> is written as compact(max+1) to make
             * (UINT)-1 sentinel to occupy 1 byte, not width_of(max)+1.
             */
            state->progLength += (1 + GetCompactIndexWidth(min)
                                  + GetCompactIndexWidth(max + 1)
                                  +3);
            return 0;
        }
    }

    state->cp = errp;
    return -1;
}