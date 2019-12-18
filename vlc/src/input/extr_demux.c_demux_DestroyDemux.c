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
struct vlc_demux_private {int /*<<< orphan*/  module; } ;
struct TYPE_5__ {int /*<<< orphan*/ * s; int /*<<< orphan*/  psz_name; int /*<<< orphan*/  psz_filepath; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 struct vlc_demux_private* vlc_stream_Private (TYPE_1__*) ; 

__attribute__((used)) static void demux_DestroyDemux(demux_t *demux)
{
    struct vlc_demux_private *priv = vlc_stream_Private(demux);

    module_unneed(demux, priv->module);
    free(demux->psz_filepath);
    free(demux->psz_name);

    assert(demux->s != NULL);
    vlc_stream_Delete(demux->s);
}