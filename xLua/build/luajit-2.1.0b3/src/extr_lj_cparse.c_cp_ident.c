#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  info; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_3__* ct; int /*<<< orphan*/  tmask; int /*<<< orphan*/  str; int /*<<< orphan*/  cts; TYPE_1__ val; int /*<<< orphan*/  sb; int /*<<< orphan*/  L; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  CPToken ;
typedef  TYPE_2__ CPState ;

/* Variables and functions */
 int /*<<< orphan*/  CTOK_IDENT ; 
 scalar_t__ CT_KW ; 
 int /*<<< orphan*/  cp_get (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_save (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_cid (int /*<<< orphan*/ ) ; 
 scalar_t__ ctype_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_buf_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lj_char_isident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_ctype_getname (int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CPToken cp_ident(CPState *cp)
{
  do { cp_save(cp, cp->c); } while (lj_char_isident(cp_get(cp)));
  cp->str = lj_buf_str(cp->L, &cp->sb);
  cp->val.id = lj_ctype_getname(cp->cts, &cp->ct, cp->str, cp->tmask);
  if (ctype_type(cp->ct->info) == CT_KW)
    return ctype_cid(cp->ct->info);
  return CTOK_IDENT;
}