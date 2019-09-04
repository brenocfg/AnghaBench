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
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ ralf; int blwf; int base; size_t start; int end; scalar_t__ pref; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 
 scalar_t__ lex_Matra_below ; 
 scalar_t__ lex_Matra_post ; 

__attribute__((used)) static void Reorder_Ra_follows_matra(WCHAR *pwChar, IndicSyllable *s, lexical_function lexical)
{
    if (s->ralf >= 0)
    {
        int j,loc;
        int stop = (s->blwf >=0)? s->blwf+1 : s->base;
        WORD Ra = pwChar[s->start];
        WORD H = pwChar[s->start+1];
        for (loc = s->end; loc > stop; loc--)
            if (lexical(pwChar[loc]) == lex_Matra_post || lexical(pwChar[loc]) == lex_Matra_below)
                break;

        TRACE("Doing reorder of Ra to %i\n",loc);
        for (j = s->start; j < loc-1; j++)
            pwChar[j] = pwChar[j+2];
        pwChar[loc-1] = Ra;
        pwChar[loc] = H;

        s->ralf = loc-1;
        s->base -= 2;
        if (s->blwf >= 0) s->blwf -= 2;
        if (s->pref >= 0) s->pref -= 2;
    }
}