#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_13__ {int /*<<< orphan*/  ts; } ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
#define  EOZ 128 
 char TK_EOS ; 
 scalar_t__ currIsNewline (TYPE_2__*) ; 
 int /*<<< orphan*/  inclinenumber (TYPE_2__*) ; 
 int /*<<< orphan*/  luaX_lexerror (TYPE_2__*,char*,char) ; 
 int /*<<< orphan*/  luaX_newstring (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ luaZ_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ luaZ_bufflen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_resetbuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (TYPE_2__*) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 
 int skip_sep (TYPE_2__*) ; 

__attribute__((used)) static void read_long_string (LexState *ls, SemInfo *seminfo, int sep) {
  int cont = 0;
  (void)(cont);  /* avoid warnings when `cont' is not used */
  save_and_next(ls);  /* skip 2nd `[' */
  if (currIsNewline(ls))  /* string starts with a newline? */
    inclinenumber(ls);  /* skip it */
  for (;;) {
    switch (ls->current) {
      case EOZ:
        luaX_lexerror(ls, (seminfo) ? "unfinished long string" :
                                   "unfinished long comment", TK_EOS);
        break;  /* to avoid warnings */
#if defined(LUA_COMPAT_LSTR)
      case '[': {
        if (skip_sep(ls) == sep) {
          save_and_next(ls);  /* skip 2nd `[' */
          cont++;
#if LUA_COMPAT_LSTR == 1
          if (sep == 0)
            luaX_lexerror(ls, "nesting of [[...]] is deprecated", '[');
#endif
        }
        break;
      }
#endif
      case ']': {
        if (skip_sep(ls) == sep) {
          save_and_next(ls);  /* skip 2nd `]' */
#if defined(LUA_COMPAT_LSTR) && LUA_COMPAT_LSTR == 2
          cont--;
          if (sep == 0 && cont >= 0) break;
#endif
          goto endloop;
        }
        break;
      }
      case '\n':
      case '\r': {
        save(ls, '\n');
        inclinenumber(ls);
        if (!seminfo) luaZ_resetbuffer(ls->buff);  /* avoid wasting space */
        break;
      }
      default: {
        if (seminfo) save_and_next(ls);
        else next(ls);
      }
    }
  } endloop:
  if (seminfo)
    seminfo->ts = luaX_newstring(ls, luaZ_buffer(ls->buff) + (2 + sep),
                                     luaZ_bufflen(ls->buff) - 2*(2 + sep));
}