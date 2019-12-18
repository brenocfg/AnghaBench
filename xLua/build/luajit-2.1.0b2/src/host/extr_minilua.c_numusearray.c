#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sizearray; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int numusearray(const Table*t,int*nums){
int lg;
int ttlg;
int ause=0;
int i=1;
for(lg=0,ttlg=1;lg<=(32-2);lg++,ttlg*=2){
int lc=0;
int lim=ttlg;
if(lim>t->sizearray){
lim=t->sizearray;
if(i>lim)
break;
}
for(;i<=lim;i++){
if(!ttisnil(&t->array[i-1]))
lc++;
}
nums[lg]+=lc;
ause+=lc;
}
return ause;
}