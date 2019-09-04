#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_20__ {TYPE_15__* f; } ;
struct TYPE_19__ {int /*<<< orphan*/  linenumber; } ;
struct TYPE_18__ {int linedefined; int /*<<< orphan*/  lastlinedefined; } ;
struct TYPE_17__ {TYPE_1__* sp; } ;
typedef  TYPE_2__ LexState ;
typedef  TYPE_3__ FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_FUNCTION ; 
 TYPE_15__* addprototype (TYPE_2__*) ; 
 int /*<<< orphan*/  adjustlocalvars (TYPE_2__*,int) ; 
 int /*<<< orphan*/  check_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  checknext (TYPE_2__*,char) ; 
 int /*<<< orphan*/  close_func (TYPE_2__*) ; 
 int /*<<< orphan*/  codeclosure (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_localvarliteral (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  open_func (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parlist (TYPE_2__*) ; 
 int /*<<< orphan*/  statlist (TYPE_2__*) ; 

__attribute__((used)) static void body (LexState *ls, expdesc *e, int ismethod, int line) {
  /* body ->  '(' parlist ')' block END */
  FuncState new_fs;
  BlockCnt bl;
  new_fs.f = addprototype(ls);
  new_fs.f->sp->linedefined = line;
  open_func(ls, &new_fs, &bl);
  checknext(ls, '(');
  if (ismethod) {
    new_localvarliteral(ls, "self");  /* create 'self' parameter */
    adjustlocalvars(ls, 1);
  }
  parlist(ls);
  checknext(ls, ')');
  statlist(ls);
  new_fs.f->sp->lastlinedefined = ls->linenumber;
  check_match(ls, TK_END, TK_FUNCTION, line);
  codeclosure(ls, e);
  close_func(ls);
}