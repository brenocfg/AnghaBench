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
struct TYPE_4__ {char c; } ;
typedef  TYPE_1__ LexState ;
typedef  char LexChar ;

/* Variables and functions */
 char lex_savenext (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static int lex_skipeq(LexState *ls)
{
  int count = 0;
  LexChar s = ls->c;
  lua_assert(s == '[' || s == ']');
  while (lex_savenext(ls) == '=')
    count++;
  return (ls->c == s) ? count : (-count) - 1;
}