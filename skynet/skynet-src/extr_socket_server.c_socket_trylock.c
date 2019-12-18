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
struct socket_lock {scalar_t__ count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spinlock_trylock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
socket_trylock(struct socket_lock *sl) {
	if (sl->count == 0) {
		if (!spinlock_trylock(sl->lock))
			return 0;	// lock failed
	}
	++sl->count;
	return 1;
}