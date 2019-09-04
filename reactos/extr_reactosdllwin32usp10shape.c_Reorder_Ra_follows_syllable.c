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
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ ralf; size_t start; int end; int base; scalar_t__ blwf; scalar_t__ pref; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static void Reorder_Ra_follows_syllable(WCHAR *pwChar, IndicSyllable *s, lexical_function lexical)
{
    if (s->ralf >= 0)
    {
        int j;
        WORD Ra = pwChar[s->start];
        WORD H = pwChar[s->start+1];

        TRACE("Doing reorder of Ra to %i\n",s->end-1);
        for (j = s->start; j < s->end-1; j++)
            pwChar[j] = pwChar[j+2];
        pwChar[s->end-1] = Ra;
        pwChar[s->end] = H;

        s->ralf = s->end-1;
        s->base -= 2;
        if (s->blwf >= 0) s->blwf -= 2;
        if (s->pref >= 0) s->pref -= 2;
    }
}