#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  time; int /*<<< orphan*/  data_public_key; int /*<<< orphan*/  ret; int /*<<< orphan*/  ret_ip_port; int /*<<< orphan*/  public_key; } ;
struct TYPE_7__ {TYPE_3__* entries; TYPE_1__* dht; } ;
struct TYPE_6__ {int /*<<< orphan*/  const* self_public_key; } ;
typedef  int /*<<< orphan*/  Onion_Announce_Entry ;
typedef  TYPE_2__ Onion_Announce ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 unsigned int ONION_ANNOUNCE_MAX_ENTRIES ; 
 int /*<<< orphan*/  ONION_ANNOUNCE_TIMEOUT ; 
 int /*<<< orphan*/  ONION_RETURN_3 ; 
 int /*<<< orphan*/  cmp_entry ; 
 int /*<<< orphan*/  cmp_public_key ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int id_closest (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int in_entries (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (TYPE_3__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_time () ; 

__attribute__((used)) static int add_to_entries(Onion_Announce *onion_a, IP_Port ret_ip_port, const uint8_t *public_key,
                          const uint8_t *data_public_key, const uint8_t *ret)
{

    int pos = in_entries(onion_a, public_key);

    unsigned int i;

    if (pos == -1) {
        for (i = 0; i < ONION_ANNOUNCE_MAX_ENTRIES; ++i) {
            if (is_timeout(onion_a->entries[i].time, ONION_ANNOUNCE_TIMEOUT))
                pos = i;
        }
    }

    if (pos == -1) {
        if (id_closest(onion_a->dht->self_public_key, public_key, onion_a->entries[0].public_key) == 1)
            pos = 0;
    }

    if (pos == -1)
        return -1;

    memcpy(onion_a->entries[pos].public_key, public_key, crypto_box_PUBLICKEYBYTES);
    onion_a->entries[pos].ret_ip_port = ret_ip_port;
    memcpy(onion_a->entries[pos].ret, ret, ONION_RETURN_3);
    memcpy(onion_a->entries[pos].data_public_key, data_public_key, crypto_box_PUBLICKEYBYTES);
    onion_a->entries[pos].time = unix_time();

    memcpy(cmp_public_key, onion_a->dht->self_public_key, crypto_box_PUBLICKEYBYTES);
    qsort(onion_a->entries, ONION_ANNOUNCE_MAX_ENTRIES, sizeof(Onion_Announce_Entry), cmp_entry);
    return in_entries(onion_a, public_key);
}