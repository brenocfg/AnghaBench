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
struct TYPE_10__ {int c; int /*<<< orphan*/  sb; int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ LexState ;
typedef  int LexChar ;

/* Variables and functions */
#define  LEX_EOF 128 
 int /*<<< orphan*/  LJ_ERR_XESC ; 
 int /*<<< orphan*/  LJ_ERR_XSTR ; 
 int /*<<< orphan*/  TK_eof ; 
 int /*<<< orphan*/  TK_string ; 
 int /*<<< orphan*/  lex_iseol (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_newline (TYPE_1__*) ; 
 int lex_next (TYPE_1__*) ; 
 int /*<<< orphan*/  lex_save (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lex_savenext (TYPE_1__*) ; 
 int /*<<< orphan*/  lj_char_isdigit (int) ; 
 int /*<<< orphan*/  lj_char_isspace (int) ; 
 int /*<<< orphan*/  lj_char_isxdigit (int) ; 
 int /*<<< orphan*/  lj_lex_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_parse_keepstr (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ sbufB (int /*<<< orphan*/ *) ; 
 scalar_t__ sbuflen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setstrV (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lex_string(LexState *ls, TValue *tv)
{
  LexChar delim = ls->c;  /* Delimiter is '\'' or '"'. */
  lex_savenext(ls);
  while (ls->c != delim) {
    switch (ls->c) {
    case LEX_EOF:
      lj_lex_error(ls, TK_eof, LJ_ERR_XSTR);
      continue;
    case '\n':
    case '\r':
      lj_lex_error(ls, TK_string, LJ_ERR_XSTR);
      continue;
    case '\\': {
      LexChar c = lex_next(ls);  /* Skip the '\\'. */
      switch (c) {
      case 'a': c = '\a'; break;
      case 'b': c = '\b'; break;
      case 'f': c = '\f'; break;
      case 'n': c = '\n'; break;
      case 'r': c = '\r'; break;
      case 't': c = '\t'; break;
      case 'v': c = '\v'; break;
      case 'x':  /* Hexadecimal escape '\xXX'. */
	c = (lex_next(ls) & 15u) << 4;
	if (!lj_char_isdigit(ls->c)) {
	  if (!lj_char_isxdigit(ls->c)) goto err_xesc;
	  c += 9 << 4;
	}
	c += (lex_next(ls) & 15u);
	if (!lj_char_isdigit(ls->c)) {
	  if (!lj_char_isxdigit(ls->c)) goto err_xesc;
	  c += 9;
	}
	break;
      case 'u':  /* Unicode escape '\u{XX...}'. */
	if (lex_next(ls) != '{') goto err_xesc;
	lex_next(ls);
	c = 0;
	do {
	  c = (c << 4) | (ls->c & 15u);
	  if (!lj_char_isdigit(ls->c)) {
	    if (!lj_char_isxdigit(ls->c)) goto err_xesc;
	    c += 9;
	  }
	  if (c >= 0x110000) goto err_xesc;  /* Out of Unicode range. */
	} while (lex_next(ls) != '}');
	if (c < 0x800) {
	  if (c < 0x80) break;
	  lex_save(ls, 0xc0 | (c >> 6));
	} else {
	  if (c >= 0x10000) {
	    lex_save(ls, 0xf0 | (c >> 18));
	    lex_save(ls, 0x80 | ((c >> 12) & 0x3f));
	  } else {
	    if (c >= 0xd800 && c < 0xe000) goto err_xesc;  /* No surrogates. */
	    lex_save(ls, 0xe0 | (c >> 12));
	  }
	  lex_save(ls, 0x80 | ((c >> 6) & 0x3f));
	}
	c = 0x80 | (c & 0x3f);
	break;
      case 'z':  /* Skip whitespace. */
	lex_next(ls);
	while (lj_char_isspace(ls->c))
	  if (lex_iseol(ls)) lex_newline(ls); else lex_next(ls);
	continue;
      case '\n': case '\r': lex_save(ls, '\n'); lex_newline(ls); continue;
      case '\\': case '\"': case '\'': break;
      case LEX_EOF: continue;
      default:
	if (!lj_char_isdigit(c))
	  goto err_xesc;
	c -= '0';  /* Decimal escape '\ddd'. */
	if (lj_char_isdigit(lex_next(ls))) {
	  c = c*10 + (ls->c - '0');
	  if (lj_char_isdigit(lex_next(ls))) {
	    c = c*10 + (ls->c - '0');
	    if (c > 255) {
	    err_xesc:
	      lj_lex_error(ls, TK_string, LJ_ERR_XESC);
	    }
	    lex_next(ls);
	  }
	}
	lex_save(ls, c);
	continue;
      }
      lex_save(ls, c);
      lex_next(ls);
      continue;
      }
    default:
      lex_savenext(ls);
      break;
    }
  }
  lex_savenext(ls);  /* Skip trailing delimiter. */
  setstrV(ls->L, tv,
	  lj_parse_keepstr(ls, sbufB(&ls->sb)+1, sbuflen(&ls->sb)-2));
}