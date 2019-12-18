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
typedef  int /*<<< orphan*/  input_attachment_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_5__ {int /*<<< orphan*/  attachments; int /*<<< orphan*/  i_attachments; int /*<<< orphan*/  i_cover_idx; int /*<<< orphan*/  i_cover_score; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ParseFlacPicture (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ParsePicture( demux_t *p_demux, const uint8_t *p_data, size_t i_data )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    i_data -= 4; p_data += 4;

    input_attachment_t *p_attachment = ParseFlacPicture( p_data, i_data,
        p_sys->i_attachments, &p_sys->i_cover_score, &p_sys->i_cover_idx );
    if( p_attachment == NULL )
        return;

    TAB_APPEND( p_sys->i_attachments, p_sys->attachments, p_attachment );
}