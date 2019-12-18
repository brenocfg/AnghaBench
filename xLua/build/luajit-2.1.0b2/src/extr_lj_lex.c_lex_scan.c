#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ reserved; } ;
struct TYPE_16__ {int c; int /*<<< orphan*/  sb; int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  char LexToken ;
typedef  TYPE_1__ LexState ;
typedef  char LexChar ;
typedef  TYPE_2__ GCstr ;

/* Variables and functions */
#define  LEX_EOF 128 
 int /*<<< orphan*/  LJ_ERR_XLDELIM ; 
 char TK_OFS ; 
 char TK_concat ; 
 char TK_dots ; 
 char TK_eof ; 
 char TK_eq ; 
 char TK_ge ; 
 char TK_label ; 
 char TK_le ; 
 char TK_name ; 
 char TK_ne ; 
 char TK_number ; 
 char TK_string ; 
 int /*<<< orphan*/  lex_iseol (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_longstring (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lex_newline (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_number (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char lex_savenext (TYPE_1__*) ; 
 int lex_skipeq (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_string (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_buf_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ lj_char_isdigit (int) ; 
 scalar_t__ lj_char_isident (int) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_1__*,char,int /*<<< orphan*/ ) ; 
 TYPE_2__* lj_parse_keepstr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbufB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setstrV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static LexToken lex_scan(LexState *ls, TValue *tv)
{
  lj_buf_reset(&ls->sb);
  for (;;) {
    if (lj_char_isident(ls->c)) {
      GCstr *s;
      if (lj_char_isdigit(ls->c)) {  /* Numeric literal. */
	lex_number(ls, tv);
	return TK_number;
      }
      /* Identifier or reserved word. */
      do {
	lex_savenext(ls);
      } while (lj_char_isident(ls->c));
      s = lj_parse_keepstr(ls, sbufB(&ls->sb), sbuflen(&ls->sb));
      setstrV(ls->L, tv, s);
      if (s->reserved > 0)  /* Reserved word? */
	return TK_OFS + s->reserved;
      return TK_name;
    }
    switch (ls->c) {
    case '\n':
    case '\r':
      lex_newline(ls);
      continue;
    case ' ':
    case '\t':
    case '\v':
    case '\f':
      lex_next(ls);
      continue;
    case '-':
      lex_next(ls);
      if (ls->c != '-') return '-';
      lex_next(ls);
      if (ls->c == '[') {  /* Long comment "--[=*[...]=*]". */
	int sep = lex_skipeq(ls);
	lj_buf_reset(&ls->sb);  /* `lex_skipeq' may dirty the buffer */
	if (sep >= 0) {
	  lex_longstring(ls, NULL, sep);
	  lj_buf_reset(&ls->sb);
	  continue;
	}
      }
      /* Short comment "--.*\n". */
      while (!lex_iseol(ls) && ls->c != LEX_EOF)
	lex_next(ls);
      continue;
    case '[': {
      int sep = lex_skipeq(ls);
      if (sep >= 0) {
	lex_longstring(ls, tv, sep);
	return TK_string;
      } else if (sep == -1) {
	return '[';
      } else {
	lj_lex_error(ls, TK_string, LJ_ERR_XLDELIM);
	continue;
      }
      }
    case '=':
      lex_next(ls);
      if (ls->c != '=') return '='; else { lex_next(ls); return TK_eq; }
    case '<':
      lex_next(ls);
      if (ls->c != '=') return '<'; else { lex_next(ls); return TK_le; }
    case '>':
      lex_next(ls);
      if (ls->c != '=') return '>'; else { lex_next(ls); return TK_ge; }
    case '~':
      lex_next(ls);
      if (ls->c != '=') return '~'; else { lex_next(ls); return TK_ne; }
    case ':':
      lex_next(ls);
      if (ls->c != ':') return ':'; else { lex_next(ls); return TK_label; }
    case '"':
    case '\'':
      lex_string(ls, tv);
      return TK_string;
    case '.':
      if (lex_savenext(ls) == '.') {
	lex_next(ls);
	if (ls->c == '.') {
	  lex_next(ls);
	  return TK_dots;   /* ... */
	}
	return TK_concat;   /* .. */
      } else if (!lj_char_isdigit(ls->c)) {
	return '.';
      } else {
	lex_number(ls, tv);
	return TK_number;
      }
    case LEX_EOF:
      return TK_eof;
    default: {
      LexChar c = ls->c;
      lex_next(ls);
      return c;  /* Single-char tokens (+ - / ...). */
    }
    }
  }
}