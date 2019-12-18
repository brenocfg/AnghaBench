#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int loaded_num_nodes; int /*<<< orphan*/  loaded_nodes_list; } ;
typedef  int /*<<< orphan*/  Node_format ;
typedef  TYPE_1__ DHT ;

/* Variables and functions */
#define  DHT_STATE_TYPE_NODES 128 
 int /*<<< orphan*/  MAX_SAVED_DHT_NODES ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int unpack_nodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dht_load_state_callback(void *outer, const uint8_t *data, uint32_t length, uint16_t type)
{
    DHT *dht = outer;

    switch (type) {
        case DHT_STATE_TYPE_NODES:
            if (length == 0)
                break;

            {
                free(dht->loaded_nodes_list);
                // Copy to loaded_clients_list
                dht->loaded_nodes_list = calloc(MAX_SAVED_DHT_NODES, sizeof(Node_format));

                int num = unpack_nodes(dht->loaded_nodes_list, MAX_SAVED_DHT_NODES, NULL, data, length, 0);

                if (num > 0) {
                    dht->loaded_num_nodes = num;
                } else {
                    dht->loaded_num_nodes = 0;
                }

            } /* localize declarations */

            break;

#ifdef DEBUG

        default:
            fprintf(stderr, "Load state (DHT): contains unrecognized part (len %u, type %u)\n",
                    length, type);
            break;
#endif
    }

    return 0;
}