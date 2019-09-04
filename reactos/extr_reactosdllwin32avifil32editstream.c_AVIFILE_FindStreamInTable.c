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
struct TYPE_6__ {scalar_t__ dwStart; } ;
struct TYPE_8__ {scalar_t__ nStreams; TYPE_2__* pStreams; TYPE_1__ sInfo; } ;
struct TYPE_7__ {scalar_t__ dwLength; scalar_t__ dwStart; int /*<<< orphan*/ * pStream; } ;
typedef  int /*<<< orphan*/ * PAVISTREAM ;
typedef  TYPE_3__ IAVIEditStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_BADPARAM ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 scalar_t__ EditStreamEnd (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static HRESULT AVIFILE_FindStreamInTable(IAVIEditStreamImpl* const This,
					 DWORD pos,PAVISTREAM *ppStream,
					 DWORD* streamPos,
					 DWORD* streamNr,BOOL bFindSample)
{
  DWORD n;

  TRACE("(%p,%u,%p,%p,%p,%d)\n",This,pos,ppStream,streamPos,
        streamNr,bFindSample);

  if (pos < This->sInfo.dwStart)
    return AVIERR_BADPARAM;

  pos -= This->sInfo.dwStart;
  for (n = 0; n < This->nStreams; n++) {
    if (pos < This->pStreams[n].dwLength) {
      *ppStream  = This->pStreams[n].pStream;
      *streamPos = This->pStreams[n].dwStart + pos;
      if (streamNr != NULL)
        *streamNr = n;

      return AVIERR_OK;
    }
    pos -= This->pStreams[n].dwLength;
  }
  if (pos == 0 && bFindSample) {
    *ppStream  = This->pStreams[--n].pStream;
    *streamPos = EditStreamEnd(This, n);
    if (streamNr != NULL)
      *streamNr = n;

    TRACE(" -- pos=0 && b=1 -> (%p,%u,%u)\n",*ppStream, *streamPos, n);
    return AVIERR_OK;
  } else {
    *ppStream = NULL;
    *streamPos = 0;
    if (streamNr != NULL)
      *streamNr = 0;

    TRACE(" -> ERROR (NULL,0,0)\n");
    return AVIERR_BADPARAM;
  }
}