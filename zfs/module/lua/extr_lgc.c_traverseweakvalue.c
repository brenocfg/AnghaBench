#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  grayagain; int /*<<< orphan*/  weak; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_11__ {scalar_t__ sizearray; } ;
typedef  TYPE_2__ Table ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  checkdeadkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnodelast (TYPE_2__*) ; 
 int /*<<< orphan*/  gval (int /*<<< orphan*/ *) ; 
 scalar_t__ iscleared (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linktable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markvalue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeentry (int /*<<< orphan*/ *) ; 
 scalar_t__ ttisnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void traverseweakvalue (global_State *g, Table *h) {
  Node *n, *limit = gnodelast(h);
  /* if there is array part, assume it may have white values (do not
     traverse it just to check) */
  int hasclears = (h->sizearray > 0);
  for (n = gnode(h, 0); n < limit; n++) {
    checkdeadkey(n);
    if (ttisnil(gval(n)))  /* entry is empty? */
      removeentry(n);  /* remove it */
    else {
      lua_assert(!ttisnil(gkey(n)));
      markvalue(g, gkey(n));  /* mark key */
      if (!hasclears && iscleared(g, gval(n)))  /* is there a white value? */
        hasclears = 1;  /* table will have to be cleared */
    }
  }
  if (hasclears)
    linktable(h, &g->weak);  /* has to be cleared later */
  else  /* no white values */
    linktable(h, &g->grayagain);  /* no need to clean */
}