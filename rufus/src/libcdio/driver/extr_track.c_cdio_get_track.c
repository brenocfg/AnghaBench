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
typedef  int track_t ;
typedef  scalar_t__ lsn_t ;
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 int CDIO_CDROM_LEADOUT_TRACK ; 
 int CDIO_INVALID_TRACK ; 
 int cdio_get_first_track_num (int /*<<< orphan*/  const*) ; 
 int cdio_get_last_track_num (int /*<<< orphan*/  const*) ; 
 scalar_t__ cdio_get_track_lsn (int /*<<< orphan*/  const*,int const) ; 

track_t
cdio_get_track(const CdIo_t *p_cdio, lsn_t lsn)
{
  if (!p_cdio) return CDIO_INVALID_TRACK;

  {
    track_t i_low_track   = cdio_get_first_track_num(p_cdio);
    track_t i_high_track  = cdio_get_last_track_num(p_cdio)+1;
    track_t i_lead_track  = i_high_track;

    if (CDIO_INVALID_TRACK == i_low_track
	|| CDIO_INVALID_TRACK == i_high_track ) return CDIO_INVALID_TRACK;

    if (lsn < cdio_get_track_lsn(p_cdio, i_low_track))
      return 0; /* We're in the pre-gap of first track */

    if (lsn > cdio_get_track_lsn(p_cdio, CDIO_CDROM_LEADOUT_TRACK))
      return CDIO_INVALID_TRACK; /* We're beyond the end. */

    do {
      const track_t i_mid = (i_low_track + i_high_track) / 2;
      const lsn_t i_mid_lsn = cdio_get_track_lsn(p_cdio, i_mid);
      if (lsn <= i_mid_lsn) i_high_track = i_mid - 1;
      if (lsn >= i_mid_lsn) i_low_track  = i_mid + 1;
    } while ( i_low_track <= i_high_track );

    if (i_low_track > i_high_track + 1) {
	i_high_track++;
    }
    if (i_high_track == i_lead_track ) {
	return CDIO_CDROM_LEADOUT_TRACK;
    } else {
	return i_high_track;
    }
  }
}