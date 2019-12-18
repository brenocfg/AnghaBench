#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int current; int /*<<< orphan*/  buff; } ;
struct TYPE_9__ {int /*<<< orphan*/  r; int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ SemInfo ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int TK_FLT ; 
 int TK_INT ; 
 scalar_t__ check_next2 (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lexerror (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  lisdigit (int) ; 
 scalar_t__ lisxdigit (int) ; 
 scalar_t__ luaO_str2num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save (TYPE_2__*,char) ; 
 int /*<<< orphan*/  save_and_next (TYPE_2__*) ; 
 int /*<<< orphan*/  ttisfloat (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_numeral (LexState *ls, SemInfo *seminfo) {
  TValue obj;
  const char *expo = "Ee";
  int first = ls->current;
  lua_assert(lisdigit(ls->current));
  save_and_next(ls);
  if (first == '0' && check_next2(ls, "xX"))  /* hexadecimal? */
    expo = "Pp";
  for (;;) {
    if (check_next2(ls, expo))  /* exponent part? */
      check_next2(ls, "-+");  /* optional exponent sign */
    if (lisxdigit(ls->current))
      save_and_next(ls);
    else if (ls->current == '.')
      save_and_next(ls);
    else break;
  }
  save(ls, '\0');
  if (luaO_str2num(luaZ_buffer(ls->buff), &obj) == 0)  /* format error? */
    lexerror(ls, "malformed number", TK_FLT);
  if (ttisinteger(&obj)) {
    seminfo->i = ivalue(&obj);
    return TK_INT;
  }
  else {
    lua_assert(ttisfloat(&obj));
    seminfo->r = fltvalue(&obj);
    return TK_FLT;
  }
}