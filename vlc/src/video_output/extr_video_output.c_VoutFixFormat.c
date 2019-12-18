#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VoutFixFormatAR (TYPE_1__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_fourcc_GetCodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void VoutFixFormat(video_format_t *dst, const video_format_t *src)
{
    video_format_Copy(dst, src);
    dst->i_chroma = vlc_fourcc_GetCodec(VIDEO_ES, src->i_chroma);
    VoutFixFormatAR( dst );
    video_format_FixRgb(dst);
}