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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  scalar_t__ uint8_t ;
struct aom_image {int fmt; scalar_t__ tc; scalar_t__ bit_depth; } ;
struct TYPE_3__ {int i_chroma_id; scalar_t__ i_bitdepth; scalar_t__ i_needs_hack; int /*<<< orphan*/  i_chroma; } ;

/* Variables and functions */
 scalar_t__ AOM_CICP_TC_SRGB ; 
 int AOM_IMG_FMT_I444 ; 
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* chroma_table ; 

__attribute__((used)) static vlc_fourcc_t FindVlcChroma( struct aom_image *img )
{
    uint8_t hack = (img->fmt & AOM_IMG_FMT_I444) && (img->tc == AOM_CICP_TC_SRGB);

    for( unsigned int i = 0; i < ARRAY_SIZE(chroma_table); i++ )
        if( chroma_table[i].i_chroma_id == img->fmt &&
            chroma_table[i].i_bitdepth == img->bit_depth &&
            chroma_table[i].i_needs_hack == hack )
            return chroma_table[i].i_chroma;

    return 0;
}