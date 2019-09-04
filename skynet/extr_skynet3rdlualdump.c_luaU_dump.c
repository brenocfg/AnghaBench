#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_Writer ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {int strip; int status; void* data; int /*<<< orphan*/  writer; int /*<<< orphan*/ * L; } ;
struct TYPE_10__ {TYPE_1__* sp; } ;
struct TYPE_9__ {int /*<<< orphan*/  sizeupvalues; } ;
typedef  TYPE_2__ Proto ;
typedef  TYPE_3__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpByte (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpFunction (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  DumpHeader (TYPE_3__*) ; 

int luaU_dump(lua_State *L, const Proto *f, lua_Writer w, void *data,
              int strip) {
  DumpState D;
  D.L = L;
  D.writer = w;
  D.data = data;
  D.strip = strip;
  D.status = 0;
  DumpHeader(&D);
  DumpByte(f->sp->sizeupvalues, &D);
  DumpFunction(f, NULL, &D);
  return D.status;
}