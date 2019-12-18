#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct ConsControl {scalar_t__ nh; scalar_t__ na; int /*<<< orphan*/  v; int /*<<< orphan*/ * t; scalar_t__ tostore; } ;
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_21__ {TYPE_3__* f; } ;
struct TYPE_18__ {char token; } ;
struct TYPE_17__ {char token; } ;
struct TYPE_20__ {int linenumber; TYPE_2__ lookahead; TYPE_1__ t; TYPE_5__* fs; } ;
struct TYPE_19__ {int /*<<< orphan*/ * code; } ;
typedef  TYPE_4__ LexState ;
typedef  TYPE_5__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_NEWTABLE ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_C (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TK_NAME 128 
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  VVOID ; 
 int /*<<< orphan*/  check_match (TYPE_4__*,char,char,int) ; 
 int /*<<< orphan*/  checknext (TYPE_4__*,char) ; 
 int /*<<< orphan*/  closelistfield (TYPE_5__*,struct ConsControl*) ; 
 int /*<<< orphan*/  init_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lastlistfield (TYPE_5__*,struct ConsControl*) ; 
 int /*<<< orphan*/  listfield (TYPE_4__*,struct ConsControl*) ; 
 int luaK_codeABC (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaO_int2fb (scalar_t__) ; 
 int /*<<< orphan*/  luaX_lookahead (TYPE_4__*) ; 
 int /*<<< orphan*/  recfield (TYPE_4__*,struct ConsControl*) ; 
 scalar_t__ testnext (TYPE_4__*,char) ; 

__attribute__((used)) static void constructor(LexState*ls,expdesc*t){
FuncState*fs=ls->fs;
int line=ls->linenumber;
int pc=luaK_codeABC(fs,OP_NEWTABLE,0,0,0);
struct ConsControl cc;
cc.na=cc.nh=cc.tostore=0;
cc.t=t;
init_exp(t,VRELOCABLE,pc);
init_exp(&cc.v,VVOID,0);
luaK_exp2nextreg(ls->fs,t);
checknext(ls,'{');
do{
if(ls->t.token=='}')break;
closelistfield(fs,&cc);
switch(ls->t.token){
case TK_NAME:{
luaX_lookahead(ls);
if(ls->lookahead.token!='=')
listfield(ls,&cc);
else
recfield(ls,&cc);
break;
}
case'[':{
recfield(ls,&cc);
break;
}
default:{
listfield(ls,&cc);
break;
}
}
}while(testnext(ls,',')||testnext(ls,';'));
check_match(ls,'}','{',line);
lastlistfield(fs,&cc);
SETARG_B(fs->f->code[pc],luaO_int2fb(cc.na));
SETARG_C(fs->f->code[pc],luaO_int2fb(cc.nh));
}