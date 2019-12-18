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
typedef  int /*<<< orphan*/  TTree ;

/* Variables and functions */
 int /*<<< orphan*/  concattable (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  correctkeys (int /*<<< orphan*/ *,int) ; 
 int ktablelen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lp_equal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getuservalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void joinktables (lua_State *L, int p1, TTree *t2, int p2) {
  int n1, n2;
  lua_getuservalue(L, p1);  /* get ktables */
  lua_getuservalue(L, p2);
  n1 = ktablelen(L, -2);
  n2 = ktablelen(L, -1);
  if (n1 == 0 && n2 == 0)  /* are both tables empty? */
    lua_pop(L, 2);  /* nothing to be done; pop tables */
  else if (n2 == 0 || lp_equal(L, -2, -1)) {  /* 2nd table empty or equal? */
    lua_pop(L, 1);  /* pop 2nd table */
    lua_setuservalue(L, -2);  /* set 1st ktable into new pattern */
  }
  else if (n1 == 0) {  /* first table is empty? */
    lua_setuservalue(L, -3);  /* set 2nd table into new pattern */
    lua_pop(L, 1);  /* pop 1st table */
  }
  else {
    lua_createtable(L, n1 + n2, 0);  /* create ktable for new pattern */
    /* stack: new p; ktable p1; ktable p2; new ktable */
    concattable(L, -3, -1);  /* from p1 into new ktable */
    concattable(L, -2, -1);  /* from p2 into new ktable */
    lua_setuservalue(L, -4);  /* new ktable becomes 'p' environment */
    lua_pop(L, 2);  /* pop other ktables */
    correctkeys(t2, n1);  /* correction for indices from p2 */
  }
}