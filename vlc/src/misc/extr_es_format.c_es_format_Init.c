#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_4__ {int i_cat; int i_profile; int i_level; int i_id; int b_packetized; int /*<<< orphan*/ * p_extra; int /*<<< orphan*/  video; int /*<<< orphan*/ * p_extra_languages; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_language; int /*<<< orphan*/  i_priority; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_PRIORITY_SELECTABLE_MIN ; 
 int VIDEO_ES ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void es_format_Init( es_format_t *fmt,
                     int i_cat, vlc_fourcc_t i_codec )
{
    memset(fmt, 0, sizeof (*fmt));
    fmt->i_cat                  = i_cat;
    fmt->i_codec                = i_codec;
    fmt->i_profile              = -1;
    fmt->i_level                = -1;
    fmt->i_id                   = -1;
    fmt->i_priority             = ES_PRIORITY_SELECTABLE_MIN;
    fmt->psz_language           = NULL;
    fmt->psz_description        = NULL;
    fmt->p_extra_languages      = NULL;

    if (fmt->i_cat == VIDEO_ES)
        video_format_Init(&fmt->video, 0);

    fmt->b_packetized           = true;
    fmt->p_extra                = NULL;
}