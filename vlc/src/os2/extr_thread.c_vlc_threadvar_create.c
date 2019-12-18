#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  struct vlc_threadvar* vlc_threadvar_t ;
struct vlc_threadvar {void (* destroy ) (void*) ;struct vlc_threadvar* next; struct vlc_threadvar* prev; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 scalar_t__ DosAllocThreadLocalMemory (int,int /*<<< orphan*/ *) ; 
 int EAGAIN ; 
 int errno ; 
 int /*<<< orphan*/  free (struct vlc_threadvar*) ; 
 struct vlc_threadvar* malloc (int) ; 
 int /*<<< orphan*/  super_mutex ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vlc_threadvar* vlc_threadvar_last ; 

int vlc_threadvar_create (vlc_threadvar_t *p_tls, void (*destr) (void *))
{
    ULONG rc;

    struct vlc_threadvar *var = malloc (sizeof (*var));
    if (unlikely(var == NULL))
        return errno;

    rc = DosAllocThreadLocalMemory( 1, &var->id );
    if( rc )
    {
        free (var);
        return EAGAIN;
    }

    var->destroy = destr;
    var->next = NULL;
    *p_tls = var;

    vlc_mutex_lock (&super_mutex);
    var->prev = vlc_threadvar_last;
    if (var->prev)
        var->prev->next = var;

    vlc_threadvar_last = var;
    vlc_mutex_unlock (&super_mutex);
    return 0;
}