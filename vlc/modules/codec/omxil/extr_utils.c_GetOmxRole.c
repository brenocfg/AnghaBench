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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 char const* GetOmxAudioEncRole (int /*<<< orphan*/ ) ; 
 char const* GetOmxAudioRole (int /*<<< orphan*/ ) ; 
 char const* GetOmxVideoEncRole (int /*<<< orphan*/ ) ; 
 char const* GetOmxVideoRole (int /*<<< orphan*/ ) ; 
 int VIDEO_ES ; 

const char *GetOmxRole( vlc_fourcc_t i_fourcc, enum es_format_category_e i_cat,
                        bool b_enc )
{
    if(b_enc)
        return i_cat == VIDEO_ES ?
            GetOmxVideoEncRole( i_fourcc ) : GetOmxAudioEncRole( i_fourcc );
    else
        return i_cat == VIDEO_ES ?
            GetOmxVideoRole( i_fourcc ) : GetOmxAudioRole( i_fourcc );
}