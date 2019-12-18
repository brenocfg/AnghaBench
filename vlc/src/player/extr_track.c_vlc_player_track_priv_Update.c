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
struct vlc_player_track {char* name; int /*<<< orphan*/  fmt; } ;
struct vlc_player_track_priv {struct vlc_player_track t; } ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 

int
vlc_player_track_priv_Update(struct vlc_player_track_priv *trackpriv,
                             const char *name, const es_format_t *fmt)
{
    struct vlc_player_track *track = &trackpriv->t;

    if (strcmp(name, track->name) != 0)
    {
        char *dup = strdup(name);
        if (!dup)
            return VLC_ENOMEM;
        free((char *)track->name);
        track->name = dup;
    }

    es_format_t fmtdup;
    int ret = es_format_Copy(&fmtdup, fmt);
    if (ret != VLC_SUCCESS)
        return ret;

    es_format_Clean(&track->fmt);
    track->fmt = fmtdup;
    return VLC_SUCCESS;
}