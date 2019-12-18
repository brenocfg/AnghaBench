#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_refcount; int /*<<< orphan*/ * p_input_item; int /*<<< orphan*/  event_manager; int /*<<< orphan*/ * p_subitems; int /*<<< orphan*/  state; int /*<<< orphan*/  subitems_lock; int /*<<< orphan*/  parsed_lock; int /*<<< orphan*/  parsed_cond; int /*<<< orphan*/ * p_libvlc_instance; } ;
typedef  TYPE_1__ libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  install_input_item_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_NothingSpecial ; 
 int /*<<< orphan*/  libvlc_event_manager_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  libvlc_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

libvlc_media_t * libvlc_media_new_from_input_item(
                                   libvlc_instance_t *p_instance,
                                   input_item_t *p_input_item )
{
    libvlc_media_t * p_md;

    if (!p_input_item)
    {
        libvlc_printerr( "No input item given" );
        return NULL;
    }

    p_md = calloc( 1, sizeof(libvlc_media_t) );
    if( !p_md )
    {
        libvlc_printerr( "Not enough memory" );
        return NULL;
    }

    p_md->p_libvlc_instance = p_instance;
    p_md->p_input_item      = p_input_item;
    p_md->i_refcount        = 1;

    vlc_cond_init(&p_md->parsed_cond);
    vlc_mutex_init(&p_md->parsed_lock);
    vlc_mutex_init(&p_md->subitems_lock);

    p_md->state = libvlc_NothingSpecial;

    /* A media descriptor can be a playlist. When you open a playlist
     * It can give a bunch of item to read. */
    p_md->p_subitems        = NULL;

    libvlc_event_manager_init( &p_md->event_manager, p_md );

    input_item_Hold( p_md->p_input_item );

    install_input_item_observer( p_md );

    libvlc_retain( p_instance );
    return p_md;
}