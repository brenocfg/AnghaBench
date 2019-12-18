#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {size_t buffsize; char* buffer; } ;
typedef  TYPE_1__ Mbuffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaZ_resizebuffer (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 

__attribute__((used)) static char*luaZ_openspace(lua_State*L,Mbuffer*buff,size_t n){
if(n>buff->buffsize){
if(n<32)n=32;
luaZ_resizebuffer(L,buff,n);
}
return buff->buffer;
}