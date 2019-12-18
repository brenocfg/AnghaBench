#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_15__ {int send_nodes_ok; int /*<<< orphan*/  send_nodes_pingedid; int /*<<< orphan*/  send_nodes_timestamp; } ;
struct TYPE_18__ {TYPE_2__ hardening; } ;
struct TYPE_14__ {int /*<<< orphan*/  family; } ;
struct TYPE_17__ {TYPE_1__ ip; } ;
struct TYPE_16__ {TYPE_4__ ip_port; struct TYPE_16__* public_key; } ;
typedef  TYPE_3__ Node_format ;
typedef  TYPE_4__ IP_Port ;
typedef  TYPE_5__ IPPTsPng ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
#define  CHECK_TYPE_GETNODE_REQ 129 
#define  CHECK_TYPE_GETNODE_RES 128 
 int /*<<< orphan*/  HARDENING_INTERVAL ; 
 int HARDREQ_DATA_SIZE ; 
 int MAX_SENT_NODES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 TYPE_5__* get_closelist_IPPTsPng (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ) ; 
 int getnodes (int /*<<< orphan*/ *,TYPE_4__,TYPE_3__*,int const*,TYPE_3__*) ; 
 int /*<<< orphan*/  have_nodes_closelist (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int const*,int) ; 
 int /*<<< orphan*/  public_key_cmp (int /*<<< orphan*/ ,int const*) ; 
 int unpack_nodes (TYPE_3__*,int,int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_hardening(void *object, IP_Port source, const uint8_t *source_pubkey, const uint8_t *packet,
                            uint16_t length)
{
    DHT *dht = object;

    if (length < 2) {
        return 1;
    }

    switch (packet[0]) {
        case CHECK_TYPE_GETNODE_REQ: {
            if (length != HARDREQ_DATA_SIZE)
                return 1;

            Node_format node, tocheck_node;
            node.ip_port = source;
            memcpy(node.public_key, source_pubkey, crypto_box_PUBLICKEYBYTES);
            memcpy(&tocheck_node, packet + 1, sizeof(Node_format));

            if (getnodes(dht, tocheck_node.ip_port, tocheck_node.public_key, packet + 1 + sizeof(Node_format), &node) == -1)
                return 1;

            return 0;
        }

        case CHECK_TYPE_GETNODE_RES: {
            if (length <= crypto_box_PUBLICKEYBYTES + 1)
                return 1;

            if (length > 1 + crypto_box_PUBLICKEYBYTES + sizeof(Node_format) * MAX_SENT_NODES)
                return 1;

            uint16_t length_nodes = length - 1 - crypto_box_PUBLICKEYBYTES;
            Node_format nodes[MAX_SENT_NODES];
            int num_nodes = unpack_nodes(nodes, MAX_SENT_NODES, 0, packet + 1 + crypto_box_PUBLICKEYBYTES, length_nodes, 0);

            /* TODO: MAX_SENT_NODES nodes should be returned at all times
             (right now we have a small network size so it could cause problems for testing and etc..) */
            if (num_nodes <= 0)
                return 1;

            /* NOTE: This should work for now but should be changed to something better. */
            if (have_nodes_closelist(dht, nodes, num_nodes) < (uint32_t)((num_nodes + 2) / 2))
                return 1;

            IPPTsPng *temp = get_closelist_IPPTsPng(dht, packet + 1, nodes[0].ip_port.ip.family);

            if (temp == NULL)
                return 1;

            if (is_timeout(temp->hardening.send_nodes_timestamp, HARDENING_INTERVAL))
                return 1;

            if (public_key_cmp(temp->hardening.send_nodes_pingedid, source_pubkey) != 0)
                return 1;

            /* If Nodes look good and the request checks out */
            temp->hardening.send_nodes_ok = 1;
            return 0;/* success*/
        }
    }

    return 1;
}