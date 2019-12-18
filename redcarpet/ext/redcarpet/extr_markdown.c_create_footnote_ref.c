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
typedef  int /*<<< orphan*/  uint8_t ;
struct footnote_ref {int /*<<< orphan*/  id; } ;
struct footnote_list {int dummy; } ;

/* Variables and functions */
 struct footnote_ref* calloc (int,int) ; 
 int /*<<< orphan*/  hash_link_ref (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static struct footnote_ref *
create_footnote_ref(struct footnote_list *list, const uint8_t *name, size_t name_size)
{
	struct footnote_ref *ref = calloc(1, sizeof(struct footnote_ref));
	if (!ref)
		return NULL;

	ref->id = hash_link_ref(name, name_size);

	return ref;
}