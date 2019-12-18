#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {unsigned int i_track_id; int /*<<< orphan*/  fmt; int /*<<< orphan*/  i_timescale; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;
struct TYPE_15__ {int /*<<< orphan*/  tracks; } ;
typedef  TYPE_2__ mp4mux_handle_t ;
struct TYPE_16__ {int /*<<< orphan*/  i_codec; int /*<<< orphan*/  i_cat; } ;
typedef  TYPE_3__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  mp4mux_AddExtraBrandForFormat (TYPE_2__*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  mp4mux_trackinfo_Init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_array_append (int /*<<< orphan*/ *,TYPE_1__*) ; 

mp4mux_trackinfo_t * mp4mux_track_Add(mp4mux_handle_t *h, unsigned id,
                                      const es_format_t *fmt, uint32_t timescale)
{
    if(unlikely(id == 0))
        return NULL;
    mp4mux_trackinfo_t *t = malloc(sizeof(*t));
    if(!t || !mp4mux_trackinfo_Init(t, 0, 0))
    {
        free(t);
        return NULL;
    }
    t->i_track_id = id;
    t->i_timescale = timescale;
    es_format_Init(&t->fmt, fmt->i_cat, fmt->i_codec);
    es_format_Copy(&t->fmt, fmt);
    vlc_array_append(&h->tracks, t);
    mp4mux_AddExtraBrandForFormat(h, fmt);
    return t;
}