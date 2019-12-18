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
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/ * index2adr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  l_isfalse (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int lua_toboolean(lua_State*L,int idx){
const TValue*o=index2adr(L,idx);
return!l_isfalse(o);
}