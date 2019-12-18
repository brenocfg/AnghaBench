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
struct passwd {int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_uid; scalar_t__ pw_gid; } ;
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ geteuid () ; 
 struct group* getgrnam (char*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 char* set_group_name ; 
 char* set_user_name ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setgroups (int,scalar_t__*) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int change_user_group () {
  char *username = set_user_name;
  char *groupname = set_group_name;
  struct passwd *pw;
  /* lose root privileges if we have them */
  if (getuid() == 0 || geteuid() == 0) {
    if (username == 0 || *username == '\0') {
      username = "telegramd";
    }
    if ((pw = getpwnam (username)) == 0) {
      fprintf (stderr, "change_user_group: can't find the user %s to switch to\n", username);
      return -1;
    }
    gid_t gid = pw->pw_gid;
    if (setgroups (1, &gid) < 0) {
      fprintf (stderr, "change_user_group: failed to clear supplementary groups list: %m\n");
      return -1;
    }

    if (groupname) {
      struct group *g = getgrnam (groupname);
      if (g == NULL) {
        fprintf (stderr, "change_user_group: can't find the group %s to switch to\n", groupname);
        return -1;
      }
      gid = g->gr_gid;
    }

    if (setgid (gid) < 0) {
      fprintf (stderr, "change_user_group: setgid (%d) failed. %m\n", (int) gid);
      return -1;
    }

    if (setuid (pw->pw_uid) < 0) {
      fprintf (stderr, "change_user_group: failed to assume identity of user %s\n", username);
      return -1;
    } else {
      pw = getpwuid(getuid());
      setenv("USER", pw->pw_name, 1);
      setenv("HOME", pw->pw_dir, 1);
      setenv("SHELL", pw->pw_shell, 1);
    }
  }
  return 0;
}