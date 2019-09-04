#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_16__ {int llDuration; int llStop; scalar_t__ llCurrent; } ;
struct TYPE_17__ {unsigned int cStreams; TYPE_6__ sourceSeeking; } ;
struct TYPE_19__ {TYPE_7__ Parser; TYPE_8__* streams; TYPE_2__* oldindex; } ;
struct TYPE_15__ {int dwSampleSize; size_t dwLength; int dwScale; int dwRate; } ;
struct TYPE_18__ {int frames; unsigned int pos; size_t entries; TYPE_5__ streamheader; TYPE_4__** stdindex; scalar_t__ index; int /*<<< orphan*/  seek; } ;
struct TYPE_14__ {size_t nEntriesInUse; TYPE_3__* aIndex; } ;
struct TYPE_13__ {unsigned int dwSize; } ;
struct TYPE_12__ {int cb; TYPE_1__* aIndex; } ;
struct TYPE_11__ {int dwSize; int /*<<< orphan*/  dwChunkId; } ;
typedef  TYPE_8__ StreamData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD64 ;
typedef  size_t DWORD ;
typedef  TYPE_9__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,unsigned int,...) ; 
 int /*<<< orphan*/  S_OK ; 
 size_t StreamFromFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,size_t,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_an (char*,int) ; 

__attribute__((used)) static HRESULT AVISplitter_InitializeStreams(AVISplitterImpl *This)
{
    unsigned int x;

    if (This->oldindex)
    {
        DWORD nMax, n;

        for (x = 0; x < This->Parser.cStreams; ++x)
        {
            This->streams[x].frames = 0;
            This->streams[x].pos = ~0;
            This->streams[x].index = 0;
        }

        nMax = This->oldindex->cb / sizeof(This->oldindex->aIndex[0]);

        /* Ok, maybe this is more of an exercise to see if I interpret everything correctly or not, but that is useful for now. */
        for (n = 0; n < nMax; ++n)
        {
            DWORD streamId = StreamFromFOURCC(This->oldindex->aIndex[n].dwChunkId);
            if (streamId >= This->Parser.cStreams)
            {
                FIXME("Stream id %s ignored\n", debugstr_an((char*)&This->oldindex->aIndex[n].dwChunkId, 4));
                continue;
            }
            if (This->streams[streamId].pos == ~0U)
                This->streams[streamId].pos = n;

            if (This->streams[streamId].streamheader.dwSampleSize)
                This->streams[streamId].frames += This->oldindex->aIndex[n].dwSize / This->streams[streamId].streamheader.dwSampleSize;
            else
                ++This->streams[streamId].frames;
        }

        for (x = 0; x < This->Parser.cStreams; ++x)
        {
            if ((DWORD)This->streams[x].frames != This->streams[x].streamheader.dwLength)
            {
                FIXME("stream %u: frames found: %u, frames meant to be found: %u\n", x, (DWORD)This->streams[x].frames, This->streams[x].streamheader.dwLength);
            }
        }

    }
    else if (!This->streams[0].entries)
    {
        for (x = 0; x < This->Parser.cStreams; ++x)
        {
            This->streams[x].frames = This->streams[x].streamheader.dwLength;
        }
        /* MS Avi splitter does seek through the whole file, we should! */
        ERR("We should be manually seeking through the entire file to build an index, because the index is missing!!!\n");
        return E_NOTIMPL;
    }

    /* Not much here yet */
    for (x = 0; x < This->Parser.cStreams; ++x)
    {
        StreamData *stream = This->streams + x;
        DWORD y;
        DWORD64 frames = 0;

        stream->seek = TRUE;

        if (stream->stdindex)
        {
            stream->index = 0;
            stream->pos = 0;
            for (y = 0; y < stream->entries; ++y)
            {
                if (stream->streamheader.dwSampleSize)
                {
                    DWORD z;

                    for (z = 0; z < stream->stdindex[y]->nEntriesInUse; ++z)
                    {
                        UINT len = stream->stdindex[y]->aIndex[z].dwSize & ~(1u << 31);
                        frames += len / stream->streamheader.dwSampleSize + !!(len % stream->streamheader.dwSampleSize);
                    }
                }
                else
                    frames += stream->stdindex[y]->nEntriesInUse;
            }
        }
        else frames = stream->frames;

        frames *= stream->streamheader.dwScale;
        /* Keep accuracy as high as possible for duration */
        This->Parser.sourceSeeking.llDuration = frames * 10000000;
        This->Parser.sourceSeeking.llDuration /= stream->streamheader.dwRate;
        This->Parser.sourceSeeking.llStop = This->Parser.sourceSeeking.llDuration;
        This->Parser.sourceSeeking.llCurrent = 0;

        frames /= stream->streamheader.dwRate;

        TRACE("Duration: %d days, %d hours, %d minutes and %d.%03u seconds\n", (DWORD)(frames / 86400),
        (DWORD)((frames % 86400) / 3600), (DWORD)((frames % 3600) / 60), (DWORD)(frames % 60),
        (DWORD)(This->Parser.sourceSeeking.llDuration/10000) % 1000);
    }

    return S_OK;
}