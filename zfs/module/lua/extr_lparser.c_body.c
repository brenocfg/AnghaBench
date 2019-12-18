#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_18__ {TYPE_14__* f; } ;
struct TYPE_17__ {int /*<<< orphan*/  linenumber; } ;
struct TYPE_16__ {int linedefined; int /*<<< orphan*/  lastlinedefined; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_FUNCTION ; 
 TYPE_14__* addprototype (TYPE_1__*) ; 
 int /*<<< orphan*/  adjustlocalvars (TYPE_1__*,int) ; 
 int /*<<< orphan*/  check_match (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  checknext (TYPE_1__*,char) ; 
 int /*<<< orphan*/  close_func (TYPE_1__*) ; 
 int /*<<< orphan*/  codeclosure (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_localvarliteral (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  open_func (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parlist (TYPE_1__*) ; 
 int /*<<< orphan*/  statlist (TYPE_1__*) ; 

__attribute__((used)) static void body (LexState *ls, expdesc *e, int ismethod, int line) {
  /* body ->  `(' parlist `)' block END */
  FuncState new_fs;
  BlockCnt bl;
  new_fs.f = addprototype(ls);
  new_fs.f->linedefined = line;
  open_func(ls, &new_fs, &bl);
  checknext(ls, '(');
  if (ismethod) {
    new_localvarliteral(ls, "self");  /* create 'self' parameter */
    adjustlocalvars(ls, 1);
  }
  parlist(ls);
  checknext(ls, ')');
  statlist(ls);
  new_fs.f->lastlinedefined = ls->linenumber;
  check_match(ls, TK_END, TK_FUNCTION, line);
  codeclosure(ls, e);
  close_func(ls);
}