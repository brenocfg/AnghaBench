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
typedef  int /*<<< orphan*/  CdIo_t ;

/* Variables and functions */
 int cdio_get_num_tracks (int /*<<< orphan*/  const*) ; 
 unsigned int cdio_get_track_lba (int /*<<< orphan*/  const*,int) ; 

unsigned int
cdio_get_track_sec_count(const CdIo_t *p_cdio, track_t u_track)
{
  const track_t u_tracks = cdio_get_num_tracks(p_cdio);

  if (u_track >=1 && u_track <= u_tracks)
    return ( cdio_get_track_lba(p_cdio, u_track+1)
             - cdio_get_track_lba(p_cdio, u_track) );
  return 0;
}