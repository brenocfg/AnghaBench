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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  HANDLE_ACTION ; 
 int /*<<< orphan*/  INHIBIT_MODE ; 
 int /*<<< orphan*/  KILL_WHO ; 
 int /*<<< orphan*/  SESSION_CLASS ; 
 int /*<<< orphan*/  SESSION_STATE ; 
 int /*<<< orphan*/  SESSION_TYPE ; 
 int /*<<< orphan*/  USER_STATE ; 
 int /*<<< orphan*/  handle_action ; 
 int /*<<< orphan*/  inhibit_mode ; 
 int /*<<< orphan*/  kill_who ; 
 int /*<<< orphan*/  session_class ; 
 int /*<<< orphan*/  session_state ; 
 int /*<<< orphan*/  session_type ; 
 int /*<<< orphan*/  test_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_state ; 

int main(int argc, char **argv) {
        test_table(handle_action, HANDLE_ACTION);
        test_table(inhibit_mode, INHIBIT_MODE);
        test_table(kill_who, KILL_WHO);
        test_table(session_class, SESSION_CLASS);
        test_table(session_state, SESSION_STATE);
        test_table(session_type, SESSION_TYPE);
        test_table(user_state, USER_STATE);

        return EXIT_SUCCESS;
}