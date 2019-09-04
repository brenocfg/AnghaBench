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
typedef  int /*<<< orphan*/  track_t ;
typedef  int /*<<< orphan*/  lsn_t ;
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_get_track_pregap_lba (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdio_lba_to_lsn (int /*<<< orphan*/ ) ; 

lsn_t
cdio_get_track_pregap_lsn(const CdIo_t *p_cdio, track_t u_track)
{
  return cdio_lba_to_lsn(cdio_get_track_pregap_lba(p_cdio, u_track));
}