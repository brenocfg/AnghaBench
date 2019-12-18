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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  unsigned int TMS ;

/* Variables and functions */
 int /*<<< orphan*/  cast_byte (unsigned int) ; 
 int /*<<< orphan*/ * luaH_getstr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const TValue*luaT_gettm(Table*events,TMS event,TString*ename){
const TValue*tm=luaH_getstr(events,ename);
if(ttisnil(tm)){
events->flags|=cast_byte(1u<<event);
return NULL;
}
else return tm;
}