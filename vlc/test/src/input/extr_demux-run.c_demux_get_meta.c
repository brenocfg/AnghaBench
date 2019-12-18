#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  input_attachment_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_GET_ATTACHMENTS ; 
 int /*<<< orphan*/  DEMUX_GET_META ; 
 int /*<<< orphan*/  demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,...) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 

__attribute__((used)) static void demux_get_meta(demux_t *demux)
{
    vlc_meta_t *p_meta = vlc_meta_New();
    if (unlikely(p_meta == NULL) )
        return;

    input_attachment_t **attachment;
    int i_attachment;

    demux_Control(demux, DEMUX_GET_META, p_meta);
    demux_Control(demux, DEMUX_GET_ATTACHMENTS, &attachment, &i_attachment);

    vlc_meta_Delete(p_meta);
}