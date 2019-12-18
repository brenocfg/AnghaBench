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
struct TYPE_2__ {size_t (* size ) (void const*) ;int /*<<< orphan*/  free; void const* (* buffer ) (void const*) ;} ;
struct socket_server {TYPE_1__ soi; } ;
struct send_object {size_t sz; int /*<<< orphan*/  free_func; void const* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE ; 
 size_t USEROBJECT ; 
 void const* stub1 (void const*) ; 
 size_t stub2 (void const*) ; 

__attribute__((used)) static inline bool
send_object_init(struct socket_server *ss, struct send_object *so, const void *object, size_t sz) {
	if (sz == USEROBJECT) {
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