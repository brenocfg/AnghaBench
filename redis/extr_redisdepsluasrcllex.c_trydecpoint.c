#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lconv {char* decimal_point; } ;
struct TYPE_8__ {char decpoint; int /*<<< orphan*/  buff; } ;
struct TYPE_7__ {int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_NUMBER ; 
 int /*<<< orphan*/  buffreplace (TYPE_2__*,char,char) ; 
 struct lconv* localeconv () ; 
 int /*<<< orphan*/  luaO_str2d (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_lexerror (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trydecpoint (LexState *ls, SemInfo *seminfo) {
  /* format error: try to update decimal point separator */
  struct lconv *cv = localeconv();
  char old = ls->decpoint;
  ls->decpoint = (cv ? cv->decimal_point[0] : '.');
  buffreplace(ls, old, ls->decpoint);  /* try updated decimal separator */
  if (!luaO_str2d(luaZ_buffer(ls->buff), &seminfo->r)) {
    /* format error with correct decimal point: no more options */
    buffreplace(ls, ls->decpoint, '.');  /* undo change (for error message) */
    luaX_lexerror(ls, "malformed number", TK_NUMBER);
  }
}