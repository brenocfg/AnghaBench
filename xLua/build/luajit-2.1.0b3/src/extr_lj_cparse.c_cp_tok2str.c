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
typedef  scalar_t__ CPToken ;
typedef  TYPE_1__ CPState ;

/* Variables and functions */
 scalar_t__ CTOK_FIRSTDECL ; 
 scalar_t__ CTOK_OFS ; 
 char const** ctoknames ; 
 int /*<<< orphan*/  lj_char_iscntrl (scalar_t__) ; 
 char const* lj_strfmt_pushf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static const char *cp_tok2str(CPState *cp, CPToken tok)
{
  lua_assert(tok < CTOK_FIRSTDECL);
  if (tok > CTOK_OFS)
    return ctoknames[tok-CTOK_OFS-1];
  else if (!lj_char_iscntrl(tok))
    return lj_strfmt_pushf(cp->L, "%c", tok);
  else
    return lj_strfmt_pushf(cp->L, "char(%d)", tok);
}