#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int s_rock_offset; scalar_t__ b3_rock; } ;
struct TYPE_6__ {TYPE_1__ rr; } ;
typedef  TYPE_2__ iso9660_stat_t ;
typedef  int /*<<< orphan*/  iso9660_dir_t ;

/* Variables and functions */
 scalar_t__ nope ; 
 int parse_rock_ridge_stat_internal (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

int
parse_rock_ridge_stat(iso9660_dir_t *p_iso9660_dir,
		      /*out*/ iso9660_stat_t *p_stat)
{
  int result;

  if (!p_stat) return 0;

  result = parse_rock_ridge_stat_internal(p_iso9660_dir, p_stat, 0);
  /* if Rock-Ridge flag was reset and we didn't look for attributes
   * behind eventual XA attributes, have a look there */
  if (0xFF == p_stat->rr.s_rock_offset && nope != p_stat->rr.b3_rock) {
    result = parse_rock_ridge_stat_internal(p_iso9660_dir, p_stat, 14);
  }
  return result;
}