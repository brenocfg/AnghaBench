#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {scalar_t__ cStreams; } ;
struct TYPE_8__ {TYPE_2__* streams; TYPE_1__ Parser; } ;
struct TYPE_7__ {int /*<<< orphan*/  packet_queued; int /*<<< orphan*/ * sample; int /*<<< orphan*/ * thread; } ;
typedef  TYPE_2__ StreamData ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_3__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static HRESULT AVISplitter_done_process(LPVOID iface)
{
    AVISplitterImpl *This = iface;
    DWORD x;
    ULONG ref;

    for (x = 0; x < This->Parser.cStreams; ++x)
    {
        StreamData *stream = This->streams + x;

        TRACE("Waiting for %u to terminate\n", x);
        /* Make the thread return first */
        SetEvent(stream->packet_queued);
        assert(WaitForSingleObject(stream->thread, 100000) != WAIT_TIMEOUT);
        CloseHandle(stream->thread);
        stream->thread = NULL;

        if (stream->sample)
        {
            ref = IMediaSample_Release(stream->sample);
            assert(ref == 0);
        }
        stream->sample = NULL;

        ResetEvent(stream->packet_queued);
    }
    TRACE("All threads are now terminated\n");

    return S_OK;
}