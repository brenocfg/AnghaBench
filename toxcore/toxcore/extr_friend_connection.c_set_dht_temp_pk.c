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
typedef  int /*<<< orphan*/  Friend_Connections ;

/* Variables and functions */
 int /*<<< orphan*/  dht_pk_callback (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 

void set_dht_temp_pk(Friend_Connections *fr_c, int friendcon_id, const uint8_t *dht_temp_pk)
{
    dht_pk_callback(fr_c, friendcon_id, dht_temp_pk);
}