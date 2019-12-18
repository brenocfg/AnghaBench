#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_7__ {int /*<<< orphan*/  public_key; TYPE_2__ assoc6; TYPE_1__ assoc4; } ;
typedef  TYPE_3__ Client_data ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 int id_closest (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int store_node_ok(const Client_data *client, const uint8_t *public_key, const uint8_t *comp_public_key)
{
    if ((is_timeout(client->assoc4.timestamp, BAD_NODE_TIMEOUT) && is_timeout(client->assoc6.timestamp, BAD_NODE_TIMEOUT))
            || (id_closest(comp_public_key, client->public_key, public_key) == 2)) {
        return 1;
    } else {
        return 0;
    }
}