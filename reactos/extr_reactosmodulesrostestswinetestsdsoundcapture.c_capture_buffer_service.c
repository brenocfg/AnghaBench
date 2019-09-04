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
struct TYPE_3__ {int offset; int size; int buffer_size; int /*<<< orphan*/  dscbo; } ;
typedef  TYPE_1__ capture_state_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundCaptureBuffer_GetCurrentPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundCaptureBuffer_Lock (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundCaptureBuffer_Unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static int capture_buffer_service(capture_state_t* state)
{
    HRESULT rc;
    LPVOID ptr1,ptr2;
    DWORD len1,len2;
    DWORD capture_pos,read_pos;

    rc=IDirectSoundCaptureBuffer_GetCurrentPosition(state->dscbo,&capture_pos,
                                                    &read_pos);
    ok(rc==DS_OK,"IDirectSoundCaptureBuffer_GetCurrentPosition() failed: %08x\n", rc);
    if (rc!=DS_OK)
	return 0;

    rc=IDirectSoundCaptureBuffer_Lock(state->dscbo,state->offset,state->size,
                                      &ptr1,&len1,&ptr2,&len2,0);
    ok(rc==DS_OK,"IDirectSoundCaptureBuffer_Lock() failed: %08x\n", rc);
    if (rc!=DS_OK)
	return 0;

    rc=IDirectSoundCaptureBuffer_Unlock(state->dscbo,ptr1,len1,ptr2,len2);
    ok(rc==DS_OK,"IDirectSoundCaptureBuffer_Unlock() failed: %08x\n", rc);
    if (rc!=DS_OK)
	return 0;

    state->offset = (state->offset + state->size) % state->buffer_size;

    return 1;
}