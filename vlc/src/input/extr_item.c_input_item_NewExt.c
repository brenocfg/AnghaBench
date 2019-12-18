#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_event_manager_t ;
struct TYPE_8__ {int i_type; int b_net; int b_error_when_reading; int /*<<< orphan*/  pp_slaves; int /*<<< orphan*/  i_slaves; int /*<<< orphan*/  pp_epg; int /*<<< orphan*/  i_epg; int /*<<< orphan*/ * p_meta; int /*<<< orphan*/ * p_stats; int /*<<< orphan*/  es; int /*<<< orphan*/  i_es; int /*<<< orphan*/  pp_categories; int /*<<< orphan*/  i_categories; int /*<<< orphan*/  i_duration; int /*<<< orphan*/ * opaques; int /*<<< orphan*/ * optflagv; scalar_t__ optflagc; int /*<<< orphan*/  ppsz_options; int /*<<< orphan*/  i_options; int /*<<< orphan*/ * psz_uri; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/  lock; int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ input_item_t ;
struct TYPE_9__ {TYPE_1__ item; int /*<<< orphan*/  rc; } ;
typedef  TYPE_2__ input_item_owner_t ;
typedef  enum input_item_type_e { ____Placeholder_input_item_type_e } input_item_type_e ;
typedef  enum input_item_net_type { ____Placeholder_input_item_net_type } input_item_net_type ;

/* Variables and functions */
 int ITEM_NET ; 
 int ITEM_NET_UNKNOWN ; 
 int ITEM_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  input_item_SetName (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  input_item_SetURI (TYPE_1__*,char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_event_manager_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

input_item_t *
input_item_NewExt( const char *psz_uri, const char *psz_name,
                   vlc_tick_t duration, enum input_item_type_e type, enum input_item_net_type i_net )
{
    input_item_owner_t *owner = calloc( 1, sizeof( *owner ) );
    if( unlikely(owner == NULL) )
        return NULL;

    vlc_atomic_rc_init( &owner->rc );

    input_item_t *p_input = &owner->item;
    vlc_event_manager_t * p_em = &p_input->event_manager;

    vlc_mutex_init( &p_input->lock );

    p_input->psz_name = NULL;
    if( psz_name )
        input_item_SetName( p_input, psz_name );

    p_input->psz_uri = NULL;
    if( psz_uri )
        input_item_SetURI( p_input, psz_uri );
    else
    {
        p_input->i_type = ITEM_TYPE_UNKNOWN;
        p_input->b_net = false;
    }

    TAB_INIT( p_input->i_options, p_input->ppsz_options );
    p_input->optflagc = 0;
    p_input->optflagv = NULL;
    p_input->opaques = NULL;

    p_input->i_duration = duration;
    TAB_INIT( p_input->i_categories, p_input->pp_categories );
    TAB_INIT( p_input->i_es, p_input->es );
    p_input->p_stats = NULL;
    p_input->p_meta = NULL;
    TAB_INIT( p_input->i_epg, p_input->pp_epg );
    TAB_INIT( p_input->i_slaves, p_input->pp_slaves );

    vlc_event_manager_init( p_em, p_input );

    if( type != ITEM_TYPE_UNKNOWN )
        p_input->i_type = type;
    p_input->b_error_when_reading = false;

    if( i_net != ITEM_NET_UNKNOWN )
        p_input->b_net = i_net == ITEM_NET;
    return p_input;
}