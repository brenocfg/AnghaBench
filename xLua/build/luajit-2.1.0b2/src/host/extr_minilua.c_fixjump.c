#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ls; TYPE_1__* f; } ;
struct TYPE_4__ {int /*<<< orphan*/ * code; } ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  SETARG_sBx (int /*<<< orphan*/ ,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  luaX_syntaxerror (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fixjump(FuncState*fs,int pc,int dest){
Instruction*jmp=&fs->f->code[pc];
int offset=dest-(pc+1);
if(abs(offset)>(((1<<(9+9))-1)>>1))
luaX_syntaxerror(fs->ls,"control structure too long");
SETARG_sBx(*jmp,offset);
}