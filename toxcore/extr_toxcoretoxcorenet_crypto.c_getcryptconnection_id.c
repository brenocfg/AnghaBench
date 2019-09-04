#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t crypto_connections_length; TYPE_1__* crypto_connections; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_2__ Net_Crypto ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_NO_CONNECTION ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getcryptconnection_id(const Net_Crypto *c, const uint8_t *public_key)
{
    uint32_t i;

    for (i = 0; i < c->crypto_connections_length; ++i) {
        if (c->crypto_connections[i].status != CRYPTO_CONN_NO_CONNECTION)
            if (public_key_cmp(public_key, c->crypto_connections[i].public_key) == 0)
                return i;
    }

    return -1;
}