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
typedef  int /*<<< orphan*/  uid_t ;
struct stat {int /*<<< orphan*/  st_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 char* uid_to_name (int /*<<< orphan*/ ) ; 

char* getlogname_malloc(void) {
        uid_t uid;
        struct stat st;

        if (isatty(STDIN_FILENO) && fstat(STDIN_FILENO, &st) >= 0)
                uid = st.st_uid;
        else
                uid = getuid();

        return uid_to_name(uid);
}