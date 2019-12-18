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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  text_t ;
typedef  int /*<<< orphan*/  subtitle_t ;
typedef  int /*<<< orphan*/  subs_properties_t ;

/* Variables and functions */
 int ParseSubRipSubViewer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VLC_UNUSED (size_t) ; 
 int /*<<< orphan*/  subtitle_ParseSubViewerTiming ; 

__attribute__((used)) static int  ParseSubViewer( vlc_object_t *p_obj, subs_properties_t *p_props,
                            text_t *txt, subtitle_t *p_subtitle,
                            size_t i_idx )
{
    VLC_UNUSED( i_idx );

    return ParseSubRipSubViewer( p_obj, p_props, txt, p_subtitle,
                                 &subtitle_ParseSubViewerTiming,
                                 true );
}