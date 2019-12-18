#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* usri1_password; void* usri1_name; int /*<<< orphan*/ * usri1_script_path; int /*<<< orphan*/  usri1_flags; int /*<<< orphan*/ * usri1_comment; int /*<<< orphan*/ * usri1_home_dir; int /*<<< orphan*/  usri1_priv; } ;
typedef  TYPE_1__ USER_INFO_1 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INVALID_LEVEL ; 
 scalar_t__ NERR_BadUsername ; 
 scalar_t__ NERR_PasswordTooShort ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NERR_UserExists ; 
 scalar_t__ NERR_UserNotFound ; 
 int /*<<< orphan*/  UF_SCRIPT ; 
 int /*<<< orphan*/  USER_PRIV_USER ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pNetUserAdd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNetUserDel (int /*<<< orphan*/ *,void*) ; 
 void* sTestUserName ; 
 void* sTestUserOldPass ; 
 void* sTooLongName ; 
 void* sTooLongPassword ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void run_userhandling_tests(void)
{
    NET_API_STATUS ret;
    USER_INFO_1 usri;

    usri.usri1_priv = USER_PRIV_USER;
    usri.usri1_home_dir = NULL;
    usri.usri1_comment = NULL;
    usri.usri1_flags = UF_SCRIPT;
    usri.usri1_script_path = NULL;

    usri.usri1_name = sTooLongName;
    usri.usri1_password = sTestUserOldPass;

    ret = pNetUserAdd(NULL, 1, (LPBYTE)&usri, NULL);
    if (ret == NERR_Success || ret == NERR_UserExists)
    {
        /* Windows NT4 does create the user. Delete the user and also if it already existed
         * due to a previous test run on NT4.
         */
        trace("We are on NT4, we have to delete the user with the too long username\n");
        ret = pNetUserDel(NULL, sTooLongName);
        ok(ret == NERR_Success, "Deleting the user failed : %d\n", ret);
    }
    else if (ret == ERROR_ACCESS_DENIED)
    {
        skip("not enough permissions to add a user\n");
        return;
    }
    else
        ok(ret == NERR_BadUsername ||
           broken(ret == NERR_PasswordTooShort), /* NT4 */
           "Adding user with too long username returned 0x%08x\n", ret);

    usri.usri1_name = sTestUserName;
    usri.usri1_password = sTooLongPassword;

    ret = pNetUserAdd(NULL, 1, (LPBYTE)&usri, NULL);
    ok(ret == NERR_PasswordTooShort || ret == ERROR_ACCESS_DENIED /* Win2003 */,
       "Adding user with too long password returned 0x%08x\n", ret);

    usri.usri1_name = sTooLongName;
    usri.usri1_password = sTooLongPassword;

    ret = pNetUserAdd(NULL, 1, (LPBYTE)&usri, NULL);
    /* NT4 doesn't have a problem with the username so it will report the too long password
     * as the error. NERR_PasswordTooShort is reported for all kind of password related errors.
     */
    ok(ret == NERR_BadUsername || ret == NERR_PasswordTooShort,
            "Adding user with too long username/password returned 0x%08x\n", ret);

    usri.usri1_name = sTestUserName;
    usri.usri1_password = sTestUserOldPass;

    ret = pNetUserAdd(NULL, 5, (LPBYTE)&usri, NULL);
    ok(ret == ERROR_INVALID_LEVEL, "Adding user with level 5 returned 0x%08x\n", ret);

    ret = pNetUserAdd(NULL, 1, (LPBYTE)&usri, NULL);
    if(ret == ERROR_ACCESS_DENIED)
    {
        skip("Insufficient permissions to add users. Skipping test.\n");
        return;
    }
    if(ret == NERR_UserExists)
    {
        skip("User already exists, skipping test to not mess up the system\n");
        return;
    }

    ok(ret == NERR_Success ||
       broken(ret == NERR_PasswordTooShort), /* NT4 */
       "Adding user failed with error 0x%08x\n", ret);
    if(ret != NERR_Success)
        return;

    /* On Windows XP (and newer), calling NetUserChangePassword with a NULL
     * domainname parameter creates a user home directory, iff the machine is
     * not member of a domain.
     * Using \\127.0.0.1 as domain name does not work on standalone machines
     * either, unless the ForceGuest option in the registry is turned off.
     * So let's not test NetUserChangePassword for now.
     */

    ret = pNetUserDel(NULL, sTestUserName);
    ok(ret == NERR_Success, "Deleting the user failed.\n");

    ret = pNetUserDel(NULL, sTestUserName);
    ok(ret == NERR_UserNotFound, "Deleting a nonexistent user returned 0x%08x\n",ret);
}