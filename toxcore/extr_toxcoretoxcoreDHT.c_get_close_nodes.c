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
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int MAX_SENT_NODES ; 
 int get_somewhat_close_nodes (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int get_close_nodes(const DHT *dht, const uint8_t *public_key, Node_format *nodes_list, sa_family_t sa_family,
                    uint8_t is_LAN, uint8_t want_good)
{
    memset(nodes_list, 0, MAX_SENT_NODES * sizeof(Node_format));
#ifdef ENABLE_ASSOC_DHT

    if (!dht->assoc)
#endif
        return get_somewhat_close_nodes(dht, public_key, nodes_list, sa_family, is_LAN, want_good);

#ifdef ENABLE_ASSOC_DHT
    //TODO: assoc, sa_family 0 (don't care if ipv4 or ipv6) support.
    Client_data *result[MAX_SENT_NODES];

    Assoc_close_entries request;
    memset(&request, 0, sizeof(request));
    request.count = MAX_SENT_NODES;
    request.count_good = MAX_SENT_NODES - 2; /* allow 2 'indirect' nodes */
    request.result = result;
    request.wanted_id = public_key;
    request.flags = (is_LAN ? LANOk : 0) + (sa_family == AF_INET ? ProtoIPv4 : ProtoIPv6);

    uint8_t num_found = Assoc_get_close_entries(dht->assoc, &request);

    if (!num_found) {
        LOGGER_DEBUG("get_close_nodes(): Assoc_get_close_entries() returned zero nodes");
        return get_somewhat_close_nodes(dht, public_key, nodes_list, sa_family, is_LAN, want_good);
    }

    LOGGER_DEBUG("get_close_nodes(): Assoc_get_close_entries() returned %i 'direct' and %i 'indirect' nodes",
                 request.count_good, num_found - request.count_good);

    uint8_t i, num_returned = 0;

    for (i = 0; i < num_found; i++) {
        Client_data *client = result[i];

        if (client) {
            id_copy(nodes_list[num_returned].public_key, client->public_key);

            if (sa_family == AF_INET)
                if (ipport_isset(&client->assoc4.ip_port)) {
                    nodes_list[num_returned].ip_port = client->assoc4.ip_port;
                    num_returned++;
                    continue;
                }

            if (sa_family == AF_INET6)
                if (ipport_isset(&client->assoc6.ip_port)) {
                    nodes_list[num_returned].ip_port = client->assoc6.ip_port;
                    num_returned++;
                    continue;
                }
        }
    }

    return num_returned;
#endif
}