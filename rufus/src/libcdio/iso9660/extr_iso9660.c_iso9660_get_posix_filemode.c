#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_5__ {int /*<<< orphan*/  attributes; } ;
struct TYPE_7__ {scalar_t__ b3_rock; } ;
struct TYPE_6__ {TYPE_1__ xa; scalar_t__ b_xa; TYPE_3__ rr; } ;
typedef  TYPE_2__ iso9660_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  iso9660_get_posix_filemode_from_rock (TYPE_3__*) ; 
 int /*<<< orphan*/  iso9660_get_posix_filemode_from_xa (int /*<<< orphan*/ ) ; 
 scalar_t__ yep ; 

mode_t
iso9660_get_posix_filemode(const iso9660_stat_t *p_iso_dirent)
{
  mode_t mode = 0;

#ifdef HAVE_ROCK
  if (yep == p_iso_dirent->rr.b3_rock) {
      return iso9660_get_posix_filemode_from_rock(&p_iso_dirent->rr);
  } else
#endif
  if (p_iso_dirent->b_xa) {
    return iso9660_get_posix_filemode_from_xa(p_iso_dirent->xa.attributes);
  }
  return mode;
}