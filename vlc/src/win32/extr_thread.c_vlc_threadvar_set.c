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
typedef  TYPE_1__* vlc_threadvar_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,void*) ; 

int vlc_threadvar_set (vlc_threadvar_t key, void *value)
{
    int saved = GetLastError ();

    if (!TlsSetValue(key->id, value))
        return ENOMEM;

    SetLastError(saved);
    return 0;
}