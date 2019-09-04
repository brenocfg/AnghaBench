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
typedef  scalar_t__ track_t ;
typedef  scalar_t__ lsn_t ;
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 scalar_t__ CDIO_INVALID_LSN ; 
 scalar_t__ cdio_get_track_lsn (int /*<<< orphan*/  const*,scalar_t__) ; 

lsn_t
cdio_get_track_last_lsn(const CdIo_t *p_cdio, track_t u_track)
{
  lsn_t lsn = cdio_get_track_lsn(p_cdio, u_track+1);

  if (CDIO_INVALID_LSN == lsn) return CDIO_INVALID_LSN;
  /* Safe, we've always the leadout. */
  return lsn - 1;
}