#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {size_t n; char* buff; int /*<<< orphan*/ * f; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ RN ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l_getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l_lockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l_unlockfile (int /*<<< orphan*/ *) ; 
 char lua_getlocaledecpoint () ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_stringtonumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ readdigits (TYPE_1__*,int) ; 
 scalar_t__ test2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ungetc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_number (lua_State *L, FILE *f) {
  RN rn;
  int count = 0;
  int hex = 0;
  char decp[2];
  rn.f = f; rn.n = 0;
  decp[0] = lua_getlocaledecpoint();  /* get decimal point from locale */
  decp[1] = '.';  /* always accept a dot */
  l_lockfile(rn.f);
  do { rn.c = l_getc(rn.f); } while (isspace(rn.c));  /* skip spaces */
  test2(&rn, "-+");  /* optional signal */
  if (test2(&rn, "00")) {
    if (test2(&rn, "xX")) hex = 1;  /* numeral is hexadecimal */
    else count = 1;  /* count initial '0' as a valid digit */
  }
  count += readdigits(&rn, hex);  /* integral part */
  if (test2(&rn, decp))  /* decimal point? */
    count += readdigits(&rn, hex);  /* fractional part */
  if (count > 0 && test2(&rn, (hex ? "pP" : "eE"))) {  /* exponent mark? */
    test2(&rn, "-+");  /* exponent signal */
    readdigits(&rn, 0);  /* exponent digits */
  }
  ungetc(rn.c, rn.f);  /* unread look-ahead char */
  l_unlockfile(rn.f);
  rn.buff[rn.n] = '\0';  /* finish string */
  if (lua_stringtonumber(L, rn.buff))  /* is this a valid number? */
    return 1;  /* ok */
  else {  /* invalid format */
   lua_pushnil(L);  /* "result" to be removed */
   return 0;  /* read fails */
  }
}