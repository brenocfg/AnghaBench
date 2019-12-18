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
typedef  int /*<<< orphan*/  msf_t ;
typedef  scalar_t__ lba_t ;
struct TYPE_4__ {int (* get_track_msf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* get_track_lba ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  env; TYPE_1__ op; } ;
typedef  TYPE_2__ CdIo_t ;

/* Variables and functions */
 scalar_t__ CDIO_INVALID_LBA ; 
 int /*<<< orphan*/  cdio_lba_to_msf (scalar_t__,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
cdio_get_track_msf(const CdIo_t *p_cdio, track_t u_track, /*out*/ msf_t *msf)
{
  if (!p_cdio) return false;

  if (p_cdio->op.get_track_msf) {
    return p_cdio->op.get_track_msf (p_cdio->env, u_track, msf);
  } else if (p_cdio->op.get_track_lba) {
    lba_t lba = p_cdio->op.get_track_lba (p_cdio->env, u_track);
    if (lba  == CDIO_INVALID_LBA) return false;
    cdio_lba_to_msf(lba, msf);
    return true;
  } else {
    return false;
  }
}