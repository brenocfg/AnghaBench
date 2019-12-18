#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_23__ {TYPE_1__* ts; } ;
struct TYPE_22__ {int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ TString ;
typedef  TYPE_2__ SemInfo ;
typedef  TYPE_3__ LexState ;

/* Variables and functions */
#define  EOZ 128 
 int FIRST_RESERVED ; 
 int TK_CONCAT ; 
 int TK_DBCOLON ; 
 int TK_DOTS ; 
 int TK_EOS ; 
 int TK_EQ ; 
 int TK_GE ; 
 int TK_IDIV ; 
 int TK_LE ; 
 int TK_NAME ; 
 int TK_NE ; 
 int TK_SHL ; 
 int TK_SHR ; 
 int TK_STRING ; 
 int /*<<< orphan*/  check_next1 (TYPE_3__*,char) ; 
 int /*<<< orphan*/  currIsNewline (TYPE_3__*) ; 
 int /*<<< orphan*/  inclinenumber (TYPE_3__*) ; 
 int /*<<< orphan*/  isreserved (TYPE_1__*) ; 
 int /*<<< orphan*/  lexerror (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  lisdigit (int) ; 
 int /*<<< orphan*/  lislalnum (int) ; 
 int /*<<< orphan*/  lislalpha (int) ; 
 TYPE_1__* luaX_newstring (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_bufflen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_resetbuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (TYPE_3__*) ; 
 int /*<<< orphan*/  read_long_string (TYPE_3__*,TYPE_2__*,int) ; 
 int read_numeral (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  read_string (TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  save_and_next (TYPE_3__*) ; 
 int skip_sep (TYPE_3__*) ; 

__attribute__((used)) static int llex (LexState *ls, SemInfo *seminfo) {
  luaZ_resetbuffer(ls->buff);
  for (;;) {
    switch (ls->current) {
      case '\n': case '\r': {  /* line breaks */
        inclinenumber(ls);
        break;
      }
      case ' ': case '\f': case '\t': case '\v': {  /* spaces */
        next(ls);
        break;
      }
      case '-': {  /* '-' or '--' (comment) */
        next(ls);
        if (ls->current != '-') return '-';
        /* else is a comment */
        next(ls);
        if (ls->current == '[') {  /* long comment? */
          int sep = skip_sep(ls);
          luaZ_resetbuffer(ls->buff);  /* 'skip_sep' may dirty the buffer */
          if (sep >= 0) {
            read_long_string(ls, NULL, sep);  /* skip long comment */
            luaZ_resetbuffer(ls->buff);  /* previous call may dirty the buff. */
            break;
          }
        }
        /* else short comment */
        while (!currIsNewline(ls) && ls->current != EOZ)
          next(ls);  /* skip until end of line (or end of file) */
        break;
      }
      case '[': {  /* long string or simply '[' */
        int sep = skip_sep(ls);
        if (sep >= 0) {
          read_long_string(ls, seminfo, sep);
          return TK_STRING;
        }
        else if (sep != -1)  /* '[=...' missing second bracket */
          lexerror(ls, "invalid long string delimiter", TK_STRING);
        return '[';
      }
      case '=': {
        next(ls);
        if (check_next1(ls, '=')) return TK_EQ;
        else return '=';
      }
      case '<': {
        next(ls);
        if (check_next1(ls, '=')) return TK_LE;
        else if (check_next1(ls, '<')) return TK_SHL;
        else return '<';
      }
      case '>': {
        next(ls);
        if (check_next1(ls, '=')) return TK_GE;
        else if (check_next1(ls, '>')) return TK_SHR;
        else return '>';
      }
      case '/': {
        next(ls);
        if (check_next1(ls, '/')) return TK_IDIV;
        else return '/';
      }
      case '~': {
        next(ls);
        if (check_next1(ls, '=')) return TK_NE;
        else return '~';
      }
      case ':': {
        next(ls);
        if (check_next1(ls, ':')) return TK_DBCOLON;
        else return ':';
      }
      case '"': case '\'': {  /* short literal strings */
        read_string(ls, ls->current, seminfo);
        return TK_STRING;
      }
      case '.': {  /* '.', '..', '...', or number */
        save_and_next(ls);
        if (check_next1(ls, '.')) {
          if (check_next1(ls, '.'))
            return TK_DOTS;   /* '...' */
          else return TK_CONCAT;   /* '..' */
        }
        else if (!lisdigit(ls->current)) return '.';
        else return read_numeral(ls, seminfo);
      }
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': {
        return read_numeral(ls, seminfo);
      }
      case EOZ: {
        return TK_EOS;
      }
      default: {
        if (lislalpha(ls->current)) {  /* identifier or reserved word? */
          TString *ts;
          do {
            save_and_next(ls);
          } while (lislalnum(ls->current));
          ts = luaX_newstring(ls, luaZ_buffer(ls->buff),
                                  luaZ_bufflen(ls->buff));
          seminfo->ts = ts;
          if (isreserved(ts))  /* reserved word? */
            return ts->extra - 1 + FIRST_RESERVED;
          else {
            return TK_NAME;
          }
        }
        else {  /* single-char tokens (+ - / ...) */
          int c = ls->current;
          next(ls);
          return c;
        }
      }
    }
  }
}