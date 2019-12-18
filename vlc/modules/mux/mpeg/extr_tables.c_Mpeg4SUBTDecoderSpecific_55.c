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
typedef  int /*<<< orphan*/  bits_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  bits_write (int /*<<< orphan*/ *,int,char const) ; 

__attribute__((used)) static void Mpeg4SUBTDecoderSpecific_55( bits_buffer_t *b )
{
    bits_write( b, 8, 0x10 ); /* textFormat, 0x10 for 3GPP TS 26.245 */
    bits_write( b, 8, 0x00 ); /* flags: 1b: associated video info flag
                                        3b: reserved
                                        1b: duration flag
                                        3b: reserved */
    bits_write( b, 8, 52 );   /* remaining size */

    bits_write( b, 32, 0x00 ); /* display flags */

    bits_write( b, 8, 0x00 ); /* horizontal justification (-1: left, 0 center, 1 right) */
    bits_write( b, 8, 0x01 );  /* vertical   justification (-1: top, 0 center, 1 bottom) */

    bits_write( b, 24, 0x00 ); /* background rgb */
    bits_write( b, 8,  0xff ); /* background a */

    bits_write( b, 16,  0x00 ); /* text box top */
    bits_write( b, 16,  0x00 ); /* text box left */
    bits_write( b, 16,  0x00 ); /* text box bottom */
    bits_write( b, 16,  0x00 ); /* text box right */

    bits_write( b, 16,  0x00 ); /* start char */
    bits_write( b, 16,  0x00 ); /* end char */
    bits_write( b, 16,  0x00 ); /* default font id */


    bits_write( b, 8, 0x00 );   /* font style flags */
    bits_write( b, 8,   12 );   /* font size */

    bits_write( b, 24, 0x00 );  /* foreground rgb */
    bits_write( b,  8, 0x00 );  /* foreground a */

    bits_write( b, 24, 0x00 );
    bits_write( b,  8,   22 );  /* atom size */

    bits_write( b,  8,   'f' ); /* atom id */
    bits_write( b,  8,   't' );
    bits_write( b,  8,   'a' );
    bits_write( b,  8,   'b' );

    bits_write( b,  8,  0x00 );
    bits_write( b,  8,  0x01 ); /* entry count */

    bits_write( b, 16,  0x00 ); /* font id */
    bits_write( b,  8,     9 ); /* font name length */
    const char fontname[] = "Helvetica";
    for(int i=0; i<9; i++)
        bits_write( b,  8, fontname[i] ); /* font name */
}