#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  track_t ;
typedef  int /*<<< orphan*/  track_flag_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_track_copy_permit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_TRACK_FLAG_UNKNOWN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

track_flag_t
cdio_get_track_copy_permit(const CdIo_t *p_cdio, track_t u_track)
{
  if (p_cdio->op.get_track_copy_permit) {
    return p_cdio->op.get_track_copy_permit (p_cdio->env, u_track);
  } else {
    return CDIO_TRACK_FLAG_UNKNOWN;
  }
}