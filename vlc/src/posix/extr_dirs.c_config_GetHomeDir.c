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
struct passwd {char const* pw_dir; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_GETPW_R_SIZE_MAX ; 
 char* getenv (char*) ; 
 scalar_t__ getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 int /*<<< orphan*/  getuid () ; 
 char* strdup (char const*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *config_GetHomeDir (void)
{
    /* 1/ Try $HOME  */
    const char *home = getenv ("HOME");
    if (home != NULL)
        return strdup (home);
#if defined(HAVE_GETPWUID_R)
    /* 2/ Try /etc/passwd */
    long max = sysconf (_SC_GETPW_R_SIZE_MAX);
    if (max != -1)
    {
        char buf[max];
        struct passwd pwbuf, *pw;

        if (getpwuid_r (getuid (), &pwbuf, buf, sizeof (buf), &pw) == 0
          && pw != NULL)
            return strdup (pw->pw_dir);
    }
#endif
    return NULL;
}