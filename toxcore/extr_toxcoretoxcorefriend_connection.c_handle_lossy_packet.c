#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_1__* callbacks; } ;
struct TYPE_4__ {int /*<<< orphan*/  lossy_data_callback_id; int /*<<< orphan*/  lossy_data_callback_object; int /*<<< orphan*/  (* lossy_data_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Friend_Connections ;
typedef  TYPE_2__ Friend_Conn ;

/* Variables and functions */
 unsigned int MAX_FRIEND_CONNECTION_CALLBACKS ; 
 TYPE_2__* get_conn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_lossy_packet(void *object, int number, const uint8_t *data, uint16_t length)
{
    if (length == 0)
        return -1;

    Friend_Connections *fr_c = object;
    Friend_Conn *friend_con = get_conn(fr_c, number);

    if (!friend_con)
        return -1;

    unsigned int i;

    for (i = 0; i < MAX_FRIEND_CONNECTION_CALLBACKS; ++i) {
        if (friend_con->callbacks[i].lossy_data_callback)
            friend_con->callbacks[i].lossy_data_callback(friend_con->callbacks[i].lossy_data_callback_object,
                    friend_con->callbacks[i].lossy_data_callback_id, data, length);

        friend_con = get_conn(fr_c, number);

        if (!friend_con)
            return -1;
    }

    return 0;
}