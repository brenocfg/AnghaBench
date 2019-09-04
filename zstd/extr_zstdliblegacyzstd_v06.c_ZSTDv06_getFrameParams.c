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
struct TYPE_4__ {int frameContentSize; scalar_t__ windowLog; } ;
typedef  TYPE_1__ ZSTDv06_frameParams ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_readLE16 (int const*) ; 
 scalar_t__ MEM_readLE32 (void const*) ; 
 int MEM_readLE64 (int const*) ; 
 scalar_t__ ZSTDv06_MAGICNUMBER ; 
 scalar_t__ ZSTDv06_WINDOWLOG_ABSOLUTEMIN ; 
 size_t ZSTDv06_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTDv06_frameHeaderSize_min ; 
 int /*<<< orphan*/  frameParameter_unsupported ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefix_unknown ; 

size_t ZSTDv06_getFrameParams(ZSTDv06_frameParams* fparamsPtr, const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;

    if (srcSize < ZSTDv06_frameHeaderSize_min) return ZSTDv06_frameHeaderSize_min;
    if (MEM_readLE32(src) != ZSTDv06_MAGICNUMBER) return ERROR(prefix_unknown);

    /* ensure there is enough `srcSize` to fully read/decode frame header */
    { size_t const fhsize = ZSTDv06_frameHeaderSize(src, srcSize);
      if (srcSize < fhsize) return fhsize; }

    memset(fparamsPtr, 0, sizeof(*fparamsPtr));
    {   BYTE const frameDesc = ip[4];
        fparamsPtr->windowLog = (frameDesc & 0xF) + ZSTDv06_WINDOWLOG_ABSOLUTEMIN;
        if ((frameDesc & 0x20) != 0) return ERROR(frameParameter_unsupported);   /* reserved 1 bit */
        switch(frameDesc >> 6)  /* fcsId */
        {
            default:   /* impossible */
            case 0 : fparamsPtr->frameContentSize = 0; break;
            case 1 : fparamsPtr->frameContentSize = ip[5]; break;
            case 2 : fparamsPtr->frameContentSize = MEM_readLE16(ip+5)+256; break;
            case 3 : fparamsPtr->frameContentSize = MEM_readLE64(ip+5); break;
    }   }
    return 0;
}