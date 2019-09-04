#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct uncomplete* buffer; } ;
struct uncomplete {TYPE_1__ pack; } ;
struct queue {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct uncomplete* find_uncomplete (struct queue*,int) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (struct uncomplete*) ; 

__attribute__((used)) static void
close_uncomplete(lua_State *L, int fd) {
	struct queue *q = lua_touserdata(L,1);
	struct uncomplete * uc = find_uncomplete(q, fd);
	if (uc) {
		skynet_free(uc->pack.buffer);
		skynet_free(uc);
	}
}