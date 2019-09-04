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
struct TYPE_2__ {int (* size ) (void*) ;int /*<<< orphan*/  free; void* (* buffer ) (void*) ;} ;
struct socket_server {TYPE_1__ soi; } ;
struct send_object {int sz; int /*<<< orphan*/  free_func; void* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 void* stub1 (void*) ; 
 int stub2 (void*) ; 

__attribute__((used)) static inline bool
send_object_init(struct socket_server *ss, struct send_object *so, void *object, int sz) {
	if (sz < 0) {
		so->buffer = ss->soi.buffer(object);
		so->sz = ss->soi.size(object);
		so->free_func = ss->soi.free;
		return true;
	} else {
		so->buffer = object;
		so->sz = sz;
		so->free_func = FREE;
		return false;
	}
}