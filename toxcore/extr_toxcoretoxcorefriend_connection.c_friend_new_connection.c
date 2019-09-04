#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int crypt_connection_id; int /*<<< orphan*/  dht_temp_pk; int /*<<< orphan*/  real_public_key; int /*<<< orphan*/  dht_lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  net_crypto; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  connection_data_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  connection_lossy_data_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  connection_status_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dht_pk_callback ; 
 TYPE_2__* get_conn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  handle_lossy_packet ; 
 int /*<<< orphan*/  handle_packet ; 
 int /*<<< orphan*/  handle_status ; 
 int /*<<< orphan*/  nc_dht_pk_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int new_crypto_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int friend_new_connection(Friend_Connections *fr_c, int friendcon_id)
{
    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return -1;

    if (friend_con->crypt_connection_id != -1) {
        return -1;
    }

    /* If dht_temp_pk does not contains a pk. */
    if (!friend_con->dht_lock) {
        return -1;
    }

    int id = new_crypto_connection(fr_c->net_crypto, friend_con->real_public_key, friend_con->dht_temp_pk);

    if (id == -1)
        return -1;

    friend_con->crypt_connection_id = id;
    connection_status_handler(fr_c->net_crypto, id, &handle_status, fr_c, friendcon_id);
    connection_data_handler(fr_c->net_crypto, id, &handle_packet, fr_c, friendcon_id);
    connection_lossy_data_handler(fr_c->net_crypto, id, &handle_lossy_packet, fr_c, friendcon_id);
    nc_dht_pk_callback(fr_c->net_crypto, id, &dht_pk_callback, fr_c, friendcon_id);

    return 0;
}