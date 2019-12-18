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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  issetugid () ; 
 int /*<<< orphan*/  uu_warn_internal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uu_die_internal(int status, const char *format, va_list alist)
{
	uu_warn_internal(errno, format, alist);
#ifdef DEBUG
	{
		char *cp;

		if (!issetugid()) {
			cp = getenv("UU_DIE_ABORTS");
			if (cp != NULL && *cp != '\0')
				abort();
		}
	}
#endif
	exit(status);
}