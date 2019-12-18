#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_7__ {TYPE_2__* p_sys; int /*<<< orphan*/  psz_filepath; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_8__ {int fd; int /*<<< orphan*/  file_sizes; int /*<<< orphan*/  fps; scalar_t__ cur_seekpoint; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_SET_CALLBACKS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 char* BaseName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Control ; 
 char const DIR_SEP_CHAR ; 
 int /*<<< orphan*/  Read ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanDirectory (TYPE_1__*) ; 
 int /*<<< orphan*/  Seek ; 
 int /*<<< orphan*/  SwitchFile (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int sscanf (char const*,char*,char*,int*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritFloat (TYPE_1__*,char*) ; 
 TYPE_2__* vlc_obj_calloc (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ vlc_stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    stream_t *p_access = (stream_t*)p_this;

    if( !p_access->psz_filepath )
        return VLC_EGENERIC;

    /* Some tests can be skipped if this module was explicitly requested.
     * That way, the user can play "corrupt" recordings if necessary
     * and we can avoid false positives in the general case. */
    bool b_strict = strcmp( p_access->psz_name, "vdr" );

    /* Do a quick test based on the directory name to see if this
     * directory might contain a VDR recording. We can be reasonably
     * sure if ScanDirectory() actually finds files. */
    if( b_strict )
    {
        char psz_extension[4];
        int i_length = 0;
        const char *psz_name = BaseName( p_access->psz_filepath );
        if( sscanf( psz_name, "%*u-%*u-%*u.%*u.%*u.%*u%*[-.]%*u.%3s%n",
            psz_extension, &i_length ) != 1 || strcasecmp( psz_extension, "rec" ) ||
            ( psz_name[i_length] != DIR_SEP_CHAR && psz_name[i_length] != '\0' ) )
            return VLC_EGENERIC;
    }

    /* Only directories can be recordings */
    struct stat st;
    if( vlc_stat( p_access->psz_filepath, &st ) ||
        !S_ISDIR( st.st_mode ) )
        return VLC_EGENERIC;

    access_sys_t *p_sys = vlc_obj_calloc( p_this, 1, sizeof( *p_sys ) );

    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    p_access->p_sys = p_sys;
    p_sys->fd = -1;
    p_sys->cur_seekpoint = 0;
    p_sys->fps = var_InheritFloat( p_access, "vdr-fps" );
    ARRAY_INIT( p_sys->file_sizes );

    /* Import all files and prepare playback. */
    if( !ScanDirectory( p_access ) ||
        !SwitchFile( p_access, 0 ) )
    {
        Close( p_this );
        return VLC_EGENERIC;
    }

    ACCESS_SET_CALLBACKS( Read, NULL, Control, Seek );
    return VLC_SUCCESS;
}