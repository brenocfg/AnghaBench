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
 int GetTextSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 float M_PI ; 
 int /*<<< orphan*/  SetTextAlpha (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SetTextSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sin (float) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  usleep (int) ; 

void TextTest( FILE *p_cmd, FILE *p_res, int i_overlay ) {
    printf( "Sweeping (text) alpha..." );
    for( int i_alpha = 0xFF; i_alpha >= -0xFF ; i_alpha -= 8 ) {
        SetTextAlpha( p_cmd, p_res, i_overlay, abs( i_alpha ) );
        usleep( 20000 );
    }
    SetTextAlpha( p_cmd, p_res, i_overlay, 255 );
    printf( " done\n" );

    printf( "Sweeping colors..." );
    for( int i_red = 0xFF; i_red >= 0x00 ; i_red -= 8 ) {
        SetTextColor( p_cmd, p_res, i_overlay, i_red, 0xFF, 0xFF );
        usleep( 20000 );
    }
    for( int i_green = 0xFF; i_green >= 0x00 ; i_green -= 8 ) {
        SetTextColor( p_cmd, p_res, i_overlay, 0x00, i_green, 0xFF );
        usleep( 20000 );
    }
    for( int i_blue = 0xFF; i_blue >= 0x00 ; i_blue -= 8 ) {
        SetTextColor( p_cmd, p_res, i_overlay, 0x00, 0x00, i_blue );
        usleep( 20000 );
    }
    SetTextColor( p_cmd, p_res, i_overlay, 0x00, 0x00, 0x00 );
    printf( " done\n" );

    printf( "Getting size..." );
    int i_basesize = GetTextSize( p_cmd, p_res, i_overlay );
    printf( " done. Size is %d\n", i_basesize );

    printf( "Sweeping size..." );
    for( float f_theta = 0; f_theta <= M_PI ; f_theta += M_PI / 128.0 ) {
        SetTextSize( p_cmd, p_res, i_overlay,
                     i_basesize * ( 1 + 3 * sin( f_theta ) ) );
        usleep( 20000 );
    }
    SetTextSize( p_cmd, p_res, i_overlay, i_basesize );
    printf( " done\n" );

    sleep( 5 );
}