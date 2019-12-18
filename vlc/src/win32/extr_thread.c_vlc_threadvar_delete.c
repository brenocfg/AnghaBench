#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  struct vlc_threadvar* vlc_threadvar_t ;
struct vlc_threadvar {int /*<<< orphan*/  id; TYPE_2__* prev; TYPE_1__* next; } ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {TYPE_2__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TlsFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_threadvar*) ; 
 int /*<<< orphan*/  super_mutex ; 
 TYPE_2__* vlc_threadvar_last ; 

void vlc_threadvar_delete (vlc_threadvar_t *p_tls)
{
    struct vlc_threadvar *var = *p_tls;

    EnterCriticalSection(&super_mutex);
    if (var->prev != NULL)
        var->prev->next = var->next;

    if (var->next != NULL)
        var->next->prev = var->prev;
    else
        vlc_threadvar_last = var->prev;

    LeaveCriticalSection(&super_mutex);

    TlsFree (var->id);
    free (var);
}