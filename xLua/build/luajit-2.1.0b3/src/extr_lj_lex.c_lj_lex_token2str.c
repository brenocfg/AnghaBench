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
struct TYPE_3__ {int /*<<< orphan*/  L; } ;
typedef  scalar_t__ LexToken ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 scalar_t__ TK_OFS ; 
 int /*<<< orphan*/  lj_char_iscntrl (scalar_t__) ; 
 char const* lj_strfmt_pushf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char const** tokennames ; 

const char *lj_lex_token2str(LexState *ls, LexToken tok)
{
  if (tok > TK_OFS)
    return tokennames[tok-TK_OFS-1];
  else if (!lj_char_iscntrl(tok))
    return lj_strfmt_pushf(ls->L, "%c", tok);
  else
    return lj_strfmt_pushf(ls->L, "char(%d)", tok);
}