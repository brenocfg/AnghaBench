#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_15__ {int /*<<< orphan*/  ts; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
#define  EOZ 128 
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  TK_STRING ; 
 int /*<<< orphan*/  currIsNewline (TYPE_2__*) ; 
 int /*<<< orphan*/  escerror (TYPE_2__*,int*,int,char*) ; 
 int /*<<< orphan*/  inclinenumber (TYPE_2__*) ; 
 int /*<<< orphan*/  lexerror (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lisdigit (int) ; 
 int /*<<< orphan*/  lisspace (int) ; 
 int /*<<< orphan*/  luaX_newstring (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ luaZ_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ luaZ_bufflen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (TYPE_2__*) ; 
 int readdecesc (TYPE_2__*) ; 
 int readhexaesc (TYPE_2__*) ; 
 int /*<<< orphan*/  save (TYPE_2__*,int) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 

__attribute__((used)) static void read_string (LexState *ls, int del, SemInfo *seminfo) {
  save_and_next(ls);  /* keep delimiter (for error messages) */
  while (ls->current != del) {
    switch (ls->current) {
      case EOZ:
        lexerror(ls, "unfinished string", TK_EOS);
        break;  /* to avoid warnings */
      case '\n':
      case '\r':
        lexerror(ls, "unfinished string", TK_STRING);
        break;  /* to avoid warnings */
      case '\\': {  /* escape sequences */
        int c;  /* final character to be saved */
        next(ls);  /* do not save the `\' */
        switch (ls->current) {
          case 'a': c = '\a'; goto read_save;
          case 'b': c = '\b'; goto read_save;
          case 'f': c = '\f'; goto read_save;
          case 'n': c = '\n'; goto read_save;
          case 'r': c = '\r'; goto read_save;
          case 't': c = '\t'; goto read_save;
          case 'v': c = '\v'; goto read_save;
          case 'x': c = readhexaesc(ls); goto read_save;
          case '\n': case '\r':
            inclinenumber(ls); c = '\n'; goto only_save;
          case '\\': case '\"': case '\'':
            c = ls->current; goto read_save;
          case EOZ: goto no_save;  /* will raise an error next loop */
          case 'z': {  /* zap following span of spaces */
            next(ls);  /* skip the 'z' */
            while (lisspace(ls->current)) {
              if (currIsNewline(ls)) inclinenumber(ls);
              else next(ls);
            }
            goto no_save;
          }
          default: {
            if (!lisdigit(ls->current))
              escerror(ls, &ls->current, 1, "invalid escape sequence");
            /* digital escape \ddd */
            c = readdecesc(ls);
            goto only_save;
          }
        }
       read_save: next(ls);  /* read next character */
       only_save: save(ls, c);  /* save 'c' */
       no_save: break;
      }
      default:
        save_and_next(ls);
    }
  }
  save_and_next(ls);  /* skip delimiter */
  seminfo->ts = luaX_newstring(ls, luaZ_buffer(ls->buff) + 1,
                                   luaZ_bufflen(ls->buff) - 2);
}