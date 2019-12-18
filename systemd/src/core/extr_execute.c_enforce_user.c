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
typedef  scalar_t__ uid_t ;
struct TYPE_4__ {scalar_t__ capability_ambient_set; int secure_bits; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  PR_GET_SECUREBITS ; 
 int /*<<< orphan*/  PR_SET_SECUREBITS ; 
 int SECURE_KEEP_CAPS ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int errno ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,...) ; 
 scalar_t__ setresuid (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uid_is_valid (scalar_t__) ; 

__attribute__((used)) static int enforce_user(const ExecContext *context, uid_t uid) {
        assert(context);

        if (!uid_is_valid(uid))
                return 0;

        /* Sets (but doesn't look up) the uid and make sure we keep the
         * capabilities while doing so. */

        if (context->capability_ambient_set != 0) {

                /* First step: If we need to keep capabilities but
                 * drop privileges we need to make sure we keep our
                 * caps, while we drop privileges. */
                if (uid != 0) {
                        int sb = context->secure_bits | 1<<SECURE_KEEP_CAPS;

                        if (prctl(PR_GET_SECUREBITS) != sb)
                                if (prctl(PR_SET_SECUREBITS, sb) < 0)
                                        return -errno;
                }
        }

        /* Second step: actually set the uids */
        if (setresuid(uid, uid, uid) < 0)
                return -errno;

        /* At this point we should have all necessary capabilities but
           are otherwise a normal user. However, the caps might got
           corrupted due to the setresuid() so we need clean them up
           later. This is done outside of this call. */

        return 0;
}