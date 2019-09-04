#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  real_public_key; } ;
struct TYPE_6__ {scalar_t__ num_cons; } ;
typedef  TYPE_1__ Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 TYPE_2__* get_conn (TYPE_1__*,scalar_t__) ; 
 scalar_t__ public_key_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int getfriend_conn_id_pk(Friend_Connections *fr_c, const uint8_t *real_pk)
{
    uint32_t i;

    for (i = 0; i < fr_c->num_cons; ++i) {
        Friend_Conn *friend_con = get_conn(fr_c, i);

        if (friend_con) {
            if (public_key_cmp(friend_con->real_public_key, real_pk) == 0)
                return i;
        }
    }

    return -1;
}