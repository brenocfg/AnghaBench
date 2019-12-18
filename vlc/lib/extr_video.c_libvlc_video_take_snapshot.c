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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetVout (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

int
libvlc_video_take_snapshot( libvlc_media_player_t *p_mi, unsigned num,
                            const char *psz_filepath,
                            unsigned int i_width, unsigned int i_height )
{
    assert( psz_filepath );

    vout_thread_t *p_vout = GetVout (p_mi, num);
    if (p_vout == NULL)
        return -1;

    /* FIXME: This is not atomic. All parameters should be passed at once
     * (obviously _not_ with var_*()). Also, the libvlc object should not be
     * used for the callbacks: that breaks badly if there are concurrent
     * media players in the instance. */
    var_Create( p_vout, "snapshot-width", VLC_VAR_INTEGER );
    var_SetInteger( p_vout, "snapshot-width", i_width);
    var_Create( p_vout, "snapshot-height", VLC_VAR_INTEGER );
    var_SetInteger( p_vout, "snapshot-height", i_height );
    var_Create( p_vout, "snapshot-path", VLC_VAR_STRING );
    var_SetString( p_vout, "snapshot-path", psz_filepath );
    var_Create( p_vout, "snapshot-format", VLC_VAR_STRING );
    var_SetString( p_vout, "snapshot-format", "png" );
    var_TriggerCallback( p_vout, "video-snapshot" );
    vout_Release(p_vout);
    return 0;
}