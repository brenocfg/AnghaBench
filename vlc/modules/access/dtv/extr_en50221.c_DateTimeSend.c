#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_gmtoff; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_last; } ;
typedef  TYPE_2__ date_time_t ;
struct TYPE_8__ {TYPE_1__* p_sessions; } ;
typedef  TYPE_3__ cam_t ;
struct TYPE_6__ {scalar_t__ p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOT_DATE_TIME ; 
 int /*<<< orphan*/  APDUSend (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DEC2BCD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWBE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static void DateTimeSend( cam_t * p_cam, int i_session_id )
{
    date_time_t *p_date =
        (date_time_t *)p_cam->p_sessions[i_session_id - 1].p_sys;

    time_t t = time(NULL);
    struct tm tm_gmt;
    struct tm tm_loc;

    if ( gmtime_r(&t, &tm_gmt) && localtime_r(&t, &tm_loc) )
    {
        int Y = tm_gmt.tm_year;
        int M = tm_gmt.tm_mon + 1;
        int D = tm_gmt.tm_mday;
        int L = (M == 1 || M == 2) ? 1 : 0;
        int MJD = 14956 + D + (int)((Y - L) * 365.25)
                    + (int)((M + 1 + L * 12) * 30.6001);
        uint8_t p_response[7];

#define DEC2BCD(d) (((d / 10) << 4) + (d % 10))

        SetWBE( &p_response[0], MJD );
        p_response[2] = DEC2BCD(tm_gmt.tm_hour);
        p_response[3] = DEC2BCD(tm_gmt.tm_min);
        p_response[4] = DEC2BCD(tm_gmt.tm_sec);
        SetWBE( &p_response[5], tm_loc.tm_gmtoff / 60 );

        APDUSend( p_cam, i_session_id, AOT_DATE_TIME, p_response, 7 );

        p_date->i_last = vlc_tick_now();
    }
}