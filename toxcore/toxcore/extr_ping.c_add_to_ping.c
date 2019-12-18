#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int /*<<< orphan*/  ip; } ;
struct TYPE_19__ {int /*<<< orphan*/  self_public_key; int /*<<< orphan*/  close_clientlist; } ;
struct TYPE_18__ {int /*<<< orphan*/  ip; } ;
struct TYPE_17__ {TYPE_5__* dht; TYPE_12__* to_ping; } ;
struct TYPE_16__ {int /*<<< orphan*/  public_key; TYPE_7__ ip_port; } ;
typedef  TYPE_1__ PING ;
typedef  TYPE_2__ IP_Port ;

/* Variables and functions */
 scalar_t__ DHT_getfriendip (TYPE_5__*,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 int /*<<< orphan*/  LCLIENT_LIST ; 
 unsigned int MAX_TO_PING ; 
 scalar_t__ add_to_list (TYPE_12__*,unsigned int,int /*<<< orphan*/  const*,TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ in_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_2__) ; 
 int /*<<< orphan*/  ip_isset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipport_copy (TYPE_7__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_addable_to_close_list (TYPE_5__*,int /*<<< orphan*/  const*,TYPE_2__) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  send_ping_request (TYPE_1__*,TYPE_2__,int /*<<< orphan*/  const*) ; 

int add_to_ping(PING *ping, const uint8_t *public_key, IP_Port ip_port)
{
    if (!ip_isset(&ip_port.ip))
        return -1;

    if (!node_addable_to_close_list(ping->dht, public_key, ip_port))
        return -1;

    if (in_list(ping->dht->close_clientlist, LCLIENT_LIST, public_key, ip_port))
        return -1;

    IP_Port temp;

    if (DHT_getfriendip(ping->dht, public_key, &temp) == 0) {
        send_ping_request(ping, ip_port, public_key);
        return -1;
    }

    unsigned int i;

    for (i = 0; i < MAX_TO_PING; ++i) {
        if (!ip_isset(&ping->to_ping[i].ip_port.ip)) {
            memcpy(ping->to_ping[i].public_key, public_key, crypto_box_PUBLICKEYBYTES);
            ipport_copy(&ping->to_ping[i].ip_port, &ip_port);
            return 0;
        }

        if (public_key_cmp(ping->to_ping[i].public_key, public_key) == 0) {
            return -1;
        }
    }

    if (add_to_list(ping->to_ping, MAX_TO_PING, public_key, ip_port, ping->dht->self_public_key))
        return 0;

    return -1;
}