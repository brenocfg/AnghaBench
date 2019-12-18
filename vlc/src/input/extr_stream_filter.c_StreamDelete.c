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
struct vlc_stream_filter_private {int /*<<< orphan*/  module; } ;
struct TYPE_5__ {int /*<<< orphan*/  psz_filepath; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_unneed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ ) ; 
 struct vlc_stream_filter_private* vlc_stream_Private (TYPE_1__*) ; 

__attribute__((used)) static void StreamDelete(stream_t *s)
{
    struct vlc_stream_filter_private *priv = vlc_stream_Private(s);

    module_unneed(s, priv->module);
    vlc_stream_Delete(s->s);
    free(s->psz_filepath);
}