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
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  invalid_stream (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  memcpy (double*,double*,int) ; 
 double* rb_read (struct read_block*,int) ; 

__attribute__((used)) static double
get_real(lua_State *L, struct read_block *rb) {
	double n;
	double * pn = rb_read(rb,sizeof(n));
	if (pn == NULL)
		invalid_stream(L,rb);
	memcpy(&n, pn, sizeof(n));
	return n;
}