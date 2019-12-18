#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct shmid_ds {size_t shm_segsz; } ;
struct TYPE_16__ {char* p_text; TYPE_7__* p_pic; } ;
struct TYPE_17__ {int /*<<< orphan*/  b_active; TYPE_2__ data; int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ overlay_t ;
struct TYPE_18__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_19__ {int /*<<< orphan*/  b_updated; int /*<<< orphan*/  overlays; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_20__ {scalar_t__ fourcc; int i_height; int i_width; int /*<<< orphan*/  i_shmid; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_6__ const commandparams_t ;
struct TYPE_21__ {TYPE_1__* p; scalar_t__ i_planes; int /*<<< orphan*/  format; } ;
struct TYPE_15__ {size_t i_visible_lines; size_t i_visible_pitch; char* p_pixels; int /*<<< orphan*/  i_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_STAT ; 
 TYPE_3__* ListGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHM_RDONLY ; 
 scalar_t__ VLC_CODEC_TEXT ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (TYPE_6__ const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,...) ; 
 TYPE_7__* picture_New (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  picture_Release (TYPE_7__*) ; 
 char* shmat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct shmid_ds*) ; 
 int /*<<< orphan*/  shmdt (char*) ; 
 int /*<<< orphan*/  video_format_Setup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exec_DataSharedMem( filter_t *p_filter,
                               const commandparams_t *p_params,
                               commandparams_t *p_results )
{
#if defined(HAVE_SYS_SHM_H)
    filter_sys_t *p_sys = p_filter->p_sys;
    struct shmid_ds shminfo;
    overlay_t *p_ovl;
    size_t i_size;

    VLC_UNUSED(p_results);

    p_ovl = ListGet( &p_sys->overlays, p_params->i_id );
    if( p_ovl == NULL )
    {
        msg_Err( p_filter, "Invalid overlay: %d", p_params->i_id );
        return VLC_EGENERIC;
    }

    if( shmctl( p_params->i_shmid, IPC_STAT, &shminfo ) == -1 )
    {
        msg_Err( p_filter, "Unable to access shared memory" );
        return VLC_EGENERIC;
    }
    i_size = shminfo.shm_segsz;

    if( p_params->fourcc == VLC_CODEC_TEXT )
    {
        char *p_data;

        if( (p_params->i_height != 1) || (p_params->i_width < 1) )
        {
            msg_Err( p_filter,
                     "Invalid width and/or height. when specifying text height "
                     "must be 1 and width the number of bytes in the string, "
                     "including the null terminator" );
            return VLC_EGENERIC;
        }

        if( (size_t)p_params->i_width > i_size )
        {
            msg_Err( p_filter,
                     "Insufficient data in shared memory. need %d, got %zu",
                     p_params->i_width, i_size );
            return VLC_EGENERIC;
        }

        p_ovl->data.p_text = malloc( p_params->i_width );
        if( p_ovl->data.p_text == NULL )
        {
            msg_Err( p_filter, "Unable to allocate string storage" );
            return VLC_ENOMEM;
        }

        video_format_Setup( &p_ovl->format, VLC_CODEC_TEXT,
                            0, 0, 0, 0, 0, 1 );

        p_data = shmat( p_params->i_shmid, NULL, SHM_RDONLY );
        if( p_data == NULL )
        {
            msg_Err( p_filter, "Unable to attach to shared memory" );
            free( p_ovl->data.p_text );
            p_ovl->data.p_text = NULL;
            return VLC_ENOMEM;
        }
        memcpy( p_ovl->data.p_text, p_data, p_params->i_width );

        shmdt( p_data );
    }
    else
    {
        uint8_t *p_data, *p_in;
        size_t i_neededsize = 0;

        p_ovl->data.p_pic = picture_New( p_params->fourcc,
                                         p_params->i_width, p_params->i_height,
                                         1, 1 );
        if( p_ovl->data.p_pic == NULL )
            return VLC_ENOMEM;

        p_ovl->format = p_ovl->data.p_pic->format;

        for( size_t i_plane = 0; i_plane < (size_t)p_ovl->data.p_pic->i_planes;
             ++i_plane )
        {
            i_neededsize += p_ovl->data.p_pic->p[i_plane].i_visible_lines *
                            p_ovl->data.p_pic->p[i_plane].i_visible_pitch;
        }

        if( i_neededsize > i_size )
        {
            msg_Err( p_filter,
                     "Insufficient data in shared memory. need %zu, got %zu",
                     i_neededsize, i_size );
            picture_Release( p_ovl->data.p_pic );
            p_ovl->data.p_pic = NULL;
            return VLC_EGENERIC;
        }

        p_data = shmat( p_params->i_shmid, NULL, SHM_RDONLY );
        if( p_data == NULL )
        {
            msg_Err( p_filter, "Unable to attach to shared memory" );
            picture_Release( p_ovl->data.p_pic );
            p_ovl->data.p_pic = NULL;
            return VLC_ENOMEM;
        }

        p_in = p_data;
        for( size_t i_plane = 0; i_plane < (size_t)p_ovl->data.p_pic->i_planes;
             ++i_plane )
        {
            uint8_t *p_out = p_ovl->data.p_pic->p[i_plane].p_pixels;
            for( size_t i_line = 0;
                 i_line < (size_t)p_ovl->data.p_pic->p[i_plane].i_visible_lines;
                 ++i_line )
            {
                memcpy( p_out, p_in,
                            p_ovl->data.p_pic->p[i_plane].i_visible_pitch );
                p_out += p_ovl->data.p_pic->p[i_plane].i_pitch;
                p_in += p_ovl->data.p_pic->p[i_plane].i_visible_pitch;
            }
        }
        shmdt( p_data );
    }
    p_sys->b_updated = p_ovl->b_active;

    return VLC_SUCCESS;
#else
    VLC_UNUSED(p_params);
    VLC_UNUSED(p_results);

    msg_Err( p_filter, "system doesn't support shared memory" );
    return VLC_EGENERIC;
#endif
}