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
struct TYPE_4__ {int b_packetized; } ;
typedef  TYPE_1__ es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_MPGV ; 
 void* codec_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *mpv_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, VIDEO_ES, VLC_CODEC_MPGV);
    fmt.b_packetized = false;
    return codec_init (demux, &fmt);
}