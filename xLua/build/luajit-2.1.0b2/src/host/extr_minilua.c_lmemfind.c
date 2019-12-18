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

/* Variables and functions */
 scalar_t__ memchr (char const*,char const,size_t) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const char*lmemfind(const char*s1,size_t l1,
const char*s2,size_t l2){
if(l2==0)return s1;
else if(l2>l1)return NULL;
else{
const char*init;
l2--;
l1=l1-l2;
while(l1>0&&(init=(const char*)memchr(s1,*s2,l1))!=NULL){
init++;
if(memcmp(init,s2+1,l2)==0)
return init-1;
else{
l1-=init-s1;
s1=init;
}
}
return NULL;
}
}