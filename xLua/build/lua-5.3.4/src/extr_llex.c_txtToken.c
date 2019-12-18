#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buff; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
#define  TK_FLT 131 
#define  TK_INT 130 
#define  TK_NAME 129 
#define  TK_STRING 128 
 char const* luaO_pushfstring (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char const* luaX_token2str (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaZ_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save (TYPE_1__*,char) ; 

__attribute__((used)) static const char *txtToken (LexState *ls, int token) {
  switch (token) {
    case TK_NAME: case TK_STRING:
    case TK_FLT: case TK_INT:
      save(ls, '\0');
      return luaO_pushfstring(ls->L, "'%s'", luaZ_buffer(ls->buff));
    default:
      return luaX_token2str(ls, token);
  }
}