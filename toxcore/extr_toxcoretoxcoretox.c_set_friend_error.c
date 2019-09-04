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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  TOX_ERR_FRIEND_ADD ;

/* Variables and functions */
#define  FAERR_ALREADYSENT 134 
#define  FAERR_BADCHECKSUM 133 
#define  FAERR_NOMEM 132 
#define  FAERR_NOMESSAGE 131 
#define  FAERR_OWNKEY 130 
#define  FAERR_SETNEWNOSPAM 129 
#define  FAERR_TOOLONG 128 
 int /*<<< orphan*/  SET_ERROR_PARAMETER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_ALREADY_SENT ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_BAD_CHECKSUM ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_MALLOC ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_NO_MESSAGE ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_OWN_KEY ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_SET_NEW_NOSPAM ; 
 int /*<<< orphan*/  TOX_ERR_FRIEND_ADD_TOO_LONG ; 

__attribute__((used)) static void set_friend_error(int32_t ret, TOX_ERR_FRIEND_ADD *error)
{
    switch (ret) {
        case FAERR_TOOLONG:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_TOO_LONG);
            break;

        case FAERR_NOMESSAGE:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_NO_MESSAGE);
            break;

        case FAERR_OWNKEY:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_OWN_KEY);
            break;

        case FAERR_ALREADYSENT:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_ALREADY_SENT);
            break;

        case FAERR_BADCHECKSUM:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_BAD_CHECKSUM);
            break;

        case FAERR_SETNEWNOSPAM:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_SET_NEW_NOSPAM);
            break;

        case FAERR_NOMEM:
            SET_ERROR_PARAMETER(error, TOX_ERR_FRIEND_ADD_MALLOC);
            break;

    }
}