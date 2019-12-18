#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; scalar_t__ discoverable; int /*<<< orphan*/  path; TYPE_1__* userdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  image_cache; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int hashmap_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  image_ref (TYPE_2__*) ; 
 int manager_image_cache_initialize (TYPE_1__*) ; 

int manager_image_cache_add(Manager *m, Image *image) {
        int r;

        assert(m);

        /* We add the specified image to the cache under two keys.
         *
         * 1. Always under its path
         *
         * 2. If the image was discovered in the search path (i.e. its discoverable boolean set) we'll also add it
         *    under its short name.
         */

        r = manager_image_cache_initialize(m);
        if (r < 0)
                return r;

        image->userdata = m;

        r = hashmap_put(m->image_cache, image->path, image);
        if (r < 0)
                return r;

        image_ref(image);

        if (image->discoverable) {
                r = hashmap_put(m->image_cache, image->name, image);
                if (r < 0)
                        return r;

                image_ref(image);
        }

        return 0;
}