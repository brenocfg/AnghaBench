#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_33__ {int b_absolute; int b_ephemer; TYPE_3__* p_region; scalar_t__ i_stop; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_34__ {int i_align; struct TYPE_34__* p_next; int /*<<< orphan*/  i_alpha; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; int /*<<< orphan*/  p_picture; TYPE_9__* p_text; } ;
typedef  TYPE_3__ subpicture_region_t ;
typedef  int ssize_t ;
struct TYPE_32__ {int /*<<< orphan*/  p_pic; int /*<<< orphan*/  p_text; } ;
struct TYPE_30__ {scalar_t__ i_chroma; } ;
struct TYPE_35__ {int /*<<< orphan*/  i_alpha; int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; TYPE_1__ data; int /*<<< orphan*/  p_fontstyle; TYPE_11__ format; } ;
typedef  TYPE_4__ overlay_t ;
struct TYPE_36__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_31__ {char* p_begin; int /*<<< orphan*/  i_length; } ;
struct TYPE_37__ {int i_inputfd; char* psz_inputfile; int i_outputfd; char* psz_outputfile; size_t i_commands; int b_updated; int /*<<< orphan*/  overlays; TYPE_12__ output; int /*<<< orphan*/  processed; int /*<<< orphan*/  pending; TYPE_12__ input; int /*<<< orphan*/  atomic; scalar_t__ b_atomic; TYPE_7__** pp_commands; int /*<<< orphan*/  lock; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_38__ {scalar_t__ (* pf_execute ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pf_unparse ) (int /*<<< orphan*/ *,TYPE_12__*) ;scalar_t__ b_atomic; int /*<<< orphan*/  (* pf_parser ) (char*,char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  psz_command; } ;
typedef  TYPE_7__ commanddesc_t ;
struct TYPE_39__ {scalar_t__ i_status; int /*<<< orphan*/  results; TYPE_7__* p_command; int /*<<< orphan*/  params; } ;
typedef  TYPE_8__ command_t ;
struct TYPE_40__ {int /*<<< orphan*/  style; } ;

/* Variables and functions */
 int /*<<< orphan*/  BufferAdd (TYPE_12__*,char const*,int) ; 
 int /*<<< orphan*/  BufferDel (TYPE_12__*,int) ; 
 char* BufferGetToken (TYPE_12__*) ; 
 int /*<<< orphan*/  BufferPrintf (TYPE_12__*,char*,scalar_t__) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ ENXIO ; 
 TYPE_4__* ListWalk (int /*<<< orphan*/ *) ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 TYPE_8__* QueueDequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QueueEnqueue (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 scalar_t__ VLC_CODEC_TEXT ; 
 scalar_t__ VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ errno ; 
 TYPE_2__* filter_NewSubpicture (TYPE_5__*) ; 
 TYPE_8__* malloc (int) ; 
 char* memchr (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_5__*,char*,char*,...) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,TYPE_12__*) ; 
 TYPE_3__* subpicture_region_New (TYPE_11__*) ; 
 TYPE_9__* text_segment_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Duplicate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* vlc_open (char*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 
 int vlc_write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static subpicture_t *Filter( filter_t *p_filter, vlc_tick_t date )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    /* We might need to open these at any time. */
    vlc_mutex_lock( &p_sys->lock );
    if( p_sys->i_inputfd == -1 )
    {
        p_sys->i_inputfd = vlc_open( p_sys->psz_inputfile, O_RDONLY | O_NONBLOCK );
        if( p_sys->i_inputfd == -1 )
        {
            msg_Warn( p_filter, "Failed to grab input file: %s (%s)",
                      p_sys->psz_inputfile, vlc_strerror_c(errno) );
        }
        else
        {
            msg_Info( p_filter, "Grabbed input file: %s",
                      p_sys->psz_inputfile );
        }
    }

    if( p_sys->i_outputfd == -1 )
    {
        p_sys->i_outputfd = vlc_open( p_sys->psz_outputfile,
                                  O_WRONLY | O_NONBLOCK );
        if( p_sys->i_outputfd == -1 )
        {
            if( errno != ENXIO )
            {
                msg_Warn( p_filter, "Failed to grab output file: %s (%s)",
                          p_sys->psz_outputfile, vlc_strerror_c(errno) );
            }
        }
        else
        {
            msg_Info( p_filter, "Grabbed output file: %s",
                      p_sys->psz_outputfile );
        }
    }
    vlc_mutex_unlock( &p_sys->lock );

    /* Read any waiting commands */
    if( p_sys->i_inputfd != -1 )
    {
        char p_buffer[1024];
        ssize_t i_len = read( p_sys->i_inputfd, p_buffer, 1024 );
        if( i_len == -1 )
        {
            /* We hit an error */
            if( errno != EAGAIN )
            {
                msg_Warn( p_filter, "Error on input file: %s",
                          vlc_strerror_c(errno) );
                vlc_close( p_sys->i_inputfd );
                p_sys->i_inputfd = -1;
            }
        }
        else if( i_len == 0 )
        {
            /* We hit the end-of-file */
        }
        else
        {
            BufferAdd( &p_sys->input, p_buffer, i_len );
        }
    }

    /* Parse any complete commands */
    char *p_end, *p_cmd;
    while( ( p_end = memchr( p_sys->input.p_begin, '\n',
                             p_sys->input.i_length ) ) )
    {
        commanddesc_t *p_cur = NULL;
        bool b_found = false;
        size_t i_index = 0;

        *p_end = '\0';
        p_cmd = BufferGetToken( &p_sys->input );

        msg_Info( p_filter, "Search command: %s", p_cmd );
        for( i_index = 0; i_index < p_sys->i_commands; i_index++ )
        {
            p_cur = p_sys->pp_commands[i_index];
            if( !strncmp( p_cur->psz_command, p_cmd, strlen(p_cur->psz_command) ) )
            {
                p_cmd[strlen(p_cur->psz_command)] = '\0';
                b_found = true;
                break;
            }
        }

        if( !b_found )
        {
            /* No matching command */
            msg_Err( p_filter, "Got invalid command: %s", p_cmd );
            BufferPrintf( &p_sys->output, "FAILURE: %d Invalid Command\n", VLC_EGENERIC );
        }
        else
        {
            msg_Info( p_filter, "Got valid command: %s", p_cmd );

            command_t *p_cmddesc = malloc( sizeof( command_t ) );
            if( !p_cmddesc )
                return NULL;

            p_cmd = p_cmd + strlen(p_cur->psz_command) +1;
            p_cmddesc->p_command = p_cur;
            p_cmddesc->p_command->pf_parser( p_cmd, p_end,
                                             &p_cmddesc->params );

            if( p_cmddesc->p_command->b_atomic && p_sys->b_atomic )
                QueueEnqueue( &p_sys->atomic, p_cmddesc );
            else
                QueueEnqueue( &p_sys->pending, p_cmddesc );
        }

        BufferDel( &p_sys->input, p_end - p_sys->input.p_begin + 1 );
    }

    /* Process any pending commands */
    command_t *p_command = NULL;
    while( (p_command = QueueDequeue( &p_sys->pending )) )
    {
        p_command->i_status =
            p_command->p_command->pf_execute( p_filter, &p_command->params,
                                              &p_command->results );
        QueueEnqueue( &p_sys->processed, p_command );
    }

    /* Output any processed commands */
    while( (p_command = QueueDequeue( &p_sys->processed )) )
    {
        if( p_command->i_status == VLC_SUCCESS )
        {
            const char *psz_success = "SUCCESS:";
            const char *psz_nl = "\n";
            BufferAdd( &p_sys->output, psz_success, 8 );
            p_command->p_command->pf_unparse( &p_command->results,
                                              &p_sys->output );
            BufferAdd( &p_sys->output, psz_nl, 1 );
        }
        else
        {
            BufferPrintf( &p_sys->output, "FAILURE: %d\n",
                          p_command->i_status );
        }
    }

    /* Try emptying the output buffer */
    if( p_sys->i_outputfd != -1 )
    {
        ssize_t i_len = vlc_write( p_sys->i_outputfd, p_sys->output.p_begin,
                                   p_sys->output.i_length );
        if( i_len == -1 )
        {
            /* We hit an error */
            if( errno != EAGAIN )
            {
                msg_Warn( p_filter, "Error on output file: %s",
                          vlc_strerror_c(errno) );
                vlc_close( p_sys->i_outputfd );
                p_sys->i_outputfd = -1;
            }
        }
        else
        {
            BufferDel( &p_sys->output, i_len );
        }
    }

    if( !p_sys->b_updated )
        return NULL;

    subpicture_t *p_spu = NULL;
    overlay_t *p_overlay = NULL;

    p_spu = filter_NewSubpicture( p_filter );
    if( !p_spu )
        return NULL;

    p_spu->b_absolute = true;
    p_spu->i_start = date;
    p_spu->i_stop = 0;
    p_spu->b_ephemer = true;

    subpicture_region_t **pp_region = &p_spu->p_region;
    while( (p_overlay = ListWalk( &p_sys->overlays )) )
    {
        subpicture_region_t *p_region;

        *pp_region = p_region = subpicture_region_New( &p_overlay->format );
        if( !p_region )
            break;

        msg_Dbg( p_filter, "Displaying overlay: %4.4s, %d, %d, %d",
                 (char*)&p_overlay->format.i_chroma, p_overlay->i_x, p_overlay->i_y,
                 p_overlay->i_alpha );

        if( p_overlay->format.i_chroma == VLC_CODEC_TEXT )
        {
            p_region->p_text = text_segment_New( p_overlay->data.p_text );
            p_region->p_text->style = text_style_Duplicate( p_overlay->p_fontstyle );
        }
        else
        {
            /* FIXME the copy is probably not needed anymore */
            picture_Copy( p_region->p_picture, p_overlay->data.p_pic );
        }
        p_region->i_x = p_overlay->i_x;
        p_region->i_y = p_overlay->i_y;
        p_region->i_align = SUBPICTURE_ALIGN_LEFT | SUBPICTURE_ALIGN_TOP;
        p_region->i_alpha = p_overlay->i_alpha;
        pp_region = &p_region->p_next;
    }

    p_sys->b_updated = false;
    return p_spu;
}