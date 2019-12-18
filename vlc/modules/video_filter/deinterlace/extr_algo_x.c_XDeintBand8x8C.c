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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int XDeint8x8DetectC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDeint8x8FieldC (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDeint8x8FieldEC (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDeint8x8MergeC (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XDeintNxN (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static inline void XDeintBand8x8C( uint8_t *dst, int i_dst,
                                   uint8_t *src, int i_src,
                                   const int i_mbx, int i_modx )
{
    int x;

    for( x = 0; x < i_mbx; x++ )
    {
        int s;
        if( ( s = XDeint8x8DetectC( src, i_src ) ) )
        {
            if( x == 0 || x == i_mbx - 1 )
                XDeint8x8FieldEC( dst, i_dst, src, i_src );
            else
                XDeint8x8FieldC( dst, i_dst, src, i_src );
        }
        else
        {
            XDeint8x8MergeC( dst, i_dst,
                             &src[0*i_src], 2*i_src,
                             &src[1*i_src], 2*i_src );
        }

        dst += 8;
        src += 8;
    }

    if( i_modx )
        XDeintNxN( dst, i_dst, src, i_src, i_modx, 8 );
}