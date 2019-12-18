#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  top; } ;
struct TYPE_10__ {int /*<<< orphan*/ * redir; } ;
struct TYPE_9__ {scalar_t__ tok; TYPE_3__* L; int /*<<< orphan*/ * str; } ;
typedef  int /*<<< orphan*/  GCstr ;
typedef  TYPE_1__ CPState ;
typedef  TYPE_2__ CPDecl ;

/* Variables and functions */
 scalar_t__ CTOK_STRING ; 
 int /*<<< orphan*/  UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_check (TYPE_1__*,char) ; 
 scalar_t__ cp_next (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_strfmt_pushf (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cp_decl_asm(CPState *cp, CPDecl *decl)
{
  UNUSED(decl);
  cp_next(cp);
  cp_check(cp, '(');
  if (cp->tok == CTOK_STRING) {
    GCstr *str = cp->str;
    while (cp_next(cp) == CTOK_STRING) {
      lj_strfmt_pushf(cp->L, "%s%s", strdata(str), strdata(cp->str));
      cp->L->top--;
      str = strV(cp->L->top);
    }
    decl->redir = str;
  }
  cp_check(cp, ')');
}