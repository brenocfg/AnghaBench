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
struct vtable_member {int /*<<< orphan*/  member; int /*<<< orphan*/  interface; int /*<<< orphan*/  path; } ;
struct siphash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vtable_member const*) ; 
 int /*<<< orphan*/  string_hash_func (int /*<<< orphan*/ ,struct siphash*) ; 

__attribute__((used)) static void vtable_member_hash_func(const struct vtable_member *m, struct siphash *state) {
        assert(m);

        string_hash_func(m->path, state);
        string_hash_func(m->interface, state);
        string_hash_func(m->member, state);
}