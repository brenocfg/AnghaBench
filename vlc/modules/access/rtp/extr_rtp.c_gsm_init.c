#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_rate; int /*<<< orphan*/  i_physical_channels; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHAN_CENTER ; 
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_GSM ; 
 void* codec_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *gsm_init (demux_t *demux)
{
    es_format_t fmt;

    es_format_Init (&fmt, AUDIO_ES, VLC_CODEC_GSM);
    fmt.audio.i_rate = 8000;
    fmt.audio.i_physical_channels = AOUT_CHAN_CENTER;
    return codec_init (demux, &fmt);
}