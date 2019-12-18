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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CheckResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndAtomic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int M_PI ; 
 int /*<<< orphan*/  SetAlpha (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SetPosition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  SetVisibility (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  StartAtomic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int abs (int) ; 
 double cos (float) ; 
 int /*<<< orphan*/  printf (char*) ; 
 double sin (float) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  usleep (int) ; 

void BasicTest( FILE *p_cmd, FILE *p_res, int i_overlay ) {
    printf( "Activating overlay..." );
    SetVisibility( p_cmd, p_res, i_overlay, 1 );
    printf( " done\n" );

    printf( "Sweeping alpha..." );
    for( int i_alpha = 0xFF; i_alpha >= -0xFF ; i_alpha -= 8 ) {
        SetAlpha( p_cmd, p_res, i_overlay, abs( i_alpha ) );
        usleep( 20000 );
    }
    SetAlpha( p_cmd, p_res, i_overlay, 255 );
    printf( " done\n" );

    printf( "Circle motion..." );
    for( float f_theta = 0; f_theta <= 2 * M_PI ; f_theta += M_PI / 64.0 ) {
        SetPosition( p_cmd, p_res, i_overlay,
                     (int)( - cos( f_theta ) * 100.0 + 100.0 ),
                     (int)( - sin( f_theta ) * 100.0 + 100.0 ) );
        usleep( 20000 );
    }
    SetPosition( p_cmd, p_res, i_overlay, 0, 100 );
    printf( " done\n" );

    printf( "Atomic motion..." );
    StartAtomic( p_cmd, p_res );
    SetPosition( p_cmd, NULL, i_overlay, 200, 50 );
    sleep( 1 );
    SetPosition( p_cmd, NULL, i_overlay, 0, 0 );
    EndAtomic( p_cmd, p_res );
    CheckResult( p_res );
    CheckResult( p_res );
    printf( " done\n" );

    sleep( 5 );
}