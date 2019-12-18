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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  VarlinkServer ;
typedef  int /*<<< orphan*/  Varlink ;

/* Variables and functions */
 scalar_t__ UID_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ getuid () ; 
 scalar_t__ varlink_get_peer_uid (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int on_connect(VarlinkServer *s, Varlink *link, void *userdata) {
        uid_t uid = UID_INVALID;

        assert(s);
        assert(link);

        assert_se(varlink_get_peer_uid(link, &uid) >= 0);
        assert_se(getuid() == uid);

        return 0;
}