#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int locked; int /*<<< orphan*/  mutex; int /*<<< orphan*/  contention; int /*<<< orphan*/  dynamic; } ;
typedef  TYPE_1__ vlc_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SleepConditionVariableCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  super_mutex ; 
 int /*<<< orphan*/  super_variable ; 
 int /*<<< orphan*/  vlc_mutex_mark (TYPE_1__*) ; 

void vlc_mutex_lock (vlc_mutex_t *p_mutex)
{
    if (!p_mutex->dynamic)
    {   /* static mutexes */
        EnterCriticalSection(&super_mutex);
        while (p_mutex->locked)
        {
            p_mutex->contention++;
            SleepConditionVariableCS(&super_variable, &super_mutex, INFINITE);
            p_mutex->contention--;
        }
        p_mutex->locked = true;
        LeaveCriticalSection(&super_mutex);
    }
    else
        EnterCriticalSection (&p_mutex->mutex);

    vlc_mutex_mark(p_mutex);
}