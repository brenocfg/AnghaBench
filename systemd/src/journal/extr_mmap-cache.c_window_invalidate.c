#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int invalidated; scalar_t__ ptr; int /*<<< orphan*/  prot; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ Window ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ mmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void window_invalidate(Window *w) {
        assert(w);

        if (w->invalidated)
                return;

        /* Replace the window with anonymous pages. This is useful
         * when we hit a SIGBUS and want to make sure the file cannot
         * trigger any further SIGBUS, possibly overrunning the sigbus
         * queue. */

        assert_se(mmap(w->ptr, w->size, w->prot, MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0) == w->ptr);
        w->invalidated = true;
}