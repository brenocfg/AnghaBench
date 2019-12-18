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

/* Variables and functions */
 int GID_NOBODY ; 
 char* NOBODY_GROUP_NAME ; 
 char* NOBODY_USER_NAME ; 
 char* NOLOGIN ; 
 int TTY_GID ; 
 int UID_NOBODY ; 
 int /*<<< orphan*/  test_get_group_creds_one (char*,char*,int) ; 
 int /*<<< orphan*/  test_get_user_creds_one (char*,char*,int,int,char*,char*) ; 
 int /*<<< orphan*/  test_gid_to_name_one (int,char*) ; 
 int /*<<< orphan*/  test_in_gid () ; 
 int /*<<< orphan*/  test_make_salt () ; 
 int /*<<< orphan*/  test_parse_uid () ; 
 int /*<<< orphan*/  test_uid_ptr () ; 
 int /*<<< orphan*/  test_uid_to_name_one (int,char*) ; 
 int /*<<< orphan*/  test_valid_gecos () ; 
 int /*<<< orphan*/  test_valid_home () ; 
 int /*<<< orphan*/  test_valid_user_group_name () ; 
 int /*<<< orphan*/  test_valid_user_group_name_compat () ; 
 int /*<<< orphan*/  test_valid_user_group_name_or_id () ; 
 int /*<<< orphan*/  test_valid_user_group_name_or_id_compat () ; 

int main(int argc, char *argv[]) {
        test_uid_to_name_one(0, "root");
        test_uid_to_name_one(UID_NOBODY, NOBODY_USER_NAME);
        test_uid_to_name_one(0xFFFF, "65535");
        test_uid_to_name_one(0xFFFFFFFF, "4294967295");

        test_gid_to_name_one(0, "root");
        test_gid_to_name_one(GID_NOBODY, NOBODY_GROUP_NAME);
        test_gid_to_name_one(TTY_GID, "tty");
        test_gid_to_name_one(0xFFFF, "65535");
        test_gid_to_name_one(0xFFFFFFFF, "4294967295");

        test_get_user_creds_one("root", "root", 0, 0, "/root", "/bin/sh");
        test_get_user_creds_one("0", "root", 0, 0, "/root", "/bin/sh");
        test_get_user_creds_one(NOBODY_USER_NAME, NOBODY_USER_NAME, UID_NOBODY, GID_NOBODY, "/", NOLOGIN);
        test_get_user_creds_one("65534", NOBODY_USER_NAME, UID_NOBODY, GID_NOBODY, "/", NOLOGIN);

        test_get_group_creds_one("root", "root", 0);
        test_get_group_creds_one("0", "root", 0);
        test_get_group_creds_one(NOBODY_GROUP_NAME, NOBODY_GROUP_NAME, GID_NOBODY);
        test_get_group_creds_one("65534", NOBODY_GROUP_NAME, GID_NOBODY);

        test_parse_uid();
        test_uid_ptr();

        test_valid_user_group_name_compat();
        test_valid_user_group_name();
        test_valid_user_group_name_or_id_compat();
        test_valid_user_group_name_or_id();
        test_valid_gecos();
        test_valid_home();

        test_make_salt();

        test_in_gid();

        return 0;
}