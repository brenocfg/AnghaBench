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
struct TYPE_4__ {int /*<<< orphan*/ * crypto_connections; } ;
typedef  TYPE_1__ Net_Crypto ;
typedef  int /*<<< orphan*/  Crypto_Connection ;

/* Variables and functions */
 scalar_t__ crypt_connection_id_not_valid (TYPE_1__ const*,int) ; 

__attribute__((used)) static Crypto_Connection *get_crypto_connection(const Net_Crypto *c, int crypt_connection_id)
{
    if (crypt_connection_id_not_valid(c, crypt_connection_id))
        return 0;

    return &c->crypto_connections[crypt_connection_id];
}