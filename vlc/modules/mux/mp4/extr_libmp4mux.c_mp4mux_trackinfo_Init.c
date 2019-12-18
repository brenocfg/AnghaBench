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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {unsigned int i_track_id; int /*<<< orphan*/  fmt; int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mp4mux_trackinfo_Init(mp4mux_trackinfo_t *p_stream, unsigned i_id,
                                  uint32_t i_timescale)
{
    memset(p_stream, 0, sizeof(*p_stream));
    p_stream->i_track_id = i_id;

    p_stream->i_timescale   = i_timescale;
    es_format_Init(&p_stream->fmt, 0, 0);

    return true;
}