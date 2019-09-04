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
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_BY_PUBLIC_KEY ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_BY_PUBLIC_KEY_NOT_FOUND ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_BY_PUBLIC_KEY_NULL ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK ; 
 int UINT32_MAX ; 
 int getfriend_id (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

uint32_t tox_friend_by_public_key(const Tox *tox, const uint8_t *public_key, TOX_ERR_FRIEND_BY_PUBLIC_KEY *error)
{
    if (!public_key) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_BY_PUBLIC_KEY_NULL);
        return UINT32_MAX;
    }

    const Messenger *m = tox;
    int32_t ret = getfriend_id(m, public_key);

    if (ret == -1) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_BY_PUBLIC_KEY_NOT_FOUND);
        return UINT32_MAX;
    }

    SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_BY_PUBLIC_KEY_OK);
    return ret;
}