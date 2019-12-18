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
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCTG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDOOR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISMPC (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISNWK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISOFD (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISOFL (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char
ftypelet (mode_t bits)
{
#ifdef S_ISBLK
  if (S_ISBLK (bits))
    return 'b';
#endif
  if (S_ISCHR (bits))
    return 'c';
  if (S_ISDIR (bits))
    return 'd';
  if (S_ISREG (bits))
    return '-';
#ifdef S_ISFIFO
  if (S_ISFIFO (bits))
    return 'p';
#endif
#ifdef S_ISLNK
  if (S_ISLNK (bits))
    return 'l';
#endif
#ifdef S_ISSOCK
  if (S_ISSOCK (bits))
    return 's';
#endif
#ifdef S_ISMPC
  if (S_ISMPC (bits))
    return 'm';
#endif
#ifdef S_ISNWK
  if (S_ISNWK (bits))
    return 'n';
#endif
#ifdef S_ISDOOR
  if (S_ISDOOR (bits))
    return 'D';
#endif
#ifdef S_ISCTG
  if (S_ISCTG (bits))
    return 'C';
#endif

  /* The following two tests are for Cray DMF (Data Migration
     Facility), which is a HSM file system.  A migrated file has a
     `st_dm_mode' that is different from the normal `st_mode', so any
     tests for migrated files should use the former.  */

#ifdef S_ISOFD
  if (S_ISOFD (bits))
    /* off line, with data  */
    return 'M';
#endif
#ifdef S_ISOFL
  /* off line, with no data  */
  if (S_ISOFL (bits))
    return 'M';
#endif
  return '?';
}