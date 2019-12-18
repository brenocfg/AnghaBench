#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int crypt_connection_id; } ;
typedef  int /*<<< orphan*/  Friend_Connections ;
typedef  TYPE_1__ Friend_Conn ;

/* Variables and functions */
 TYPE_1__* get_conn (int /*<<< orphan*/ *,int) ; 

int friend_connection_crypt_connection_id(Friend_Connections *fr_c, int friendcon_id)
{
    Friend_Conn *friend_con = get_conn(fr_c, friendcon_id);

    if (!friend_con)
        return -1;

    return friend_con->crypt_connection_id;
}