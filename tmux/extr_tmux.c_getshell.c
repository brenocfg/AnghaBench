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
struct passwd {char const* pw_shell; } ;

/* Variables and functions */
 char const* _PATH_BSHELL ; 
 scalar_t__ checkshell (char const*) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 

__attribute__((used)) static const char *
getshell(void)
{
	struct passwd	*pw;
	const char	*shell;

	shell = getenv("SHELL");
	if (checkshell(shell))
		return (shell);

	pw = getpwuid(getuid());
	if (pw != NULL && checkshell(pw->pw_shell))
		return (pw->pw_shell);

	return (_PATH_BSHELL);
}