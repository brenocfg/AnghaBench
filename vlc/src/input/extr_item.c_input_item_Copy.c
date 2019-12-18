#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_t ;
struct TYPE_8__ {int b_net; scalar_t__ i_slaves; int /*<<< orphan*/ * p_meta; int /*<<< orphan*/  lock; TYPE_7__** pp_slaves; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_duration; int /*<<< orphan*/  psz_name; int /*<<< orphan*/  psz_uri; } ;
typedef  TYPE_1__ input_item_t ;
typedef  int /*<<< orphan*/  input_item_slave_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_priority; int /*<<< orphan*/  i_type; int /*<<< orphan*/  psz_uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_NET_UNKNOWN ; 
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_7__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_CopyOptions (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* input_item_NewExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_item_slave_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_meta_Merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_meta_New () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

input_item_t *input_item_Copy( input_item_t *p_input )
{
    vlc_meta_t *meta = NULL;
    input_item_t *item;
    bool b_net;

    vlc_mutex_lock( &p_input->lock );

    item = input_item_NewExt( p_input->psz_uri, p_input->psz_name,
                              p_input->i_duration, p_input->i_type,
                              ITEM_NET_UNKNOWN );
    if( likely(item != NULL) && p_input->p_meta != NULL )
    {
        meta = vlc_meta_New();
        vlc_meta_Merge( meta, p_input->p_meta );
    }
    b_net = p_input->b_net;

    if( likely(item != NULL) && p_input->i_slaves > 0 )
    {
        for( int i = 0; i < p_input->i_slaves; i++ )
        {
            input_item_slave_t* slave = input_item_slave_New(
                        p_input->pp_slaves[i]->psz_uri,
                        p_input->pp_slaves[i]->i_type,
                        p_input->pp_slaves[i]->i_priority);
            if( unlikely(slave != NULL) )
            {
                TAB_APPEND(item->i_slaves, item->pp_slaves, slave);
            }
        }
    }

    vlc_mutex_unlock( &p_input->lock );

    if( likely(item != NULL) )
    {   /* No need to lock; no other thread has seen this new item yet. */
        input_item_CopyOptions( item, p_input );
        item->p_meta = meta;
        item->b_net = b_net;
    }

    return item;
}