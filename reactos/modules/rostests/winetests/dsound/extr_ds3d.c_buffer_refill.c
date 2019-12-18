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
struct TYPE_3__ {scalar_t__ wave_len; scalar_t__ written; int offset; scalar_t__ wave; int buffer_size; int /*<<< orphan*/  dsbo; } ;
typedef  TYPE_1__ play_state_t ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DSERR_INVALIDPARAM ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_Lock (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_Unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static int buffer_refill(play_state_t* state, DWORD size)
{
    LPVOID ptr1,ptr2;
    DWORD len1,len2;
    HRESULT rc;

    if (size>state->wave_len-state->written)
        size=state->wave_len-state->written;

    /* some broken apps like Navyfield mistakenly pass NULL for a ppValue */
    rc=IDirectSoundBuffer_Lock(state->dsbo,state->offset,size,
                               &ptr1,NULL,&ptr2,&len2,0);
    ok(rc==DSERR_INVALIDPARAM,"expected %08x got %08x\n",DSERR_INVALIDPARAM, rc);
    rc=IDirectSoundBuffer_Lock(state->dsbo,state->offset,size,
                               &ptr1,&len1,&ptr2,&len2,0);
    ok(rc==DS_OK,"IDirectSoundBuffer_Lock() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return -1;

    memcpy(ptr1,state->wave+state->written,len1);
    state->written+=len1;
    if (ptr2!=NULL) {
        memcpy(ptr2,state->wave+state->written,len2);
        state->written+=len2;
    }
    state->offset=state->written % state->buffer_size;
    /* some apps blindly pass &ptr1 instead of ptr1 */
    rc=IDirectSoundBuffer_Unlock(state->dsbo,&ptr1,len1,ptr2,len2);
    ok(rc==DSERR_INVALIDPARAM, "IDDirectSoundBuffer_Unlock(): expected %08x got %08x, %p %p\n",DSERR_INVALIDPARAM, rc, &ptr1, ptr1);
    rc=IDirectSoundBuffer_Unlock(state->dsbo,ptr1,len1,ptr2,len2);
    ok(rc==DS_OK,"IDirectSoundBuffer_Unlock() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return -1;
    return size;
}