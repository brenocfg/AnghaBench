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
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ psz_uri; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 char* strdup (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

char *input_item_GetURI( input_item_t *p_i )
{
    vlc_mutex_lock( &p_i->lock );

    char *psz_s = p_i->psz_uri ? strdup( p_i->psz_uri ) : NULL;

    vlc_mutex_unlock( &p_i->lock );
    return psz_s;
}