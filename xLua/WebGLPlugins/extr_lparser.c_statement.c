#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
struct TYPE_25__ {int token; } ;
struct TYPE_27__ {int linenumber; TYPE_11__* fs; TYPE_1__ t; } ;
struct TYPE_26__ {scalar_t__ maxstacksize; } ;
struct TYPE_24__ {scalar_t__ freereg; scalar_t__ nactvar; TYPE_2__* f; } ;
typedef  TYPE_3__ LexState ;

/* Variables and functions */
#define  TK_BREAK 138 
#define  TK_DBCOLON 137 
#define  TK_DO 136 
 int /*<<< orphan*/  TK_END ; 
#define  TK_FOR 135 
#define  TK_FUNCTION 134 
#define  TK_GOTO 133 
#define  TK_IF 132 
#define  TK_LOCAL 131 
#define  TK_REPEAT 130 
#define  TK_RETURN 129 
#define  TK_WHILE 128 
 int /*<<< orphan*/  block (TYPE_3__*) ; 
 int /*<<< orphan*/  check_match (TYPE_3__*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  enterlevel (TYPE_3__*) ; 
 int /*<<< orphan*/  exprstat (TYPE_3__*) ; 
 int /*<<< orphan*/  forstat (TYPE_3__*,int) ; 
 int /*<<< orphan*/  funcstat (TYPE_3__*,int) ; 
 int /*<<< orphan*/  gotostat (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifstat (TYPE_3__*,int) ; 
 int /*<<< orphan*/  labelstat (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  leavelevel (TYPE_3__*) ; 
 int /*<<< orphan*/  localfunc (TYPE_3__*) ; 
 int /*<<< orphan*/  localstat (TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_jump (TYPE_11__*) ; 
 int /*<<< orphan*/  luaX_next (TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  repeatstat (TYPE_3__*,int) ; 
 int /*<<< orphan*/  retstat (TYPE_3__*) ; 
 int /*<<< orphan*/  str_checkname (TYPE_3__*) ; 
 int /*<<< orphan*/  testnext (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  whilestat (TYPE_3__*,int) ; 

__attribute__((used)) static void statement (LexState *ls) {
  int line = ls->linenumber;  /* may be needed for error messages */
  enterlevel(ls);
  switch (ls->t.token) {
    case ';': {  /* stat -> ';' (empty statement) */
      luaX_next(ls);  /* skip ';' */
      break;
    }
    case TK_IF: {  /* stat -> ifstat */
      ifstat(ls, line);
      break;
    }
    case TK_WHILE: {  /* stat -> whilestat */
      whilestat(ls, line);
      break;
    }
    case TK_DO: {  /* stat -> DO block END */
      luaX_next(ls);  /* skip DO */
      block(ls);
      check_match(ls, TK_END, TK_DO, line);
      break;
    }
    case TK_FOR: {  /* stat -> forstat */
      forstat(ls, line);
      break;
    }
    case TK_REPEAT: {  /* stat -> repeatstat */
      repeatstat(ls, line);
      break;
    }
    case TK_FUNCTION: {  /* stat -> funcstat */
      funcstat(ls, line);
      break;
    }
    case TK_LOCAL: {  /* stat -> localstat */
      luaX_next(ls);  /* skip LOCAL */
      if (testnext(ls, TK_FUNCTION))  /* local function? */
        localfunc(ls);
      else
        localstat(ls);
      break;
    }
    case TK_DBCOLON: {  /* stat -> label */
      luaX_next(ls);  /* skip double colon */
      labelstat(ls, str_checkname(ls), line);
      break;
    }
    case TK_RETURN: {  /* stat -> retstat */
      luaX_next(ls);  /* skip RETURN */
      retstat(ls);
      break;
    }
    case TK_BREAK:   /* stat -> breakstat */
    case TK_GOTO: {  /* stat -> 'goto' NAME */
      gotostat(ls, luaK_jump(ls->fs));
      break;
    }
    default: {  /* stat -> func | assignment */
      exprstat(ls);
      break;
    }
  }
  lua_assert(ls->fs->f->maxstacksize >= ls->fs->freereg &&
             ls->fs->freereg >= ls->fs->nactvar);
  ls->fs->freereg = ls->fs->nactvar;  /* free registers */
  leavelevel(ls);
}