#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ base; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {scalar_t__ udtype; } ;
typedef  int /*<<< orphan*/  IOFileUD ;

/* Variables and functions */
 scalar_t__ UDTYPE_IO_FILE ; 
 int /*<<< orphan*/  lj_err_argtype (TYPE_1__*,int,char*) ; 
 scalar_t__ tvisudata (scalar_t__) ; 
 TYPE_2__* udataV (scalar_t__) ; 
 scalar_t__ uddata (TYPE_2__*) ; 

__attribute__((used)) static IOFileUD *io_tofilep(lua_State *L)
{
  if (!(L->base < L->top && tvisudata(L->base) &&
	udataV(L->base)->udtype == UDTYPE_IO_FILE))
    lj_err_argtype(L, 1, "FILE*");
  return (IOFileUD *)uddata(udataV(L->base));
}