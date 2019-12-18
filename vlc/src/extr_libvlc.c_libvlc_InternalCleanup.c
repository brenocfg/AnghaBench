#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ p_media_library; scalar_t__ main_playlist; int /*<<< orphan*/ * parser; scalar_t__ p_vlm; scalar_t__ media_source_provider; scalar_t__ p_thumbnailer; } ;
typedef  TYPE_2__ libvlc_priv_t ;
struct TYPE_16__ {int /*<<< orphan*/  logger; } ;
struct TYPE_18__ {TYPE_1__ obj; } ;
typedef  TYPE_3__ libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  config_AutoSaveConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_preparser_Deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_preparser_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intf_DestroyAll (TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_InternalActionsClean (TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_InternalDialogClean (TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_InternalKeystoreClean (TYPE_3__*) ; 
 int /*<<< orphan*/  libvlc_MlRelease (scalar_t__) ; 
 TYPE_2__* libvlc_priv (TYPE_3__*) ; 
 int /*<<< orphan*/  module_EndBank (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_End () ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  var_InheritBool (TYPE_3__*,char*) ; 
 char* var_InheritString (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  vlc_LogDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_media_source_provider_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_thumbnailer_Release (scalar_t__) ; 
 int /*<<< orphan*/  vlm_Delete (scalar_t__) ; 

void libvlc_InternalCleanup( libvlc_int_t *p_libvlc )
{
    libvlc_priv_t *priv = libvlc_priv (p_libvlc);

    if (priv->parser != NULL)
        input_preparser_Deactivate(priv->parser);

    /* Ask the interfaces to stop and destroy them */
    msg_Dbg( p_libvlc, "removing all interfaces" );
    intf_DestroyAll( p_libvlc );

    if ( priv->p_thumbnailer )
        vlc_thumbnailer_Release( priv->p_thumbnailer );

    if( priv->media_source_provider )
        vlc_media_source_provider_Delete( priv->media_source_provider );

    libvlc_InternalDialogClean( p_libvlc );
    libvlc_InternalKeystoreClean( p_libvlc );

#ifdef ENABLE_VLM
    /* Destroy VLM if created in libvlc_InternalInit */
    if( priv->p_vlm )
    {
        vlm_Delete( priv->p_vlm );
    }
#endif

#if !defined( _WIN32 ) && !defined( __OS2__ )
    char *pidfile = var_InheritString( p_libvlc, "pidfile" );
    if( pidfile != NULL )
    {
        msg_Dbg( p_libvlc, "removing PID file %s", pidfile );
        if( unlink( pidfile ) )
            msg_Warn( p_libvlc, "cannot remove PID file %s: %s",
                      pidfile, vlc_strerror_c(errno) );
        free( pidfile );
    }
#endif

    if (priv->parser != NULL)
        input_preparser_Delete(priv->parser);

    if (priv->main_playlist)
        vlc_playlist_Delete(priv->main_playlist);

    if ( priv->p_media_library )
        libvlc_MlRelease( priv->p_media_library );

    libvlc_InternalActionsClean( p_libvlc );

    /* Save the configuration */
    if( !var_InheritBool( p_libvlc, "ignore-config" ) )
        config_AutoSaveConfigFile( VLC_OBJECT(p_libvlc) );

    vlc_LogDestroy(p_libvlc->obj.logger);
    /* Free module bank. It is refcounted, so we call this each time  */
    module_EndBank (true);
#if defined(_WIN32) || defined(__OS2__)
    system_End( );
#endif
}