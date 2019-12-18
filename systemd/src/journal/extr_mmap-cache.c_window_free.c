#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* cache; } ;
typedef  TYPE_2__ Window ;
struct TYPE_7__ {int /*<<< orphan*/  n_windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  window_unlink (TYPE_2__*) ; 

__attribute__((used)) static void window_free(Window *w) {
        assert(w);

        window_unlink(w);
        w->cache->n_windows--;
        free(w);
}