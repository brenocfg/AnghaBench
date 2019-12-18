#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_TESTSET ; 
 int getjump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getjumpcontrol (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int need_value(FuncState*fs,int list){
for(;list!=(-1);list=getjump(fs,list)){
Instruction i=*getjumpcontrol(fs,list);
if(GET_OPCODE(i)!=OP_TESTSET)return 1;
}
return 0;
}