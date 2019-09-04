#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {scalar_t__ cStreams; } ;
struct TYPE_9__ {TYPE_2__* streams; TYPE_1__ Parser; } ;
struct TYPE_8__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  packet_queued; int /*<<< orphan*/ * sample; } ;
typedef  TYPE_2__ StreamData ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_3__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static HRESULT AVISplitter_Flush(LPVOID iface)
{
    AVISplitterImpl *This = iface;
    DWORD x;
    ULONG ref;

    TRACE("(%p)->()\n", This);

    for (x = 0; x < This->Parser.cStreams; ++x)
    {
        StreamData *stream = This->streams + x;

        if (stream->sample)
        {
            ref = IMediaSample_Release(stream->sample);
            assert(ref == 0);
        }
        stream->sample = NULL;

        ResetEvent(stream->packet_queued);
        assert(!stream->thread);
    }

    return S_OK;
}