#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strHdr ;
typedef  int /*<<< orphan*/  ckRIFF ;
struct TYPE_30__ {size_t dwStreams; int cksize; size_t dwDataOffset; scalar_t__ fccType; int /*<<< orphan*/  ckid; scalar_t__ dwInitialFrames; int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwTotalFrames; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwPaddingGranularity; int /*<<< orphan*/  dwMaxBytesPerSec; int /*<<< orphan*/  dwMicroSecPerFrame; } ;
struct TYPE_29__ {int cb; int /*<<< orphan*/ * lp; } ;
struct TYPE_26__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_28__ {scalar_t__* szName; TYPE_4__ rcFrame; int /*<<< orphan*/  dwSampleSize; int /*<<< orphan*/  dwQuality; int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  dwStart; int /*<<< orphan*/  dwRate; int /*<<< orphan*/  dwScale; int /*<<< orphan*/  dwInitialFrames; int /*<<< orphan*/  wLanguage; int /*<<< orphan*/  wPriority; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
struct TYPE_27__ {int cb; int /*<<< orphan*/ * lp; } ;
struct TYPE_25__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_24__ {scalar_t__ dwScale; size_t dwStreams; int /*<<< orphan*/  dwHeight; int /*<<< orphan*/  dwWidth; int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwMaxBytesPerSec; int /*<<< orphan*/  dwRate; } ;
struct TYPE_23__ {int dwFlags; } ;
struct TYPE_22__ {TYPE_3__ rcFrame; int /*<<< orphan*/  dwSampleSize; int /*<<< orphan*/  dwQuality; int /*<<< orphan*/  dwSuggestedBufferSize; int /*<<< orphan*/  dwLength; int /*<<< orphan*/  dwStart; int /*<<< orphan*/  dwRate; int /*<<< orphan*/  dwScale; int /*<<< orphan*/  dwInitialFrames; int /*<<< orphan*/  wLanguage; int /*<<< orphan*/  wPriority; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  fccHandler; int /*<<< orphan*/  fccType; } ;
struct TYPE_21__ {scalar_t__ dwMoviChunkPos; int dwNextFramePos; scalar_t__ nIdxRecords; int /*<<< orphan*/  hmmio; TYPE_7__ fileextra; TYPE_10__** ppStreams; TYPE_2__ fInfo; scalar_t__ dwInitialFrames; TYPE_1__ ckLastRecord; } ;
struct TYPE_20__ {int cbFormat; int cbHandlerData; TYPE_6__ sInfo; TYPE_5__ extra; int /*<<< orphan*/ * lpHandlerData; int /*<<< orphan*/ * lpFormat; } ;
typedef  TYPE_8__ MainAVIHeader ;
typedef  int /*<<< orphan*/  MainAVIHdr ;
typedef  TYPE_8__ MMCKINFO ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  scalar_t__ LONG ;
typedef  TYPE_10__ IAVIStreamImpl ;
typedef  TYPE_11__ IAVIFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HPSTR ;
typedef  size_t DWORD ;
typedef  TYPE_12__ AVIStreamHeader ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_FILEWRITE ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  AVIFILE_ComputeMoviStart (TYPE_11__*) ; 
 int /*<<< orphan*/  AVIFILE_SaveIndex (TYPE_11__*) ; 
 int /*<<< orphan*/  AVIFILE_UpdateInfo (TYPE_11__*) ; 
 int /*<<< orphan*/  AVI_HEADERSIZE ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMIO_CREATELIST ; 
 int /*<<< orphan*/  MMIO_CREATERIFF ; 
 int MMIO_DIRTY ; 
 int /*<<< orphan*/  MulDiv (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckidAVIMAINHDR ; 
 int /*<<< orphan*/  ckidAVIPADDING ; 
 int /*<<< orphan*/  ckidSTREAMFORMAT ; 
 int /*<<< orphan*/  ckidSTREAMHANDLERDATA ; 
 int /*<<< orphan*/  ckidSTREAMHEADER ; 
 int /*<<< orphan*/  ckidSTREAMNAME ; 
 scalar_t__ formtypeAVI ; 
 scalar_t__ listtypeAVIHEADER ; 
 scalar_t__ listtypeAVIMOVIE ; 
 scalar_t__ listtypeSTREAMHEADER ; 
 int lstrlenW (scalar_t__*) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmioAscend (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioCreateChunk (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmioFlush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmioSeek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mmioWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT AVIFILE_SaveFile(IAVIFileImpl *This)
{
  MainAVIHeader   MainAVIHdr;
  IAVIStreamImpl* pStream;
  MMCKINFO        ckRIFF;
  MMCKINFO        ckLIST1;
  MMCKINFO        ckLIST2;
  MMCKINFO        ck;
  DWORD           nStream;
  DWORD           dwPos;
  HRESULT         hr;

  /* initialize some things */
  if (This->dwMoviChunkPos == 0)
    AVIFILE_ComputeMoviStart(This);

  /* written one record too much? */
  if (This->ckLastRecord.dwFlags & MMIO_DIRTY) {
    This->dwNextFramePos -= 3 * sizeof(DWORD);
    if (This->nIdxRecords > 0)
      This->nIdxRecords--;
  }

  AVIFILE_UpdateInfo(This);

  assert(This->fInfo.dwScale != 0);

  memset(&MainAVIHdr, 0, sizeof(MainAVIHdr));
  MainAVIHdr.dwMicroSecPerFrame    = MulDiv(This->fInfo.dwRate, 1000000,
					    This->fInfo.dwScale);
  MainAVIHdr.dwMaxBytesPerSec      = This->fInfo.dwMaxBytesPerSec;
  MainAVIHdr.dwPaddingGranularity  = AVI_HEADERSIZE;
  MainAVIHdr.dwFlags               = This->fInfo.dwFlags;
  MainAVIHdr.dwTotalFrames         = This->fInfo.dwLength;
  MainAVIHdr.dwInitialFrames       = 0;
  MainAVIHdr.dwStreams             = This->fInfo.dwStreams;
  MainAVIHdr.dwSuggestedBufferSize = This->fInfo.dwSuggestedBufferSize;
  MainAVIHdr.dwWidth               = This->fInfo.dwWidth;
  MainAVIHdr.dwHeight              = This->fInfo.dwHeight;
  MainAVIHdr.dwInitialFrames       = This->dwInitialFrames;

  /* now begin writing ... */
  mmioSeek(This->hmmio, 0, SEEK_SET);

  /* RIFF chunk */
  ckRIFF.cksize  = 0;
  ckRIFF.fccType = formtypeAVI;
  if (mmioCreateChunk(This->hmmio, &ckRIFF, MMIO_CREATERIFF) != S_OK)
    return AVIERR_FILEWRITE;

  /* AVI headerlist */
  ckLIST1.cksize  = 0;
  ckLIST1.fccType = listtypeAVIHEADER;
  if (mmioCreateChunk(This->hmmio, &ckLIST1, MMIO_CREATELIST) != S_OK)
    return AVIERR_FILEWRITE;

  /* MainAVIHeader */
  ck.ckid    = ckidAVIMAINHDR;
  ck.cksize  = sizeof(MainAVIHdr);
  ck.fccType = 0;
  if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioWrite(This->hmmio, (HPSTR)&MainAVIHdr, ck.cksize) != ck.cksize)
    return AVIERR_FILEWRITE;
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* write the headers of each stream into a separate streamheader list */
  for (nStream = 0; nStream < This->fInfo.dwStreams; nStream++) {
    AVIStreamHeader strHdr;

    pStream = This->ppStreams[nStream];

    /* begin the new streamheader list */
    ckLIST2.cksize  = 0;
    ckLIST2.fccType = listtypeSTREAMHEADER;
    if (mmioCreateChunk(This->hmmio, &ckLIST2, MMIO_CREATELIST) != S_OK)
      return AVIERR_FILEWRITE;

    /* create an AVIStreamHeader from the AVSTREAMINFO */
    strHdr.fccType               = pStream->sInfo.fccType;
    strHdr.fccHandler            = pStream->sInfo.fccHandler;
    strHdr.dwFlags               = pStream->sInfo.dwFlags;
    strHdr.wPriority             = pStream->sInfo.wPriority;
    strHdr.wLanguage             = pStream->sInfo.wLanguage;
    strHdr.dwInitialFrames       = pStream->sInfo.dwInitialFrames;
    strHdr.dwScale               = pStream->sInfo.dwScale;
    strHdr.dwRate                = pStream->sInfo.dwRate;
    strHdr.dwStart               = pStream->sInfo.dwStart;
    strHdr.dwLength              = pStream->sInfo.dwLength;
    strHdr.dwSuggestedBufferSize = pStream->sInfo.dwSuggestedBufferSize;
    strHdr.dwQuality             = pStream->sInfo.dwQuality;
    strHdr.dwSampleSize          = pStream->sInfo.dwSampleSize;
    strHdr.rcFrame.left          = pStream->sInfo.rcFrame.left;
    strHdr.rcFrame.top           = pStream->sInfo.rcFrame.top;
    strHdr.rcFrame.right         = pStream->sInfo.rcFrame.right;
    strHdr.rcFrame.bottom        = pStream->sInfo.rcFrame.bottom;

    /* now write the AVIStreamHeader */
    ck.ckid   = ckidSTREAMHEADER;
    ck.cksize = sizeof(strHdr);
    if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
    if (mmioWrite(This->hmmio, (HPSTR)&strHdr, ck.cksize) != ck.cksize)
      return AVIERR_FILEWRITE;
    if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;

    /* ... the hopefully ever present streamformat ... */
    ck.ckid   = ckidSTREAMFORMAT;
    ck.cksize = pStream->cbFormat;
    if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
    if (pStream->lpFormat != NULL && ck.cksize > 0) {
      if (mmioWrite(This->hmmio, pStream->lpFormat, ck.cksize) != ck.cksize)
	return AVIERR_FILEWRITE;
    }
    if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;

    /* ... some optional existing handler data ... */
    if (pStream->lpHandlerData != NULL && pStream->cbHandlerData > 0) {
      ck.ckid   = ckidSTREAMHANDLERDATA;
      ck.cksize = pStream->cbHandlerData;
      if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
      if (mmioWrite(This->hmmio, pStream->lpHandlerData, ck.cksize) != ck.cksize)
	return AVIERR_FILEWRITE;
      if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
    }

    /* ... some optional additional extra chunk for this stream ... */
    if (pStream->extra.lp != NULL && pStream->extra.cb > 0) {
      /* the chunk header(s) are already in the structure */
      if (mmioWrite(This->hmmio, pStream->extra.lp, pStream->extra.cb) != pStream->extra.cb)
	return AVIERR_FILEWRITE;
    }

    /* ... an optional name for this stream ... */
    if (pStream->sInfo.szName[0]) {
      LPSTR str;

      ck.ckid   = ckidSTREAMNAME;
      ck.cksize = lstrlenW(pStream->sInfo.szName) + 1;
      if (ck.cksize & 1) /* align */
	ck.cksize++;
      if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;

      /* the streamname must be saved in ASCII not Unicode */
      str = HeapAlloc(GetProcessHeap(), 0, ck.cksize);
      if (str == NULL)
	return AVIERR_MEMORY;
      WideCharToMultiByte(CP_ACP, 0, pStream->sInfo.szName, -1, str,
			  ck.cksize, NULL, NULL);

      if (mmioWrite(This->hmmio, str, ck.cksize) != ck.cksize) {
	HeapFree(GetProcessHeap(), 0, str);	
	return AVIERR_FILEWRITE;
      }

      HeapFree(GetProcessHeap(), 0, str);
      if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
    }

    /* close streamheader list for this stream */
    if (mmioAscend(This->hmmio, &ckLIST2, 0) != S_OK)
      return AVIERR_FILEWRITE;
  } /* for (0 <= nStream < MainAVIHdr.dwStreams) */

  /* close the aviheader list */
  if (mmioAscend(This->hmmio, &ckLIST1, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* check for padding to pre-guessed 'movi'-chunk position */
  dwPos = ckLIST1.dwDataOffset + ckLIST1.cksize;
  if (This->dwMoviChunkPos - 2 * sizeof(DWORD) > dwPos) {
    ck.ckid   = ckidAVIPADDING;
    ck.cksize = This->dwMoviChunkPos - dwPos - 4 * sizeof(DWORD);
    assert((LONG)ck.cksize >= 0);

    if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
    if (mmioSeek(This->hmmio, ck.cksize, SEEK_CUR) == -1)
      return AVIERR_FILEWRITE;
    if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
  }

  /* now write the 'movi' chunk */
  mmioSeek(This->hmmio, This->dwMoviChunkPos - 2 * sizeof(DWORD), SEEK_SET);
  ckLIST1.cksize  = 0;
  ckLIST1.fccType = listtypeAVIMOVIE;
  if (mmioCreateChunk(This->hmmio, &ckLIST1, MMIO_CREATELIST) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioSeek(This->hmmio, This->dwNextFramePos, SEEK_SET) == -1)
    return AVIERR_FILEWRITE;
  if (mmioAscend(This->hmmio, &ckLIST1, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* write 'idx1' chunk */
  hr = AVIFILE_SaveIndex(This);
  if (FAILED(hr))
    return hr;

  /* write optional extra file chunks */
  if (This->fileextra.lp != NULL && This->fileextra.cb > 0) {
    /* as for the streams, are the chunk header(s) in the structure */
    if (mmioWrite(This->hmmio, This->fileextra.lp, This->fileextra.cb) != This->fileextra.cb)
      return AVIERR_FILEWRITE;
  }

  /* close RIFF chunk */
  if (mmioAscend(This->hmmio, &ckRIFF, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* add some JUNK at end for bad parsers */
  memset(&ckRIFF, 0, sizeof(ckRIFF));
  mmioWrite(This->hmmio, (HPSTR)&ckRIFF, sizeof(ckRIFF));
  mmioFlush(This->hmmio, 0);

  return AVIERR_OK;
}