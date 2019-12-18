#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double f_float; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_12__ {int b_out_pace_control; int i_slave; TYPE_4__* p_sout; int /*<<< orphan*/ * p_es_out; int /*<<< orphan*/ * p_resource; int /*<<< orphan*/  p_es_out_display; TYPE_6__* p_item; TYPE_3__** slave; int /*<<< orphan*/  b_preparsing; int /*<<< orphan*/  normal_time; TYPE_3__* master; int /*<<< orphan*/  rate; } ;
typedef  TYPE_2__ input_thread_private_t ;
struct TYPE_13__ {int /*<<< orphan*/  p_demux; } ;
typedef  TYPE_3__ input_source_t ;
struct TYPE_15__ {char* psz_uri; } ;
struct TYPE_14__ {scalar_t__ i_out_pace_nocontrol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUX_GET_LENGTH ; 
 int /*<<< orphan*/  ERROR_S ; 
 int /*<<< orphan*/  ES_OUT_MODE_END ; 
 int /*<<< orphan*/  INPUT_CONTROL_SET_RATE ; 
 int /*<<< orphan*/  InitPrograms (int /*<<< orphan*/ *) ; 
 scalar_t__ InitSout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitTitle (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  InputMetaUser (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InputSourceMeta (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* InputSourceNew (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LoadSlaves (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENING_S ; 
 int /*<<< orphan*/  PLAYING_S ; 
 int /*<<< orphan*/  SetSubtitlesOptions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartTitle (int /*<<< orphan*/ *) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ demux_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  es_out_ControlSetMeta (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_SetMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_ChangeState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_ControlPushHelper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * input_EsOutTimeshiftNew (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_SendEventCache (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  input_SendEventTimes (int /*<<< orphan*/ *,double,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ input_item_GetDuration (TYPE_6__*) ; 
 int /*<<< orphan*/  input_item_IsPreparsed (TYPE_6__*) ; 
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_RequestSout (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 double var_GetFloat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ var_Type (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_meta_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_object_parent (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static int Init( input_thread_t * p_input )
{
    input_thread_private_t *priv = input_priv(p_input);
    input_source_t *master;

    /* */
    input_ChangeState( p_input, OPENING_S, VLC_TICK_INVALID );
    input_SendEventCache( p_input, 0.0 );

    if( var_Type( vlc_object_parent(p_input), "meta-file" ) )
    {
        msg_Dbg( p_input, "Input is a meta file: disabling unneeded options" );
        var_SetString( p_input, "sout", "" );
        var_SetBool( p_input, "sout-all", false );
        var_SetString( p_input, "input-slave", "" );
        var_SetInteger( p_input, "input-repeat", 0 );
        var_SetString( p_input, "sub-file", "" );
        var_SetBool( p_input, "sub-autodetect-file", false );
    }

#ifdef ENABLE_SOUT
    if( InitSout( p_input ) )
        goto error;
#endif

    /* Create es out */
    priv->p_es_out = input_EsOutTimeshiftNew( p_input, priv->p_es_out_display, priv->rate );
    if( priv->p_es_out == NULL )
        goto error;

    /* */
    master = InputSourceNew( p_input, priv->p_item->psz_uri, NULL, false );
    if( master == NULL )
        goto error;
    priv->master = master;

    InitTitle( p_input, false );

    /* Load master infos */
    /* Init length */
    vlc_tick_t i_length;
    if( demux_Control( master->p_demux, DEMUX_GET_LENGTH, &i_length ) )
        i_length = VLC_TICK_INVALID;
    if( i_length == VLC_TICK_INVALID )
        i_length = input_item_GetDuration( priv->p_item );

    input_SendEventTimes( p_input, 0.0, VLC_TICK_INVALID, priv->normal_time,
                          i_length );

    if( !priv->b_preparsing )
    {
        StartTitle( p_input );
        SetSubtitlesOptions( p_input );
        LoadSlaves( p_input );
        InitPrograms( p_input );

        double f_rate = var_GetFloat( p_input, "rate" );
        if( f_rate != 0.0 && f_rate != 1.0 )
        {
            vlc_value_t val = { .f_float = f_rate };
            input_ControlPushHelper( p_input, INPUT_CONTROL_SET_RATE, &val );
        }
    }

    if( !priv->b_preparsing && priv->p_sout )
    {
        priv->b_out_pace_control = priv->p_sout->i_out_pace_nocontrol > 0;

        msg_Dbg( p_input, "starting in %ssync mode",
                 priv->b_out_pace_control ? "a" : "" );
    }

    if (!input_item_IsPreparsed(input_priv(p_input)->p_item))
    {
        vlc_meta_t *p_meta = vlc_meta_New();
        if( p_meta != NULL )
        {
            /* Get meta data from users */
            InputMetaUser( p_input, p_meta );

            /* Get meta data from master input */
            InputSourceMeta( p_input, master, p_meta );

            /* And from slave */
            for( int i = 0; i < priv->i_slave; i++ )
                InputSourceMeta( p_input, priv->slave[i], p_meta );

            es_out_ControlSetMeta( priv->p_es_out, p_meta );
            vlc_meta_Delete( p_meta );
        }
    }

    msg_Dbg( p_input, "`%s' successfully opened",
             input_priv(p_input)->p_item->psz_uri );

    /* initialization is complete */
    input_ChangeState( p_input, PLAYING_S, vlc_tick_now() );

    return VLC_SUCCESS;

error:
    input_ChangeState( p_input, ERROR_S, VLC_TICK_INVALID );

    if( input_priv(p_input)->p_es_out )
        es_out_Delete( input_priv(p_input)->p_es_out );
    es_out_SetMode( input_priv(p_input)->p_es_out_display, ES_OUT_MODE_END );
    if( input_priv(p_input)->p_resource )
    {
        if( input_priv(p_input)->p_sout )
            input_resource_RequestSout( input_priv(p_input)->p_resource,
                                         input_priv(p_input)->p_sout, NULL );
        input_resource_SetInput( input_priv(p_input)->p_resource, NULL );
        if( input_priv(p_input)->p_resource )
        {
            input_resource_Release( input_priv(p_input)->p_resource );
            input_priv(p_input)->p_resource = NULL;
        }
    }

    /* Mark them deleted */
    input_priv(p_input)->p_es_out = NULL;
    input_priv(p_input)->p_sout = NULL;

    return VLC_EGENERIC;
}