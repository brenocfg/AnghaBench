#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_12__ {TYPE_1__* next; TYPE_2__* access; } ;
typedef  TYPE_3__ access_sys_t ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  mrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 TYPE_2__* vlc_access_NewMRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_stream_Eof (TYPE_2__*) ; 

__attribute__((used)) static stream_t *GetAccess(stream_t *access)
{
    access_sys_t *sys = access->p_sys;
    stream_t *a = sys->access;

    if (a != NULL)
    {
        if (!vlc_stream_Eof(a))
            return a;

        vlc_stream_Delete(a);
        sys->access = NULL;
    }

    if (sys->next == NULL)
        return NULL;

    a = vlc_access_NewMRL(VLC_OBJECT(access), sys->next->mrl);
    if (a == NULL)
        return NULL;

    sys->access = a;
    sys->next = sys->next->next;
    return a;
}