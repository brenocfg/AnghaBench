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
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY_FRIEND_NOT_FOUND ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_QUERY_OK ; 
 int m_get_name_size (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

size_t tox_friend_get_name_size(const Tox *tox, uint32_t friend_number, TOX_ERR_FRIEND_QUERY *error)
{
    const Messenger *m = tox;
    int ret = m_get_name_size(m, friend_number);

    if (ret == -1) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_QUERY_FRIEND_NOT_FOUND);
        return SIZE_MAX;
    }

    SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_QUERY_OK);
    return ret;
}