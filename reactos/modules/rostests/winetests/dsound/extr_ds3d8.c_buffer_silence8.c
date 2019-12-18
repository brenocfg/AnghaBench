#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset; int buffer_size; int /*<<< orphan*/  dsbo; TYPE_1__* wfx; } ;
typedef  TYPE_2__ play_state_t ;
struct TYPE_4__ {int wBitsPerSample; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_Lock (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundBuffer_Unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static int buffer_silence8(play_state_t* state, DWORD size)
{
    LPVOID ptr1,ptr2;
    DWORD len1,len2;
    HRESULT rc;
    BYTE s;

    rc=IDirectSoundBuffer_Lock(state->dsbo,state->offset,size,
                               &ptr1,&len1,&ptr2,&len2,0);
    ok(rc==DS_OK,"IDirectSoundBuffer_Lock() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return -1;

    s=(state->wfx->wBitsPerSample==8?0x80:0);
    memset(ptr1,s,len1);
    if (ptr2!=NULL) {
        memset(ptr2,s,len2);
    }
    state->offset=(state->offset+size) % state->buffer_size;
    rc=IDirectSoundBuffer_Unlock(state->dsbo,ptr1,len1,ptr2,len2);
    ok(rc==DS_OK,"IDirectSoundBuffer_Unlock() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return -1;
    return size;
}