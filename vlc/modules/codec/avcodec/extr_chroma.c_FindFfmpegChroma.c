#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_chroma; int i_chroma_id; } ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 TYPE_1__* chroma_table ; 

int FindFfmpegChroma( vlc_fourcc_t fourcc )
{
    for( int i = 0; chroma_table[i].i_chroma != 0; i++ )
        if( chroma_table[i].i_chroma == fourcc )
            return chroma_table[i].i_chroma_id;
    return AV_PIX_FMT_NONE;
}