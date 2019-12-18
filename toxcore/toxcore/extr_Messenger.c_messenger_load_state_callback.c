#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  self_public_key; } ;
struct TYPE_10__ {int /*<<< orphan*/  onion_c; int /*<<< orphan*/  has_added_relays; TYPE_1__* loaded_relays; int /*<<< orphan*/  dht; TYPE_7__* net_crypto; int /*<<< orphan*/  fr; } ;
struct TYPE_9__ {int /*<<< orphan*/  public_key; int /*<<< orphan*/  ip_port; } ;
typedef  TYPE_1__ Node_format ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  DHT_load (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int MAX_NAME_LENGTH ; 
 int MAX_STATUSMESSAGE_LENGTH ; 
#define  MESSENGER_STATE_TYPE_DHT 136 
#define  MESSENGER_STATE_TYPE_END 135 
#define  MESSENGER_STATE_TYPE_FRIENDS 134 
#define  MESSENGER_STATE_TYPE_NAME 133 
#define  MESSENGER_STATE_TYPE_NOSPAMKEYS 132 
#define  MESSENGER_STATE_TYPE_PATH_NODE 131 
#define  MESSENGER_STATE_TYPE_STATUS 130 
#define  MESSENGER_STATE_TYPE_STATUSMESSAGE 129 
#define  MESSENGER_STATE_TYPE_TCP_RELAY 128 
 int NUM_SAVED_PATH_NODES ; 
 int NUM_SAVED_TCP_RELAYS ; 
 scalar_t__ crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ crypto_box_SECRETKEYBYTES ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  friends_list_load (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  load_secret_key (TYPE_7__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  m_set_statusmessage (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  m_set_userstatus (TYPE_2__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  onion_add_bs_path_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  public_key_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nospam (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setname (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int unpack_nodes (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int messenger_load_state_callback(void *outer, const uint8_t *data, uint32_t length, uint16_t type)
{
    Messenger *m = outer;

    switch (type) {
        case MESSENGER_STATE_TYPE_NOSPAMKEYS:
            if (length == crypto_box_PUBLICKEYBYTES + crypto_box_SECRETKEYBYTES + sizeof(uint32_t)) {
                set_nospam(&(m->fr), *(uint32_t *)data);
                load_secret_key(m->net_crypto, (&data[sizeof(uint32_t)]) + crypto_box_PUBLICKEYBYTES);

                if (public_key_cmp((&data[sizeof(uint32_t)]), m->net_crypto->self_public_key) != 0) {
                    return -1;
                }
            } else
                return -1;    /* critical */

            break;

        case MESSENGER_STATE_TYPE_DHT:
            DHT_load(m->dht, data, length);
            break;

        case MESSENGER_STATE_TYPE_FRIENDS:
            friends_list_load(m, data, length);
            break;

        case MESSENGER_STATE_TYPE_NAME:
            if ((length > 0) && (length <= MAX_NAME_LENGTH)) {
                setname(m, data, length);
            }

            break;

        case MESSENGER_STATE_TYPE_STATUSMESSAGE:
            if ((length > 0) && (length < MAX_STATUSMESSAGE_LENGTH)) {
                m_set_statusmessage(m, data, length);
            }

            break;

        case MESSENGER_STATE_TYPE_STATUS:
            if (length == 1) {
                m_set_userstatus(m, *data);
            }

            break;

        case MESSENGER_STATE_TYPE_TCP_RELAY: {
            if (length == 0) {
                break;
            }

            unpack_nodes(m->loaded_relays, NUM_SAVED_TCP_RELAYS, 0, data, length, 1);
            m->has_added_relays = 0;

            break;
        }

        case MESSENGER_STATE_TYPE_PATH_NODE: {
            Node_format nodes[NUM_SAVED_PATH_NODES];

            if (length == 0) {
                break;
            }

            int i, num = unpack_nodes(nodes, NUM_SAVED_PATH_NODES, 0, data, length, 0);

            for (i = 0; i < num; ++i) {
                onion_add_bs_path_node(m->onion_c, nodes[i].ip_port, nodes[i].public_key);
            }

            break;
        }

        case MESSENGER_STATE_TYPE_END: {
            if (length != 0) {
                return -1;
            }

            return -2;
            break;
        }

#ifdef DEBUG

        default:
            fprintf(stderr, "Load state: contains unrecognized part (len %u, type %u)\n",
                    length, type);
            break;
#endif
    }

    return 0;
}