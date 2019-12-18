#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sensor; int /*<<< orphan*/  unimotion_hw; int /*<<< orphan*/  i_calibrate; } ;
typedef  TYPE_1__ motion_sensors_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  AMS_SENSOR 131 
#define  APPLESMC_SENSOR 130 
#define  HDAPS_SENSOR 129 
#define  UNIMOTION_SENSOR 128 
 int asin (double) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*,...) ; 
 int /*<<< orphan*/  read_sms_raw (int /*<<< orphan*/ ,int*,int*,int*) ; 
 double sqrt (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int GetOrientation( motion_sensors_t *motion )
{
    FILE *f;
    int i_x = 0, i_y = 0, i_z = 0;
    int i_ret;

    switch( motion->sensor )
    {
    case HDAPS_SENSOR:
        f = fopen( "/sys/devices/platform/hdaps/position", "re" );
        if( !f )
        {
            return 0;
        }

        i_ret = fscanf( f, "(%d,%d)", &i_x, &i_y );
        fclose( f );

        if( i_ret < 2 )
            return 0;
        else
            return ( i_x - motion->i_calibrate ) * 10;

    case AMS_SENSOR:
        f = fopen( "/sys/devices/ams/x", "re" );
        if( !f )
        {
            return 0;
        }

        i_ret = fscanf( f, "%d", &i_x);
        fclose( f );

        if( i_ret < 1 )
            return 0;
        else
            return - i_x * 30; /* FIXME: arbitrary */

    case APPLESMC_SENSOR:
        f = fopen( "/sys/devices/platform/applesmc.768/position", "re" );
        if( !f )
        {
            return 0;
        }

        i_ret = fscanf( f, "(%d,%d,%d)", &i_x, &i_y, &i_z );
        fclose( f );

        if( i_ret < 3 )
            return 0;
        else
            return ( i_x - motion->i_calibrate ) * 10;

#ifdef HAVE_MACOS_UNIMOTION
    case UNIMOTION_SENSOR:
        if( read_sms_raw( motion->unimotion_hw, &i_x, &i_y, &i_z ) )
        {
            double d_norm = sqrt( i_x*i_x+i_z*i_z );
            if( d_norm < 100 )
                return 0;
            double d_x = i_x / d_norm;
            if( i_z > 0 )
                return -asin(d_x)*3600/3.141;
            else
                return 3600 + asin(d_x)*3600/3.141;
        }
        else
            return 0;
#endif
    default:
        vlc_assert_unreachable();
    }
}