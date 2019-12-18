#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_6__ {int i_attachment; TYPE_1__* p_item; TYPE_3__** attachment; } ;
typedef  TYPE_2__ input_thread_private_t ;
typedef  int /*<<< orphan*/  input_attachment_t ;
struct TYPE_7__ {int /*<<< orphan*/  psz_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_2__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * vlc_input_attachment_Duplicate (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

input_attachment_t *input_GetAttachment(input_thread_t *input, const char *name)
{
    input_thread_private_t *priv = input_priv(input);

    vlc_mutex_lock(&priv->p_item->lock);
    for (int i = 0; i < priv->i_attachment; i++)
    {
        if (!strcmp( priv->attachment[i]->psz_name, name))
        {
            input_attachment_t *attachment =
                vlc_input_attachment_Duplicate(priv->attachment[i] );
            vlc_mutex_unlock( &priv->p_item->lock );
            return attachment;
        }
    }
    vlc_mutex_unlock( &priv->p_item->lock );
    return NULL;
}