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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int TOX_USER_STATUS ;
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY_FRIEND_NOT_FOUND ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY_OK ; 
 int TOX_USER_STATUS_BUSY ; 
 int USERSTATUS_INVALID ; 
 int m_get_userstatus (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

TOX_USER_STATUS tox_friend_get_status(const Tox *tox, uint32_t friend_number, TOX_ERR_FRIEND_QUERY *error)
{
    const Messenger *m = tox;

    int ret = m_get_userstatus(m, friend_number);

    if (ret == USERSTATUS_INVALID) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_QUERY_FRIEND_NOT_FOUND);
        return TOX_USER_STATUS_BUSY + 1;
    }

    SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_QUERY_OK);
    return ret;
}