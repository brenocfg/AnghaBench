#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char const* s; int ptop; int /*<<< orphan*/ * cap; scalar_t__ valuecached; int /*<<< orphan*/ * L; int /*<<< orphan*/ * ocap; } ;
typedef  int /*<<< orphan*/  Capture ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  caplistidx (int) ; 
 int /*<<< orphan*/  isclosecap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pushcapture (TYPE_1__*) ; 

int getcaptures (lua_State *L, const char *s, const char *r, int ptop) {
  Capture *capture = (Capture *)lua_touserdata(L, caplistidx(ptop));
  int n = 0;
  if (!isclosecap(capture)) {  /* is there any capture? */
    CapState cs;
    cs.ocap = cs.cap = capture; cs.L = L;
    cs.s = s; cs.valuecached = 0; cs.ptop = ptop;
    do {  /* collect their values */
      n += pushcapture(&cs);
    } while (!isclosecap(cs.cap));
  }
  if (n == 0) {  /* no capture values? */
    lua_pushinteger(L, r - s + 1);  /* return only end position */
    n = 1;
  }
  return n;
}