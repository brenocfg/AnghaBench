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
typedef  int (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
#define  lex_Anudatta 142 
#define  lex_Composed_Vowel 141 
#define  lex_Consonant 140 
#define  lex_Halant 139 
#define  lex_Matra_above 138 
#define  lex_Matra_below 137 
#define  lex_Matra_post 136 
#define  lex_Matra_pre 135 
#define  lex_Modifier 134 
#define  lex_Nukta 133 
#define  lex_Ra 132 
#define  lex_Vedic 131 
#define  lex_Vowel 130 
#define  lex_ZWJ 129 
#define  lex_ZWNJ 128 
 int /*<<< orphan*/  uniscribe ; 

__attribute__((used)) static void debug_output_string(const WCHAR *str, unsigned int char_count, lexical_function f)
{
    int i;
    if (TRACE_ON(uniscribe))
    {
        for (i = 0; i < char_count; ++i)
        {
            switch (f(str[i]))
            {
                case lex_Consonant: TRACE("C"); break;
                case lex_Ra: TRACE("Ra"); break;
                case lex_Vowel: TRACE("V"); break;
                case lex_Nukta: TRACE("N"); break;
                case lex_Halant: TRACE("H"); break;
                case lex_ZWNJ: TRACE("Zwnj"); break;
                case lex_ZWJ: TRACE("Zwj"); break;
                case lex_Matra_post: TRACE("Mp");break;
                case lex_Matra_above: TRACE("Ma");break;
                case lex_Matra_below: TRACE("Mb");break;
                case lex_Matra_pre: TRACE("Mm");break;
                case lex_Modifier: TRACE("Sm"); break;
                case lex_Vedic: TRACE("Vd"); break;
                case lex_Anudatta: TRACE("A"); break;
                case lex_Composed_Vowel: TRACE("t"); break;
                default:
                    TRACE("X"); break;
            }
        }
        TRACE("\n");
    }
}