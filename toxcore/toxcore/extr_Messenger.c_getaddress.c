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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nospam ;
typedef  int /*<<< orphan*/  checksum ;
struct TYPE_5__ {int /*<<< orphan*/  fr; TYPE_1__* net_crypto; } ;
struct TYPE_4__ {int /*<<< orphan*/  self_public_key; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 scalar_t__ FRIEND_ADDRESS_SIZE ; 
 int /*<<< orphan*/  address_checksum (int /*<<< orphan*/ *,scalar_t__) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  get_nospam (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void getaddress(const Messenger *m, uint8_t *address)
{
    id_copy(address, m->net_crypto->self_public_key);
    uint32_t nospam = get_nospam(&(m->fr));
    memcpy(address + crypto_box_PUBLICKEYBYTES, &nospam, sizeof(nospam));
    uint16_t checksum = address_checksum(address, FRIEND_ADDRESS_SIZE - sizeof(checksum));
    memcpy(address + crypto_box_PUBLICKEYBYTES + sizeof(nospam), &checksum, sizeof(checksum));
}