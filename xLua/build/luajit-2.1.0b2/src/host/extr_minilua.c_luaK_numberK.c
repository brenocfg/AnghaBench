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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int addk (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int luaK_numberK(FuncState*fs,lua_Number r){
TValue o;
setnvalue(&o,r);
return addk(fs,&o,&o);
}