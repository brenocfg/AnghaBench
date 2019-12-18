#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int orientation; } ;
struct TYPE_5__ {scalar_t__ i_cat; TYPE_1__ video; } ;
typedef  TYPE_2__ es_format_t ;
typedef  enum video_orientation_t { ____Placeholder_video_orientation_t } video_orientation_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATAN (int,int) ; 
 int ORIENT_NORMAL ; 
#define  ORIENT_ROTATED_180 130 
#define  ORIENT_ROTATED_270 129 
#define  ORIENT_ROTATED_90 128 
 scalar_t__ VIDEO_ES ; 

__attribute__((used)) static void matrix_apply_rotation(es_format_t *fmt, uint32_t mvhd_matrix[9])
{
    enum video_orientation_t orientation = ORIENT_NORMAL;
    if (fmt->i_cat == VIDEO_ES)
        orientation = fmt->video.orientation;

#define ATAN(a, b) \
    do { \
        mvhd_matrix[1] = ((uint32_t)(a)) << 16; \
        mvhd_matrix[0] = ((uint32_t)(b)) << 16; \
    } while(0)

    switch (orientation) {
    case ORIENT_ROTATED_90:  ATAN( 1,  0); break;
    case ORIENT_ROTATED_180: ATAN( 0, -1); break;
    case ORIENT_ROTATED_270: ATAN(-1,  0); break;
    default:                 ATAN( 0,  1); break;
    }

    mvhd_matrix[3] = mvhd_matrix[0] ? 0 : 0x10000;
    mvhd_matrix[4] = mvhd_matrix[1] ? 0 : 0x10000;
}