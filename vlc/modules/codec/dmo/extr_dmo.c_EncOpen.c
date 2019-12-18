#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {int i_rate; } ;
struct TYPE_19__ {scalar_t__ i_cat; TYPE_2__ audio; } ;
struct TYPE_20__ {scalar_t__ i_cat; } ;
struct TYPE_23__ {TYPE_14__ fmt_out; TYPE_1__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ encoder_t ;
struct TYPE_24__ {int /*<<< orphan*/  end_date; int /*<<< orphan*/  i_min_output; TYPE_6__* p_dmo; int /*<<< orphan*/ * hmsdmo_dll; } ;
typedef  TYPE_5__ encoder_sys_t ;
struct TYPE_25__ {TYPE_3__* vt; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* Release ) (int /*<<< orphan*/ *) ;scalar_t__ (* GetOutputSizeInfo ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* GetInputSizeInfo ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_6__ IMediaObject ;
typedef  int /*<<< orphan*/ * HINSTANCE ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/  CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ EncoderSetAudioType (TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ EncoderSetVideoType (TYPE_4__*,TYPE_6__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 scalar_t__ LoadDMO (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_6__**,TYPE_14__*,int) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int EncOpen( vlc_object_t *p_this )
{
    encoder_t *p_enc = (encoder_t*)p_this;
    encoder_sys_t *p_sys = NULL;
    IMediaObject *p_dmo = NULL;
    HINSTANCE hmsdmo_dll = NULL;

    /* Initialize OLE/COM */
    if( FAILED(CoInitializeEx( NULL, COINIT_MULTITHREADED )) )
        vlc_assert_unreachable();

    if( LoadDMO( p_this, &hmsdmo_dll, &p_dmo, &p_enc->fmt_out, true )
        != VLC_SUCCESS )
    {
        hmsdmo_dll = 0;
        p_dmo = 0;
        goto error;
    }

    if( p_enc->fmt_in.i_cat == VIDEO_ES )
    {
        if( EncoderSetVideoType( p_enc, p_dmo ) != VLC_SUCCESS ) goto error;
    }
    else
    {
        if( EncoderSetAudioType( p_enc, p_dmo ) != VLC_SUCCESS ) goto error;
    }

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_enc->p_sys = p_sys = malloc(sizeof(*p_sys)) ) == NULL )
    {
        goto error;
    }

    p_sys->hmsdmo_dll = hmsdmo_dll;
    p_sys->p_dmo = p_dmo;

    /* Find out some properties of the inputput */
    {
        uint32_t i_size, i_align, dum;

        if( p_dmo->vt->GetInputSizeInfo( p_dmo, 0, &i_size, &i_align, &dum ) )
            msg_Err( p_enc, "GetInputSizeInfo() failed" );
        else
            msg_Dbg( p_enc, "GetInputSizeInfo(): bytes %i, align %i, %i",
                     i_size, i_align, dum );
    }

    /* Find out some properties of the output */
    {
        uint32_t i_size, i_align;

        p_sys->i_min_output = 0;
        if( p_dmo->vt->GetOutputSizeInfo( p_dmo, 0, &i_size, &i_align ) )
        {
            msg_Err( p_enc, "GetOutputSizeInfo() failed" );
            goto error;
        }
        else
        {
            msg_Dbg( p_enc, "GetOutputSizeInfo(): bytes %i, align %i",
                     i_size, i_align );
            p_sys->i_min_output = i_size;
        }
    }

    /* Set output properties */
    p_enc->fmt_out.i_cat = p_enc->fmt_in.i_cat;
    if( p_enc->fmt_out.i_cat == AUDIO_ES )
        date_Init( &p_sys->end_date, p_enc->fmt_out.audio.i_rate, 1 );
    else
        date_Init( &p_sys->end_date, 25 /* FIXME */, 1 );

    return VLC_SUCCESS;

 error:

    if( p_dmo ) p_dmo->vt->Release( (IUnknown *)p_dmo );
    if( hmsdmo_dll ) FreeLibrary( hmsdmo_dll );

    /* Uninitialize OLE/COM */
    CoUninitialize();

    free( p_sys );

    return VLC_EGENERIC;
}