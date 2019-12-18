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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int /*<<< orphan*/  pp_title_seekpoints; int /*<<< orphan*/  i_title_seekpoints; int /*<<< orphan*/  i_cover_idx; int /*<<< orphan*/  i_cover_score; int /*<<< orphan*/  attachments; int /*<<< orphan*/  i_attachments; int /*<<< orphan*/  p_meta; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  vorbis_ParseComment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ParseComment( demux_t *p_demux, const uint8_t *p_data, size_t i_data )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( i_data < 4 )
        return;

    vorbis_ParseComment( NULL, &p_sys->p_meta, &p_data[4], i_data - 4,
        &p_sys->i_attachments, &p_sys->attachments,
        &p_sys->i_cover_score, &p_sys->i_cover_idx,
        &p_sys->i_title_seekpoints, &p_sys->pp_title_seekpoints, NULL, NULL );
}