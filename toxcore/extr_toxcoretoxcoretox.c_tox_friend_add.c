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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_ADD ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_NULL ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_OK ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ m_addfriend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  set_friend_error (scalar_t__,int /*<<< orphan*/ *) ; 

uint32_t tox_friend_add(Tox *tox, const uint8_t *address, const uint8_t *message, size_t length,
                        TOX_ERR_FRIEND_ADD *error)
{
    if (!address || !message) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_NULL);
        return UINT32_MAX;
    }

    Messenger *m = tox;
    int32_t ret = m_addfriend(m, address, message, length);

    if (ret >= 0) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_OK);
        return ret;
    }

    set_friend_error(ret, error);
    return UINT32_MAX;
}