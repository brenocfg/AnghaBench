#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* th_ycbcr_buffer ;
struct TYPE_8__ {int /*<<< orphan*/  i_lines; int /*<<< orphan*/  i_visible_lines; int /*<<< orphan*/  i_pitch; int /*<<< orphan*/  i_visible_pitch; int /*<<< orphan*/  p_pixels; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  i_planes; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_7__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  data; int /*<<< orphan*/  height; } ;

/* Variables and functions */
 int __MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plane_CopyPixels (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void theora_CopyPicture( picture_t *p_pic,
                                th_ycbcr_buffer ycbcr )
{
    int i_plane, i_planes;
    /* th_img_plane
       int  width   The width of this plane.
       int  height  The height of this plane.
       int  stride  The offset in bytes between successive rows.
       unsigned char *data  A pointer to the beginning of the first row.

       Detailed Description

       A buffer for a single color plane in an uncompressed image.

       This contains the image data in a left-to-right, top-down
       format. Each row of pixels is stored contiguously in memory,
       but successive rows need not be. Use stride to compute the
       offset of the next row. The encoder accepts both positive
       stride values (top-down in memory) and negative (bottom-up in
       memory). The decoder currently always generates images with
       positive strides.

       typedef th_img_plane th_ycbcr_buffer[3]
    */

    i_planes = __MIN(p_pic->i_planes, 3);
    for( i_plane = 0; i_plane < i_planes; i_plane++ )
    {
        plane_t src;
        src.i_lines = ycbcr[i_plane].height;
        src.p_pixels = ycbcr[i_plane].data;
        src.i_pitch = ycbcr[i_plane].stride;
        src.i_visible_pitch = src.i_pitch;
        src.i_visible_lines = src.i_lines;
        plane_CopyPixels( &p_pic->p[i_plane], &src );
    }
}