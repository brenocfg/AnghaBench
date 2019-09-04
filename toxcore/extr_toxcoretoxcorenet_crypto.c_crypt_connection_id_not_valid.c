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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ crypto_connections_length; TYPE_1__* crypto_connections; } ;
struct TYPE_4__ {scalar_t__ status; } ;
typedef  TYPE_2__ Net_Crypto ;

/* Variables and functions */
 scalar_t__ CRYPTO_CONN_NO_CONNECTION ; 

__attribute__((used)) static uint8_t crypt_connection_id_not_valid(const Net_Crypto *c, int crypt_connection_id)
{
    if ((uint32_t)crypt_connection_id >= c->crypto_connections_length)
        return 1;

    if (c->crypto_connections == NULL)
        return 1;

    if (c->crypto_connections[crypt_connection_id].status == CRYPTO_CONN_NO_CONNECTION)
        return 1;

    return 0;
}