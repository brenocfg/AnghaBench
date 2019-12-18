#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_10__ {int token; } ;
struct TYPE_11__ {TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
#define  TK_STRING 128 
 int /*<<< orphan*/  checkname (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  field (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funcargs (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2anyreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_indexed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_self (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  prefixexp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yindex (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void primaryexp(LexState*ls,expdesc*v){
FuncState*fs=ls->fs;
prefixexp(ls,v);
for(;;){
switch(ls->t.token){
case'.':{
field(ls,v);
break;
}
case'[':{
expdesc key;
luaK_exp2anyreg(fs,v);
yindex(ls,&key);
luaK_indexed(fs,v,&key);
break;
}
case':':{
expdesc key;
luaX_next(ls);
checkname(ls,&key);
luaK_self(fs,v,&key);
funcargs(ls,v);
break;
}
case'(':case TK_STRING:case'{':{
luaK_exp2nextreg(fs,v);
funcargs(ls,v);
break;
}
default:return;
}
}
}