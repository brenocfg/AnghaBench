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
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int errno ; 
 int fchmod_and_chown (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int sync_rights(FILE *from, FILE *to) {
        struct stat st;

        if (fstat(fileno(from), &st) < 0)
                return -errno;

        return fchmod_and_chown(fileno(to), st.st_mode & 07777, st.st_uid, st.st_gid);
}