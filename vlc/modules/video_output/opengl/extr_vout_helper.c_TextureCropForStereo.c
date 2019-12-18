#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int multiview_mode; } ;
struct TYPE_9__ {TYPE_3__* prgm; TYPE_1__ fmt; } ;
typedef  TYPE_4__ vout_display_opengl_t ;
struct TYPE_8__ {TYPE_2__* tc; } ;
struct TYPE_7__ {int /*<<< orphan*/  tex_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetTextureCropParamsForStereo (int /*<<< orphan*/ ,float*,float*,float*,float*,float*,float*) ; 
#define  MULTIVIEW_STEREO_SBS 129 
#define  MULTIVIEW_STEREO_TB 128 

__attribute__((used)) static void TextureCropForStereo(vout_display_opengl_t *vgl,
                                 float *left, float *top,
                                 float *right, float *bottom)
{
    float stereoCoefs[2];
    float stereoOffsets[2];

    switch (vgl->fmt.multiview_mode)
    {
    case MULTIVIEW_STEREO_TB:
        // Display only the left eye.
        stereoCoefs[0] = 1; stereoCoefs[1] = 0.5;
        stereoOffsets[0] = 0; stereoOffsets[1] = 0;
        GetTextureCropParamsForStereo(vgl->prgm->tc->tex_count,
                                      stereoCoefs, stereoOffsets,
                                      left, top, right, bottom);
        break;
    case MULTIVIEW_STEREO_SBS:
        // Display only the left eye.
        stereoCoefs[0] = 0.5; stereoCoefs[1] = 1;
        stereoOffsets[0] = 0; stereoOffsets[1] = 0;
        GetTextureCropParamsForStereo(vgl->prgm->tc->tex_count,
                                      stereoCoefs, stereoOffsets,
                                      left, top, right, bottom);
        break;
    default:
        break;
    }
}