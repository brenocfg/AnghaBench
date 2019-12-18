#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int current; int /*<<< orphan*/  buff; int /*<<< orphan*/  decpoint; } ;
struct TYPE_11__ {int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  buff2d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffreplace (TYPE_2__*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ check_next (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  lisdigit (int) ; 
 scalar_t__ lisxdigit (int) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 
 int /*<<< orphan*/  trydecpoint (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void read_numeral (LexState *ls, SemInfo *seminfo) {
  const char *expo = "Ee";
  int first = ls->current;
  lua_assert(lisdigit(ls->current));
  save_and_next(ls);
  if (first == '0' && check_next(ls, "Xx"))  /* hexadecimal? */
    expo = "Pp";
  for (;;) {
    if (check_next(ls, expo))  /* exponent part? */
      (void) check_next(ls, "+-");  /* optional exponent sign */
    if (lisxdigit(ls->current) || ls->current == '.')
      save_and_next(ls);
    else  break;
  }
  save(ls, '\0');
  buffreplace(ls, '.', ls->decpoint);  /* follow locale for decimal point */
  if (!buff2d(ls->buff, &seminfo->r))  /* format error? */
    trydecpoint(ls, seminfo); /* try to update decimal point separator */
}