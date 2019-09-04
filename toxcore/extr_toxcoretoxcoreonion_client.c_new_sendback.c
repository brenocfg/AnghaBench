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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int /*<<< orphan*/  announce_ping_array; } ;
typedef  TYPE_1__ Onion_Client ;
typedef  int /*<<< orphan*/  const IP_Port ;

/* Variables and functions */
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ping_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int new_sendback(Onion_Client *onion_c, uint32_t num, const uint8_t *public_key, IP_Port ip_port,
                        uint32_t path_num, uint64_t *sendback)
{
    uint8_t data[sizeof(uint32_t) + crypto_box_PUBLICKEYBYTES + sizeof(IP_Port) + sizeof(uint32_t)];
    memcpy(data, &num, sizeof(uint32_t));
    memcpy(data + sizeof(uint32_t), public_key, crypto_box_PUBLICKEYBYTES);
    memcpy(data + sizeof(uint32_t) + crypto_box_PUBLICKEYBYTES, &ip_port, sizeof(IP_Port));
    memcpy(data + sizeof(uint32_t) + crypto_box_PUBLICKEYBYTES + sizeof(IP_Port), &path_num, sizeof(uint32_t));
    *sendback = ping_array_add(&onion_c->announce_ping_array, data, sizeof(data));

    if (*sendback == 0)
        return -1;

    return 0;
}