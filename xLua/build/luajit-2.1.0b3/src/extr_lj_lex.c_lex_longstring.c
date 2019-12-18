#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int c; int /*<<< orphan*/  L; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int MSize ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
#define  LEX_EOF 128 
 int /*<<< orphan*/  LJ_ERR_XLCOM ; 
 int /*<<< orphan*/  LJ_ERR_XLSTR ; 
 int /*<<< orphan*/  TK_eof ; 
 scalar_t__ lex_iseol (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_newline (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_save (TYPE_1__*,char) ; 
 int /*<<< orphan*/  lex_savenext (TYPE_1__*) ; 
 int lex_skipeq (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_buf_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lj_parse_keepstr (TYPE_1__*,int,scalar_t__) ; 
 int sbufB (int /*<<< orphan*/ *) ; 
 scalar_t__ sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setstrV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lex_longstring(LexState *ls, TValue *tv, int sep)
{
  lex_savenext(ls);  /* Skip second '['. */
  if (lex_iseol(ls))  /* Skip initial newline. */
    lex_newline(ls);
  for (;;) {
    switch (ls->c) {
    case LEX_EOF:
      lj_lex_error(ls, TK_eof, tv ? LJ_ERR_XLSTR : LJ_ERR_XLCOM);
      break;
    case ']':
      if (lex_skipeq(ls) == sep) {
	lex_savenext(ls);  /* Skip second ']'. */
	goto endloop;
      }
      break;
    case '\n':
    case '\r':
      lex_save(ls, '\n');
      lex_newline(ls);
      if (!tv) lj_buf_reset(&ls->sb);  /* Don't waste space for comments. */
      break;
    default:
      lex_savenext(ls);
      break;
    }
  } endloop:
  if (tv) {
    GCstr *str = lj_parse_keepstr(ls, sbufB(&ls->sb) + (2 + (MSize)sep),
				      sbuflen(&ls->sb) - 2*(2 + (MSize)sep));
    setstrV(ls->L, tv, str);
  }
}