#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int i_calibrate; scalar_t__ i_sum; scalar_t__ i; int /*<<< orphan*/  p_oldx; int /*<<< orphan*/  sensor; int /*<<< orphan*/  unimotion_hw; } ;
typedef  TYPE_1__ motion_sensors_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_SENSOR ; 
 int /*<<< orphan*/  APPLESMC_SENSOR ; 
 int /*<<< orphan*/  HDAPS_SENSOR ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  UNIMOTION_SENSOR ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detect_sms () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*,int*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

motion_sensors_t *motion_create( vlc_object_t *obj )
{
    FILE *f;
    int i_x = 0, i_y = 0;

    motion_sensors_t *motion = malloc( sizeof( motion_sensors_t ) );
    if( unlikely( motion == NULL ) )
    {
        return NULL;
    }

    if( access( "/sys/devices/platform/hdaps/position", R_OK ) == 0
        && ( f = fopen( "/sys/devices/platform/hdaps/calibrate", "re" ) ) )
    {
        /* IBM HDAPS support */
        motion->i_calibrate = fscanf( f, "(%d,%d)", &i_x, &i_y ) == 2 ? i_x: 0;
        fclose( f );
        motion->sensor = HDAPS_SENSOR;
        msg_Dbg( obj, "HDAPS motion detection correctly loaded" );
    }
    else if( access( "/sys/devices/ams/x", R_OK ) == 0 )
    {
        /* Apple Motion Sensor support */
        motion->sensor = AMS_SENSOR;
        msg_Dbg( obj, "AMS motion detection correctly loaded" );
    }
    else if( access( "/sys/devices/platform/applesmc.768/position", R_OK ) == 0
             && ( f = fopen( "/sys/devices/platform/applesmc.768/calibrate", "re" ) ) )
    {
        /* Apple SMC (newer macbooks) */
        /* Should be factorised with HDAPS */
        motion->i_calibrate = fscanf( f, "(%d,%d)", &i_x, &i_y ) == 2 ? i_x: 0;
        fclose( f );
        motion->sensor = APPLESMC_SENSOR;
        msg_Dbg( obj, "Apple SMC motion detection correctly loaded" );
    }
#ifdef HAVE_MACOS_UNIMOTION
    else if( (motion->unimotion_hw = detect_sms()) )
    {
        motion->sensor = UNIMOTION_SENSOR;
        msg_Dbg( obj, "UniMotion motion detection correctly loaded" );
    }
#endif
    else
    {
        /* No motion sensor support */
        msg_Err( obj, "No motion sensor available" );
        free( motion );
        return NULL;
    }

    memset( motion->p_oldx, 0, sizeof( motion->p_oldx ) );
    motion->i = 0;
    motion->i_sum = 0;
    return motion;
}