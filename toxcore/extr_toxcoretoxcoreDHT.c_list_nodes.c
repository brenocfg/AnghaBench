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
typedef  size_t uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {int /*<<< orphan*/  public_key; TYPE_2__ assoc6; TYPE_2__ assoc4; } ;
struct TYPE_6__ {int /*<<< orphan*/  ip_port; int /*<<< orphan*/  public_key; } ;
typedef  TYPE_1__ Node_format ;
typedef  TYPE_2__ IPPTsPng ;
typedef  TYPE_3__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rand () ; 

uint16_t list_nodes(Client_data *list, unsigned int length, Node_format *nodes, uint16_t max_num)
{
    if (max_num == 0)
        return 0;

    uint16_t count = 0;

    unsigned int i;

    for (i = length; i != 0; --i) {
        IPPTsPng *assoc = NULL;

        if (!is_timeout(list[i - 1].assoc4.timestamp, BAD_NODE_TIMEOUT))
            assoc = &list[i - 1].assoc4;

        if (!is_timeout(list[i - 1].assoc6.timestamp, BAD_NODE_TIMEOUT)) {
            if (assoc == NULL)
                assoc = &list[i - 1].assoc6;
            else if (rand() % 2)
                assoc = &list[i - 1].assoc6;
        }

        if (assoc != NULL) {
            memcpy(nodes[count].public_key, list[i - 1].public_key, crypto_box_PUBLICKEYBYTES);
            nodes[count].ip_port = assoc->ip_port;
            ++count;

            if (count >= max_num)
                return count;
        }
    }

    return count;
}