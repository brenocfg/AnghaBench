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
struct pool {int dummy; } ;
struct sproto {struct pool memory; } ;

/* Variables and functions */
 int /*<<< orphan*/ * create_from_bundle (struct sproto*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (struct sproto*,int /*<<< orphan*/ ,int) ; 
 struct sproto* pool_alloc (struct pool*,int) ; 
 int /*<<< orphan*/  pool_init (struct pool*) ; 
 int /*<<< orphan*/  pool_release (struct pool*) ; 

struct sproto *
sproto_create(const void * proto, size_t sz) {
	struct pool mem;
	struct sproto * s;
	pool_init(&mem);
	s = pool_alloc(&mem, sizeof(*s));
	if (s == NULL)
		return NULL;
	memset(s, 0, sizeof(*s));
	s->memory = mem;
	if (create_from_bundle(s, proto, sz) == NULL) {
		pool_release(&s->memory);
		return NULL;
	}
	return s;
}