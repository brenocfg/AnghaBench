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
typedef  int /*<<< orphan*/  Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_dht_entry ; 
 int /*<<< orphan*/  cmp_public_key ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sort_client_list(Client_data *list, unsigned int length, const uint8_t *comp_public_key)
{
    memcpy(cmp_public_key, comp_public_key, crypto_box_PUBLICKEYBYTES);
    qsort(list, length, sizeof(Client_data), cmp_dht_entry);
}