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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stime_t ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_SCALE_NZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPESTimestamp (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static vlc_tick_t get_pts( const uint8_t *buf )
{
    stime_t i_pts = GetPESTimestamp( buf );
    return FROM_SCALE_NZ(i_pts); /* convert PTS (90Khz clock) to microseconds */
}