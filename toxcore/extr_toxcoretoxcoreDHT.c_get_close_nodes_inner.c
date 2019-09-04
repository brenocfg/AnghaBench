#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_12__ {int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {scalar_t__ timestamp; TYPE_8__ ip_port; int /*<<< orphan*/  hardening; } ;
struct TYPE_11__ {int /*<<< orphan*/  public_key; TYPE_2__ assoc6; TYPE_2__ assoc4; } ;
struct TYPE_9__ {TYPE_8__ ip_port; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Node_format ;
typedef  TYPE_2__ IPPTsPng ;
typedef  TYPE_3__ Client_data ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 scalar_t__ HARDENING_ALL_OK ; 
 scalar_t__ LAN_ip (int /*<<< orphan*/ ) ; 
 size_t MAX_SENT_NODES ; 
 int /*<<< orphan*/  add_to_list (TYPE_1__*,size_t,int /*<<< orphan*/ ,TYPE_8__,scalar_t__ const*) ; 
 scalar_t__ client_in_nodelist (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ hardening_correct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  id_equal (scalar_t__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_timeout (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_close_nodes_inner(const uint8_t *public_key, Node_format *nodes_list,
                                  sa_family_t sa_family, const Client_data *client_list, uint32_t client_list_length,
                                  uint32_t *num_nodes_ptr, uint8_t is_LAN, uint8_t want_good)
{
    if ((sa_family != AF_INET) && (sa_family != AF_INET6) && (sa_family != 0))
        return;

    uint32_t num_nodes = *num_nodes_ptr;
    uint32_t i;

    for (i = 0; i < client_list_length; i++) {
        const Client_data *client = &client_list[i];

        /* node already in list? */
        if (client_in_nodelist(nodes_list, MAX_SENT_NODES, client->public_key))
            continue;

        const IPPTsPng *ipptp = NULL;

        if (sa_family == AF_INET) {
            ipptp = &client->assoc4;
        } else if (sa_family == AF_INET6) {
            ipptp = &client->assoc6;
        } else {
            if (client->assoc4.timestamp >= client->assoc6.timestamp) {
                ipptp = &client->assoc4;
            } else {
                ipptp = &client->assoc6;
            }
        }

        /* node not in a good condition? */
        if (is_timeout(ipptp->timestamp, BAD_NODE_TIMEOUT))
            continue;

        /* don't send LAN ips to non LAN peers */
        if (LAN_ip(ipptp->ip_port.ip) == 0 && !is_LAN)
            continue;

        if (LAN_ip(ipptp->ip_port.ip) != 0 && want_good && hardening_correct(&ipptp->hardening) != HARDENING_ALL_OK
                && !id_equal(public_key, client->public_key))
            continue;

        if (num_nodes < MAX_SENT_NODES) {
            memcpy(nodes_list[num_nodes].public_key,
                   client->public_key,
                   crypto_box_PUBLICKEYBYTES );

            nodes_list[num_nodes].ip_port = ipptp->ip_port;
            num_nodes++;
        } else {
            add_to_list(nodes_list, MAX_SENT_NODES, client->public_key, ipptp->ip_port, public_key);
        }
    }

    *num_nodes_ptr = num_nodes;
}