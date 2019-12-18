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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  TOX_MESSAGE_TYPE ;
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_SEND_MESSAGE ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_SEND_MESSAGE_EMPTY ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_SEND_MESSAGE_NULL ; 
 int /*<<< orphan*/  m_send_message_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t tox_friend_send_message(Tox *tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t *message,
                                 size_t length, TOX_ERR_FRIEND_SEND_MESSAGE *error)
{
    if (!message) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_SEND_MESSAGE_NULL);
        return 0;
    }

    if (!length) {
        SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_SEND_MESSAGE_EMPTY);
        return 0;
    }

    Messenger *m = tox;
    uint32_t message_id = 0;
    set_message_error(m_send_message_generic(m, friend_number, type, message, length, &message_id), error);
    return message_id;
}