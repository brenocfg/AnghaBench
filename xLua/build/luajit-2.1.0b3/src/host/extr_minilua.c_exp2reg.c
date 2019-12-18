#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int info; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {scalar_t__ k; int t; int f; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ VJMP ; 
 scalar_t__ VNONRELOC ; 
 int code_label (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  discharge2reg (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ hasjumps (TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int*,int) ; 
 int luaK_getlabel (int /*<<< orphan*/ *) ; 
 int luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 scalar_t__ need_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  patchlistaux (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void exp2reg(FuncState*fs,expdesc*e,int reg){
discharge2reg(fs,e,reg);
if(e->k==VJMP)
luaK_concat(fs,&e->t,e->u.s.info);
if(hasjumps(e)){
int final;
int p_f=(-1);
int p_t=(-1);
if(need_value(fs,e->t)||need_value(fs,e->f)){
int fj=(e->k==VJMP)?(-1):luaK_jump(fs);
p_f=code_label(fs,reg,0,1);
p_t=code_label(fs,reg,1,0);
luaK_patchtohere(fs,fj);
}
final=luaK_getlabel(fs);
patchlistaux(fs,e->f,final,reg,p_f);
patchlistaux(fs,e->t,final,reg,p_t);
}
e->f=e->t=(-1);
e->u.s.info=reg;
e->k=VNONRELOC;
}