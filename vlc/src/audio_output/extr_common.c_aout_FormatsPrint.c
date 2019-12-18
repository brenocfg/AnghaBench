#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_format; } ;
typedef  TYPE_1__ audio_sample_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_FormatPrintChannels (TYPE_1__ const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aout_FormatsPrint( vlc_object_t *obj, const char * psz_text,
                        const audio_sample_format_t * p_format1,
                        const audio_sample_format_t * p_format2 )
{
    msg_Dbg( obj, "%s '%4.4s'->'%4.4s' %u Hz->%u Hz %s->%s",
             psz_text,
             (char *)&p_format1->i_format, (char *)&p_format2->i_format,
             p_format1->i_rate, p_format2->i_rate,
             aout_FormatPrintChannels( p_format1 ),
             aout_FormatPrintChannels( p_format2 ) );
}