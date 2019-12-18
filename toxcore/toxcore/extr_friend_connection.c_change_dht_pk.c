#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  dht_temp_pk; scalar_t__ dht_lock; int /*<<< orphan*/  dht_pk_lastrecv; } ;
struct TYPE_7__ {int /*<<< orphan*/  dht; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  DHT_addfriend (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__*) ; 
 scalar_t__ DHT_delfriend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  dht_ip_callback ; 
 TYPE_2__* get_conn (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static void change_dht_pk(Friend_Connections *fr_c, int friendcon_id, const uint8_t *dht_public_key)
{
    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return;

    friend_con->dht_pk_lastrecv = unix_time();

    if (friend_con->dht_lock) {
        if (DHT_delfriend(fr_c->dht, friend_con->dht_temp_pk, friend_con->dht_lock) != 0) {
            printf("a. Could not delete dht peer. Please report this.\n");
            return;
        }

        friend_con->dht_lock = 0;
    }

    DHT_addfriend(fr_c->dht, dht_public_key, dht_ip_callback, fr_c, friendcon_id, &friend_con->dht_lock);
    memcpy(friend_con->dht_temp_pk, dht_public_key, crypto_box_PUBLICKEYBYTES);
}