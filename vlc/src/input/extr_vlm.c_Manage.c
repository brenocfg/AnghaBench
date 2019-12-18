#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int input_state_changed; int i_media; int i_schedule; int /*<<< orphan*/  lock; TYPE_3__** schedule; TYPE_5__** media; int /*<<< orphan*/  lock_manage; int /*<<< orphan*/  wait_manage; } ;
typedef  TYPE_4__ vlm_t ;
typedef  int /*<<< orphan*/  vlm_message_t ;
struct TYPE_9__ {scalar_t__ b_loop; } ;
struct TYPE_10__ {int i_input; int /*<<< orphan*/  id; scalar_t__ b_vod; TYPE_1__ broadcast; } ;
struct TYPE_13__ {int i_instance; TYPE_2__ cfg; TYPE_6__** instance; } ;
typedef  TYPE_5__ vlm_media_sys_t ;
struct TYPE_14__ {int i_index; int /*<<< orphan*/  player; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_6__ vlm_media_instance_sys_t ;
typedef  scalar_t__ time_t ;
struct TYPE_11__ {scalar_t__ date; scalar_t__ period; int i_repeat; int i_command; int /*<<< orphan*/ * command; scalar_t__ b_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteCommand (TYPE_4__*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TAB_APPEND (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_REMOVE (int,char**,char*) ; 
 int /*<<< orphan*/  VLM_START_MEDIA_BROADCAST_INSTANCE ; 
 int /*<<< orphan*/  VLM_STOP_MEDIA_INSTANCE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 scalar_t__ vlc_cond_timedwait_daytime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_IsStarted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlm_ControlInternal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vlm_MessageDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* Manage( void* p_object )
{
    vlm_t *vlm = (vlm_t*)p_object;
    time_t lastcheck, now, nextschedule = 0;

    time(&lastcheck);

    for( ;; )
    {
        char **ppsz_scheduled_commands = NULL;
        int    i_scheduled_commands = 0;
        bool scheduled_command = false;

        vlc_mutex_lock( &vlm->lock_manage );
        mutex_cleanup_push( &vlm->lock_manage );
        while( !vlm->input_state_changed && !scheduled_command )
        {
            if( nextschedule != 0 )
                scheduled_command = vlc_cond_timedwait_daytime( &vlm->wait_manage, &vlm->lock_manage, nextschedule ) != 0;
            else
                vlc_cond_wait( &vlm->wait_manage, &vlm->lock_manage );
        }
        vlm->input_state_changed = false;
        vlc_cleanup_pop( );
        vlc_mutex_unlock( &vlm->lock_manage );

        int canc = vlc_savecancel ();
        /* destroy the inputs that wants to die, and launch the next input */
        vlc_mutex_lock( &vlm->lock );
        for( int i = 0; i < vlm->i_media; i++ )
        {
            vlm_media_sys_t *p_media = vlm->media[i];

            for( int j = 0; j < p_media->i_instance; )
            {
                vlm_media_instance_sys_t *p_instance = p_media->instance[j];

                vlc_player_Lock(p_instance->player);
                if (!vlc_player_IsStarted(p_instance->player))
                {
                    vlc_player_Unlock(p_instance->player);
                    int i_new_input_index;

                    /* */
                    i_new_input_index = p_instance->i_index + 1;
                    if( !p_media->cfg.b_vod && p_media->cfg.broadcast.b_loop && i_new_input_index >= p_media->cfg.i_input )
                        i_new_input_index = 0;

                    /* FIXME implement multiple input with VOD */
                    if( p_media->cfg.b_vod || i_new_input_index >= p_media->cfg.i_input )
                        vlm_ControlInternal( vlm, VLM_STOP_MEDIA_INSTANCE, p_media->cfg.id, p_instance->psz_name );
                    else
                        vlm_ControlInternal( vlm, VLM_START_MEDIA_BROADCAST_INSTANCE, p_media->cfg.id, p_instance->psz_name, i_new_input_index );

                    j = 0;
                }
                else
                {
                    vlc_player_Unlock(p_instance->player);
                    j++;
                }
            }
        }

        /* scheduling */
        time(&now);
        nextschedule = 0;

        for( int i = 0; i < vlm->i_schedule; i++ )
        {
            time_t real_date = vlm->schedule[i]->date;

            if( vlm->schedule[i]->b_enabled )
            {
                bool b_now = false;
                if( vlm->schedule[i]->date == 0 ) // now !
                {
                    vlm->schedule[i]->date = now;
                    real_date = now;
                    b_now = true;
                }
                else if( vlm->schedule[i]->period != 0 )
                {
                    int j = 0;
                    while( ((vlm->schedule[i]->date + j *
                             vlm->schedule[i]->period) <= lastcheck) &&
                           ( vlm->schedule[i]->i_repeat > j ||
                             vlm->schedule[i]->i_repeat < 0 ) )
                    {
                        j++;
                    }

                    real_date = vlm->schedule[i]->date + j *
                        vlm->schedule[i]->period;
                }

                if( real_date <= now )
                {
                    if( real_date > lastcheck || b_now )
                    {
                        for( int j = 0; j < vlm->schedule[i]->i_command; j++ )
                        {
                            TAB_APPEND( i_scheduled_commands,
                                        ppsz_scheduled_commands,
                                        strdup(vlm->schedule[i]->command[j] ) );
                        }
                    }
                }
                else if( nextschedule == 0 || real_date < nextschedule )
                {
                    nextschedule = real_date;
                }
            }
        }

        while( i_scheduled_commands )
        {
            vlm_message_t *message = NULL;
            char *psz_command = ppsz_scheduled_commands[0];
            ExecuteCommand( vlm, psz_command,&message );

            /* for now, drop the message */
            vlm_MessageDelete( message );
            TAB_REMOVE( i_scheduled_commands,
                        ppsz_scheduled_commands,
                        psz_command );
            free( psz_command );
        }

        lastcheck = now;
        vlc_mutex_unlock( &vlm->lock );
        vlc_restorecancel (canc);
    }

    return NULL;
}