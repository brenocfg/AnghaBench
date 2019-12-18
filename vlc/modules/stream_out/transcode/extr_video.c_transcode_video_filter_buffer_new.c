#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_5__ {TYPE_4__ video; int /*<<< orphan*/  i_codec; } ;
struct TYPE_6__ {TYPE_1__ fmt_out; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/ * picture_NewFromFormat (TYPE_4__*) ; 

__attribute__((used)) static picture_t *transcode_video_filter_buffer_new( filter_t *p_filter )
{
    p_filter->fmt_out.video.i_chroma = p_filter->fmt_out.i_codec;
    return picture_NewFromFormat( &p_filter->fmt_out.video );
}