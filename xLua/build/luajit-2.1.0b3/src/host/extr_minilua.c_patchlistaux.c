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
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  fixjump (int /*<<< orphan*/ *,int,int) ; 
 int getjump (int /*<<< orphan*/ *,int) ; 
 scalar_t__ patchtestreg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void patchlistaux(FuncState*fs,int list,int vtarget,int reg,
int dtarget){
while(list!=(-1)){
int next=getjump(fs,list);
if(patchtestreg(fs,list,reg))
fixjump(fs,list,vtarget);
else
fixjump(fs,list,dtarget);
list=next;
}
}