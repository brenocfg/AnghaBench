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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_align (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_eof (int /*<<< orphan*/ *) ; 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void dvbsub_pdata8bpp( bs_t *s, uint8_t *p, int i_width, int *pi_off )
{
    bool b_stop = false;

    while( !b_stop && !bs_eof( s ) )
    {
        int i_count = 0, i_color = 0;

        i_color = bs_read( s, 8 );
        if( i_color != 0x00 )
        {
            /* Add 1 pixel */
            i_count = 1;
        }
        else
        {
            if( bs_read( s, 1 ) == 0x00 )           // Switch1
            {
                i_count = bs_read( s, 7 );
                if( i_count == 0x00 )
                    b_stop = true;
            }
            else
            {
                i_count = bs_read( s, 7 );
                i_color = bs_read( s, 8 );
            }
        }

        if( !i_count ) continue;

        /* Sanity check */
        if( ( i_count + *pi_off ) > i_width ) break;

        if( i_count == 1 ) p[*pi_off] = i_color;
        else memset( ( p + *pi_off ), i_color, i_count );

        (*pi_off) += i_count;
    }

    bs_align( s );
}