#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct input_decoder_callbacks {int dummy; } ;
struct TYPE_12__ {scalar_t__ i_cat; } ;
struct TYPE_14__ {TYPE_1__ fmt_in; int /*<<< orphan*/  p_module; } ;
struct decoder_owner {int error; int /*<<< orphan*/  thread; int /*<<< orphan*/ * p_sout_input; int /*<<< orphan*/  p_sout; TYPE_3__ dec; } ;
typedef  int /*<<< orphan*/  sout_instance_t ;
typedef  int /*<<< orphan*/  input_resource_t ;
struct TYPE_13__ {scalar_t__ i_cat; int /*<<< orphan*/  i_codec; scalar_t__ b_packetized; } ;
typedef  TYPE_2__ es_format_t ;
typedef  TYPE_3__ decoder_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 struct decoder_owner* CreateDecoder (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct input_decoder_callbacks const*,void*) ; 
 int /*<<< orphan*/  DecoderThread ; 
 int /*<<< orphan*/  DecoderUnsupportedCodec (TYPE_3__*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  DeleteDecoder (TYPE_3__*) ; 
 char* N_ (char*) ; 
 scalar_t__ UNKNOWN_ES ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_THREAD_PRIORITY_AUDIO ; 
 int VLC_THREAD_PRIORITY_VIDEO ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/ * sout_InputNew (int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct decoder_owner*,int) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gettext (char const*) ; 

__attribute__((used)) static decoder_t *decoder_New( vlc_object_t *p_parent, const es_format_t *fmt,
                               vlc_clock_t *p_clock, input_resource_t *p_resource,
                               sout_instance_t *p_sout, bool thumbnailing,
                               const struct input_decoder_callbacks *cbs,
                               void *userdata)
{
    const char *psz_type = p_sout ? N_("packetizer") : N_("decoder");
    int i_priority;

    /* Create the decoder configuration structure */
    struct decoder_owner *p_owner = CreateDecoder( p_parent, fmt, p_clock, p_resource, p_sout,
                           thumbnailing, cbs, userdata );
    if( p_owner == NULL )
    {
        msg_Err( p_parent, "could not create %s", psz_type );
        vlc_dialog_display_error( p_parent, _("Streaming / Transcoding failed"),
            _("VLC could not open the %s module."), vlc_gettext( psz_type ) );
        return NULL;
    }

    decoder_t *p_dec = &p_owner->dec;
    if( !p_dec->p_module )
    {
        DecoderUnsupportedCodec( p_dec, fmt, !p_sout );

        DeleteDecoder( p_dec );
        return NULL;
    }

    assert( p_dec->fmt_in.i_cat != UNKNOWN_ES );

    if( p_dec->fmt_in.i_cat == AUDIO_ES )
        i_priority = VLC_THREAD_PRIORITY_AUDIO;
    else
        i_priority = VLC_THREAD_PRIORITY_VIDEO;

#ifdef ENABLE_SOUT
    /* Do not delay sout creation for SPU or DATA. */
    if( p_sout && fmt->b_packetized &&
        (fmt->i_cat != VIDEO_ES && fmt->i_cat != AUDIO_ES) )
    {
        p_owner->p_sout_input = sout_InputNew( p_owner->p_sout, fmt );
        if( p_owner->p_sout_input == NULL )
        {
            msg_Err( p_dec, "cannot create sout input (%4.4s)",
                     (char *)&fmt->i_codec );
            p_owner->error = true;
        }
    }
#endif

    /* Spawn the decoder thread */
    if( vlc_clone( &p_owner->thread, DecoderThread, p_owner, i_priority ) )
    {
        msg_Err( p_dec, "cannot spawn decoder thread" );
        DeleteDecoder( p_dec );
        return NULL;
    }

    return p_dec;
}