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
struct TYPE_3__ {int /*<<< orphan*/ * var_root; } ;
typedef  TYPE_1__ vlc_object_internals_t ;

/* Variables and functions */
 int /*<<< orphan*/  CleanupVar ; 
 int /*<<< orphan*/  tdestroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 

void var_DestroyAll( vlc_object_t *obj )
{
    vlc_object_internals_t *priv = vlc_internals( obj );

    tdestroy( priv->var_root, CleanupVar );
    priv->var_root = NULL;
}