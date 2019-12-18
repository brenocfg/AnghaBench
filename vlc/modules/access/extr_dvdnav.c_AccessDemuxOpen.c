#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  dvdnav_t ;
struct TYPE_3__ {char* psz_filepath; int /*<<< orphan*/  psz_url; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int CommonOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  DVD_READ_CACHE ; 
 int /*<<< orphan*/  LocaleFree (char const*) ; 
 int ProbeDVD (char*) ; 
 char* ToLocale (char*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dvdnav_close (int /*<<< orphan*/ *) ; 
 scalar_t__ dvdnav_open (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int AccessDemuxOpen ( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t*)p_this;
    dvdnav_t *p_dvdnav = NULL;
    char *psz_file = NULL;
    const char *psz_path = NULL;
    int i_ret = VLC_EGENERIC;
    bool forced = false;

    if (p_demux->out == NULL)
        return VLC_EGENERIC;

    if( !strncasecmp(p_demux->psz_url, "dvd", 3) )
        forced = true;

    if( !p_demux->psz_filepath || !*p_demux->psz_filepath )
    {
        /* Only when selected */
        if( !forced )
            return VLC_EGENERIC;

        psz_file = var_InheritString( p_this, "dvd" );
    }
    else
        psz_file = strdup( p_demux->psz_filepath );

#if defined( _WIN32 ) || defined( __OS2__ )
    if( psz_file != NULL )
    {
        /* Remove trailing backslash, otherwise dvdnav_open will fail */
        size_t flen = strlen( psz_file );
        if( flen > 0 && psz_file[flen - 1] == '\\' )
            psz_file[flen - 1] = '\0';
    }
    else
        psz_file = strdup("");
#endif

    if( unlikely(psz_file == NULL) )
        return VLC_EGENERIC;

    /* Try some simple probing to avoid going through dvdnav_open too often */
    if( !forced && ProbeDVD( psz_file ) != VLC_SUCCESS )
        goto bailout;

    /* Open dvdnav */
    psz_path = ToLocale( psz_file );
    if( dvdnav_open( &p_dvdnav, psz_path ) != DVDNAV_STATUS_OK )
    {
        msg_Warn( p_demux, "cannot open DVD (%s)", psz_file);
        goto bailout;
    }

    i_ret = CommonOpen( p_this, p_dvdnav, !!DVD_READ_CACHE );
    if( i_ret != VLC_SUCCESS )
        dvdnav_close( p_dvdnav );

bailout:
    free( psz_file );
    if( psz_path )
        LocaleFree( psz_path );
    return i_ret;
}