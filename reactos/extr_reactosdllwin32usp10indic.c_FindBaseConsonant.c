#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int ralf; int start; size_t base; int end; int blwf; int pref; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_1__ IndicSyllable ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ Consonant_is_below_base_form (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/  const),scalar_t__) ; 
 scalar_t__ Consonant_is_post_base_form (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/  const),scalar_t__) ; 
 scalar_t__ Consonant_is_pre_base_form (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/  const),scalar_t__) ; 
 scalar_t__ Consonant_is_ralf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  (*) (int /*<<< orphan*/  const)) ; 
 scalar_t__ FALSE ; 
 scalar_t__ is_consonant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FindBaseConsonant(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache *psc,
        const WCHAR *input, IndicSyllable *s, lexical_function lex, BOOL modern)
{
    int i;
    BOOL blwf = FALSE;
    BOOL pref = FALSE;

    /* remove ralf from consideration */
    if (Consonant_is_ralf(hdc, psa, psc, input, s, lex))
    {
        s->ralf = s->start;
        s->start+=2;
    }

    /* try to find a base consonant */
    if (!is_consonant( lex(input[s->base]) ))
    {
        for (i = s->end; i >= s->start; i--)
            if (is_consonant( lex(input[i]) ))
            {
                s->base = i;
                break;
            }
    }

    while ((blwf = Consonant_is_below_base_form(hdc, psa, psc, input, s, lex, modern)) || Consonant_is_post_base_form(hdc, psa, psc, input, s, lex, modern) || (pref = Consonant_is_pre_base_form(hdc, psa, psc, input, s, lex, modern)))
    {
        if (blwf && s->blwf == -1)
            s->blwf = s->base - 1;
        if (pref && s->pref == -1)
            s->pref = s->base - 1;

        for (i = s->base-1; i >= s->start; i--)
            if (is_consonant( lex(input[i]) ))
            {
                s->base = i;
                break;
            }
    }

    if (s->ralf >= 0)
        s->start = s->ralf;

    if (s->ralf == s->base)
        s->ralf = -1;

    return s->base;
}