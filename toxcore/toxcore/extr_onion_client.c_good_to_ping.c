#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Last_Pinged ;

/* Variables and functions */
 unsigned int MAX_STORED_PINGED_NODES ; 
 int /*<<< orphan*/  MIN_NODE_PING_TIME ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,unsigned int const*) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static int good_to_ping(Last_Pinged *last_pinged, uint8_t *last_pinged_index, const uint8_t *public_key)
{
    unsigned int i;

    for (i = 0; i < MAX_STORED_PINGED_NODES; ++i) {
        if (!is_timeout(last_pinged[i].timestamp, MIN_NODE_PING_TIME))
            if (public_key_cmp(last_pinged[i].public_key, public_key) == 0)
                return 0;
    }

    memcpy(last_pinged[*last_pinged_index % MAX_STORED_PINGED_NODES].public_key, public_key, crypto_box_PUBLICKEYBYTES);
    last_pinged[*last_pinged_index % MAX_STORED_PINGED_NODES].timestamp = unix_time();
    ++*last_pinged_index;
    return 1;
}