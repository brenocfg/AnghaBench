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
struct TYPE_4__ {int /*<<< orphan*/  image_cache; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Image ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,char const*) ; 

Image *manager_image_cache_get(Manager *m, const char *name_or_path) {
        assert(m);

        return hashmap_get(m->image_cache, name_or_path);
}