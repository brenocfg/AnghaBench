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
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_CONNECTED ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_FOUND ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_INVALID ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_OK ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_SENDQ ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_CUSTOM_PACKET_TOO_LONG ; 

__attribute__((used)) static void set_custom_packet_error(int ret, TOX_ERR_FRIEND_CUSTOM_PACKET *error)
{
    switch (ret) {
        case 0:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_OK);
            break;

        case -1:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_FOUND);
            break;

        case -2:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_TOO_LONG);
            break;

        case -3:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_INVALID);
            break;

        case -4:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_FRIEND_NOT_CONNECTED);
            break;

        case -5:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_CUSTOM_PACKET_SENDQ);
            break;
    }
}