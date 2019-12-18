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
typedef  scalar_t__ uid_t ;
struct passwd {scalar_t__ pw_uid; char* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  endpwent () ; 
 char* getenv (char*) ; 
 struct passwd* getpwent () ; 
 scalar_t__ getuid () ; 
 char* home_directory ; 
 int /*<<< orphan*/  setpwent () ; 
 scalar_t__ str_empty (char*) ; 
 char* tstrdup (char*) ; 

char *get_home_directory (void) {
  if (home_directory) { return home_directory; }
  home_directory = getenv("TELEGRAM_HOME");
  if (!str_empty (home_directory)) { return home_directory = tstrdup (home_directory); }
  home_directory = getenv("HOME");
  if (!str_empty (home_directory)) { return home_directory = tstrdup (home_directory); }
  struct passwd *current_passwd;
  uid_t user_id;
  setpwent ();
  user_id = getuid ();
  while ((current_passwd = getpwent ())) {
    if (current_passwd->pw_uid == user_id) {
      home_directory = tstrdup (current_passwd->pw_dir);
      break;
    }
  }
  endpwent ();
  if (str_empty (home_directory)) { home_directory = tstrdup ("."); }
  return home_directory;
}