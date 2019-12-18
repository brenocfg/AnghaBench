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
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  orientation; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_5__ {TYPE_1__ video; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void debug_format( sout_stream_t *p_stream, const es_format_t *fmt )
{
    msg_Dbg( p_stream, "format now %4.4s/%4.4s %dx%d(%dx%d) ø%d",
             (const char *) &fmt->i_codec,
             (const char *) &fmt->video.i_chroma,
             fmt->video.i_visible_width, fmt->video.i_visible_height,
             fmt->video.i_width, fmt->video.i_height,
             fmt->video.orientation );
}