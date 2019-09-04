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
typedef  int WCHAR ;

/* Variables and functions */
 int get_table_entry (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  indic_syllabic_table ; 
 int lex_Composed_Vowel ; 
 int lex_Consonant ; 
 int lex_Generic ; 
 int lex_Halant ; 
 int lex_Matra_above ; 
 int lex_Matra_below ; 
 int lex_Matra_post ; 
 int lex_Matra_pre ; 
 int lex_Modifier ; 
 int lex_NBSP ; 
 int lex_Nukta ; 
 int lex_Ra ; 
 int lex_Vowel ; 
 int lex_ZWJ ; 
 int lex_ZWNJ ; 

__attribute__((used)) static inline int unicode_lex(WCHAR c)
{
    int type;

    if (!c) return lex_Generic;
    if (c == 0x200D) return lex_ZWJ;
    if (c == 0x200C) return lex_ZWNJ;
    if (c == 0x00A0) return lex_NBSP;

    type = get_table_entry( indic_syllabic_table, c );

    if ((type & 0x00ff) != 0x0007)  type = type & 0x00ff;

    switch( type )
    {
        case 0x0d07: /* Unknown */
        case 0x0e07: /* Unknown */
        default: return lex_Generic;
        case 0x0001:
        case 0x0002:
        case 0x0011:
        case 0x0012:
        case 0x0013:
        case 0x0014: return lex_Modifier;
        case 0x0003:
        case 0x0009:
        case 0x000a:
        case 0x000b:
        case 0x000d:
        case 0x000e:
        case 0x000f:
        case 0x0010: return lex_Consonant;
        case 0x0004: return lex_Nukta;
        case 0x0005: return lex_Halant;
        case 0x0006:
        case 0x0008: return lex_Vowel;
        case 0x0007:
        case 0x0107: return lex_Matra_post;
        case 0x0207:
        case 0x0307: return lex_Matra_pre;
        case 0x0807:
        case 0x0907:
        case 0x0a07:
        case 0x0b07:
        case 0x0c07:
        case 0x0407: return lex_Composed_Vowel;
        case 0x0507: return lex_Matra_above;
        case 0x0607: return lex_Matra_below;
        case 0x000c:
        case 0x0015: return lex_Ra;
    };
}