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
typedef  scalar_t__ track_t ;
struct TYPE_5__ {int (* get_track_channels ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDIO_LOG_WARN ; 
 scalar_t__ cdio_get_last_track_num (TYPE_2__ const*) ; 
 int /*<<< orphan*/  cdio_info (char*) ; 
 int /*<<< orphan*/  cdio_log (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

int
cdio_get_track_channels(const CdIo_t *p_cdio, track_t u_track)
{
  track_t u_last_track;
  if (NULL == p_cdio) {
    cdio_info("Null CdIo object passed\n");
    return -1;
  }
  u_last_track = cdio_get_last_track_num(p_cdio);
  if (u_track > u_last_track) {
     cdio_log(CDIO_LOG_WARN, "Number of tracks exceeds maximum (%d vs. %d)\n",
              u_track, u_last_track);
     return -1;
  }
  if (p_cdio->op.get_track_channels) {
    return p_cdio->op.get_track_channels (p_cdio->env, u_track);
  } else {
    return -2;
  }
}