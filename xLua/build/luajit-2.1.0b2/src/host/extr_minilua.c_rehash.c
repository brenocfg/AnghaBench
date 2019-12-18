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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int computesizes (int*,int*) ; 
 scalar_t__ countint (int /*<<< orphan*/  const*,int*) ; 
 int numusearray (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ numusehash (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  resize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void rehash(lua_State*L,Table*t,const TValue*ek){
int nasize,na;
int nums[(32-2)+1];
int i;
int totaluse;
for(i=0;i<=(32-2);i++)nums[i]=0;
nasize=numusearray(t,nums);
totaluse=nasize;
totaluse+=numusehash(t,nums,&nasize);
nasize+=countint(ek,nums);
totaluse++;
na=computesizes(nums,&nasize);
resize(L,t,nasize,totaluse-na);
}