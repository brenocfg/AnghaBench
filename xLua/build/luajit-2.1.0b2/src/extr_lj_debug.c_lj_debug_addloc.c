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
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_4__ {int /*<<< orphan*/  firstline; } ;
typedef  TYPE_1__ GCproto ;
typedef  int /*<<< orphan*/  GCfunc ;
typedef  scalar_t__ BCLine ;

/* Variables and functions */
 int LUA_IDSIZE ; 
 scalar_t__ debug_frameline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * frame_func (int /*<<< orphan*/ *) ; 
 TYPE_1__* funcproto (int /*<<< orphan*/ *) ; 
 scalar_t__ isluafunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lj_debug_shortname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_strfmt_pushf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  proto_chunkname (TYPE_1__*) ; 

void lj_debug_addloc(lua_State *L, const char *msg,
		     cTValue *frame, cTValue *nextframe)
{
  if (frame) {
    GCfunc *fn = frame_func(frame);
    if (isluafunc(fn)) {
      BCLine line = debug_frameline(L, fn, nextframe);
      if (line >= 0) {
	GCproto *pt = funcproto(fn);
	char buf[LUA_IDSIZE];
	lj_debug_shortname(buf, proto_chunkname(pt), pt->firstline);
	lj_strfmt_pushf(L, "%s:%d: %s", buf, line, msg);
	return;
      }
    }
  }
  lj_strfmt_pushf(L, "%s", msg);
}