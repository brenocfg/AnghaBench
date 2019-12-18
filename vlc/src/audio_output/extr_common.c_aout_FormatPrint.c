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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_bytes_per_frame; int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_format; } ;
typedef  TYPE_1__ audio_sample_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_FormatPrintChannels (TYPE_1__ const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aout_FormatPrint( vlc_object_t *obj, const char *psz_text,
                       const audio_sample_format_t *p_format )
{
    msg_Dbg( obj, "%s '%4.4s' %d Hz %s frame=%u samples/%u bytes", psz_text,
             (char *)&p_format->i_format, p_format->i_rate,
             aout_FormatPrintChannels( p_format ),
             p_format->i_frame_length, p_format->i_bytes_per_frame );
}