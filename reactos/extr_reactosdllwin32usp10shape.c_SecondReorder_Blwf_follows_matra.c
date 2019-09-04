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
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ blwf; scalar_t__ base; int end; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 scalar_t__ lex_Matra_above ; 
 scalar_t__ lex_Matra_below ; 
 scalar_t__ lex_Matra_post ; 

__attribute__((used)) static void SecondReorder_Blwf_follows_matra(const WCHAR *chars, const IndicSyllable *s,
        WORD *glyphs, const IndicSyllable *g, lexical_function lexical)
{
    if (s->blwf >= 0 && g->blwf > g->base)
    {
        int j,loc;
        int g_offset;
        for (loc = s->end; loc > s->blwf; loc--)
            if (lexical(chars[loc]) == lex_Matra_below || lexical(chars[loc]) == lex_Matra_above
                    || lexical(chars[loc]) == lex_Matra_post)
                break;

        g_offset = (loc - s->blwf) - 1;

        if (loc != s->blwf)
        {
            WORD blwf = glyphs[g->blwf];
            TRACE("Doing reorder of Below-base to %i (glyph offset %i)\n",loc,g_offset);
            /* do not care about the pwChar array anymore, just the glyphs */
            for (j = 0; j < g_offset; j++)
                glyphs[g->blwf + j] = glyphs[g->blwf + j + 1];
            glyphs[g->blwf + g_offset] = blwf;
        }
    }
}