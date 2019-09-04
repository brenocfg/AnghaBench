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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  dht_temp_pk; int /*<<< orphan*/  real_public_key; } ;
typedef  int /*<<< orphan*/  Friend_Connections ;
typedef  TYPE_1__ Friend_Conn ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 TYPE_1__* get_conn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int get_friendcon_public_keys(uint8_t *real_pk, uint8_t *dht_temp_pk, Friend_Connections *fr_c, int friendcon_id)
{
    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return -1;

    if (real_pk)
        memcpy(real_pk, friend_con->real_public_key, crypto_box_PUBLICKEYBYTES);

    if (dht_temp_pk)
        memcpy(dht_temp_pk, friend_con->dht_temp_pk, crypto_box_PUBLICKEYBYTES);

    return 0;
}