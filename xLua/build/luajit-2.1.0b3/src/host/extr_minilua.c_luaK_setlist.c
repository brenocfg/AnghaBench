#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int freereg; TYPE_1__* ls; } ;
struct TYPE_6__ {int /*<<< orphan*/  lastline; } ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  Instruction ; 
 int /*<<< orphan*/  OP_SETLIST ; 
 int /*<<< orphan*/  cast (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaK_code (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void luaK_setlist(FuncState*fs,int base,int nelems,int tostore){
int c=(nelems-1)/50+1;
int b=(tostore==(-1))?0:tostore;
if(c<=((1<<9)-1))
luaK_codeABC(fs,OP_SETLIST,base,b,c);
else{
luaK_codeABC(fs,OP_SETLIST,base,b,0);
luaK_code(fs,cast(Instruction,c),fs->ls->lastline);
}
fs->freereg=base+1;
}