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
struct vlc_threadvar {scalar_t__ id; void (* destroy ) (void*) ;struct vlc_threadvar* next; struct vlc_threadvar* prev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 scalar_t__ TlsAlloc () ; 
 int errno ; 
 int /*<<< orphan*/  free (struct vlc_threadvar*) ; 
 struct vlc_threadvar* malloc (int) ; 
 int /*<<< orphan*/  super_mutex ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct vlc_threadvar* vlc_threadvar_last ; 

int vlc_threadvar_create (vlc_threadvar_t *p_tls, void (*destr) (void *))
{
    struct vlc_threadvar *var = malloc (sizeof (*var));
    if (unlikely(var == NULL))
        return errno;

    var->id = TlsAlloc();
    if (var->id == TLS_OUT_OF_INDEXES)
    {
        free (var);
        return EAGAIN;
    }
    var->destroy = destr;
    var->next = NULL;
    *p_tls = var;

    EnterCriticalSection(&super_mutex);
    var->prev = vlc_threadvar_last;
    if (var->prev)
        var->prev->next = var;

    vlc_threadvar_last = var;
    LeaveCriticalSection(&super_mutex);
    return 0;
}