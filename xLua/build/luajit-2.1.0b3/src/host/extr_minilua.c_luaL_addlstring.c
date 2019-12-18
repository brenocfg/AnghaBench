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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luaL_addlstring(luaL_Buffer*B,const char*s,size_t l){
while(l--)
luaL_addchar(B,*s++);
}