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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int /*<<< orphan*/  ck_assert (int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ tox_friend_add_norequest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void t_accept_friend_request_cb(Tox *m, const uint8_t *public_key, const uint8_t *data, size_t length, void *userdata)
{
    (void) userdata;

    if (length == 7 && memcmp("gentoo", data, 7) == 0) {
        ck_assert(tox_friend_add_norequest(m, public_key, NULL) != (uint32_t) ~0);
    }
}