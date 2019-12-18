#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t n_decrypted; TYPE_1__* decrypted; } ;
struct TYPE_5__ {int relinquished; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ DecryptedPartition ;
typedef  TYPE_2__ DecryptedImage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int dm_deferred_remove (int /*<<< orphan*/ ) ; 
 int log_debug_errno (int,char*,int /*<<< orphan*/ ) ; 

int decrypted_image_relinquish(DecryptedImage *d) {

#if HAVE_LIBCRYPTSETUP
        size_t i;
        int r;
#endif

        assert(d);

        /* Turns on automatic removal after the last use ended for all DM devices of this image, and sets a boolean so
         * that we don't clean it up ourselves either anymore */

#if HAVE_LIBCRYPTSETUP
        for (i = 0; i < d->n_decrypted; i++) {
                DecryptedPartition *p = d->decrypted + i;

                if (p->relinquished)
                        continue;

                r = dm_deferred_remove(p->name);
                if (r < 0)
                        return log_debug_errno(r, "Failed to mark %s for auto-removal: %m", p->name);

                p->relinquished = true;
        }
#endif

        return 0;
}