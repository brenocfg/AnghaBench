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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */

__attribute__((used)) static void
setst (mode_t bits, char *chars)
{
#ifdef S_ISUID
  if (bits & S_ISUID)
    {
      if (chars[3] != 'x')
	/* Set-uid, but not executable by owner.  */
	chars[3] = 'S';
      else
	chars[3] = 's';
    }
#endif
#ifdef S_ISGID
  if (bits & S_ISGID)
    {
      if (chars[6] != 'x')
	/* Set-gid, but not executable by group.  */
	chars[6] = 'S';
      else
	chars[6] = 's';
    }
#endif
#ifdef S_ISVTX
  if (bits & S_ISVTX)
    {
      if (chars[9] != 'x')
	/* Sticky, but not executable by others.  */
	chars[9] = 'T';
      else
	chars[9] = 't';
    }
#endif
}