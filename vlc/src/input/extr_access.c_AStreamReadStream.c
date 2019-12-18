#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vlc_access_stream_private {scalar_t__ input; } ;
struct input_stats {int /*<<< orphan*/  input_bitrate; } ;
struct TYPE_7__ {struct TYPE_7__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int ssize_t ;
struct TYPE_8__ {struct input_stats* stats; } ;

/* Variables and functions */
 TYPE_5__* input_priv (scalar_t__) ; 
 int /*<<< orphan*/  input_rate_Add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlc_killed () ; 
 scalar_t__ vlc_stream_Eof (TYPE_1__*) ; 
 struct vlc_access_stream_private* vlc_stream_Private (TYPE_1__*) ; 
 int vlc_stream_ReadPartial (TYPE_1__*,void*,size_t) ; 

__attribute__((used)) static ssize_t AStreamReadStream(stream_t *s, void *buf, size_t len)
{
    stream_t *access = s->p_sys;

    if (vlc_stream_Eof(access))
        return 0;
    if (vlc_killed())
        return -1;

    ssize_t val = vlc_stream_ReadPartial(access, buf, len);

    if (val > 0)
    {
        struct vlc_access_stream_private *priv = vlc_stream_Private(s);
        struct input_stats *stats =
            priv->input ? input_priv(priv->input)->stats : NULL;
        if (stats != NULL)
            input_rate_Add(&stats->input_bitrate, val);
    }

    return val;
}