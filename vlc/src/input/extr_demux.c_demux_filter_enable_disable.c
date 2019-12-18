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
struct vlc_demux_private {int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_FILTER_DISABLE ; 
 int /*<<< orphan*/  DEMUX_FILTER_ENABLE ; 
 int /*<<< orphan*/  demux_Control (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_get_name (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct vlc_demux_private* vlc_stream_Private (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool demux_filter_enable_disable(demux_t *p_demux,
                                        const char *psz_demux, bool b_enable)
{
    struct vlc_demux_private *priv = vlc_stream_Private(p_demux);

    if ( psz_demux &&
        (strcmp(module_get_name(priv->module, false), psz_demux) == 0
      || strcmp(module_get_name(priv->module, true), psz_demux) == 0) )
    {
        demux_Control( p_demux,
                       b_enable ? DEMUX_FILTER_ENABLE : DEMUX_FILTER_DISABLE );
        return true;
    }
    return false;
}