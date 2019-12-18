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
struct TYPE_2__ {int id; } ;
struct uncomplete {TYPE_1__ pack; struct uncomplete* next; } ;
struct queue {struct uncomplete** hash; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct queue* get_queue (int /*<<< orphan*/ *) ; 
 int hash_fd (int) ; 
 int /*<<< orphan*/  memset (struct uncomplete*,int /*<<< orphan*/ ,int) ; 
 struct uncomplete* skynet_malloc (int) ; 

__attribute__((used)) static struct uncomplete *
save_uncomplete(lua_State *L, int fd) {
	struct queue *q = get_queue(L);
	int h = hash_fd(fd);
	struct uncomplete * uc = skynet_malloc(sizeof(struct uncomplete));
	memset(uc, 0, sizeof(*uc));
	uc->next = q->hash[h];
	uc->pack.id = fd;
	q->hash[h] = uc;

	return uc;
}