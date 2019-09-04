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
struct TYPE_2__ {int /*<<< orphan*/ * usri1_script_path; int /*<<< orphan*/  usri1_flags; int /*<<< orphan*/ * usri1_comment; int /*<<< orphan*/ * usri1_home_dir; int /*<<< orphan*/  usri1_priv; int /*<<< orphan*/  usri1_password; int /*<<< orphan*/  usri1_name; } ;
typedef  TYPE_1__ USER_INFO_1 ;
typedef  int /*<<< orphan*/  NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  UF_SCRIPT ; 
 int /*<<< orphan*/  USER_PRIV_USER ; 
 int /*<<< orphan*/  pNetUserAdd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sTestUserName ; 
 int /*<<< orphan*/  sTestUserOldPass ; 

__attribute__((used)) static NET_API_STATUS create_test_user(void)
{
    USER_INFO_1 usri;

    usri.usri1_name = sTestUserName;
    usri.usri1_password = sTestUserOldPass;
    usri.usri1_priv = USER_PRIV_USER;
    usri.usri1_home_dir = NULL;
    usri.usri1_comment = NULL;
    usri.usri1_flags = UF_SCRIPT;
    usri.usri1_script_path = NULL;

    return pNetUserAdd(NULL, 1, (LPBYTE)&usri, NULL);
}