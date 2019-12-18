#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_8__ {scalar_t__ srcPos; void* needInitState; void* needInitProp; scalar_t__ props; int /*<<< orphan*/  enc; } ;
struct TYPE_7__ {size_t (* Write ) (TYPE_1__*,scalar_t__*,size_t) ;} ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ ISeqOutStream ;
typedef  TYPE_2__ CLzma2EncInt ;
typedef  scalar_t__ Byte ;
typedef  int Bool ;

/* Variables and functions */
 void* False ; 
 scalar_t__ LZMA2_CONTROL_COPY_NO_RESET ; 
 scalar_t__ LZMA2_CONTROL_COPY_RESET_DIC ; 
 unsigned int LZMA2_CONTROL_LZMA ; 
 int LZMA2_COPY_CHUNK_SIZE ; 
 int /*<<< orphan*/  LZMA2_PACK_SIZE_MAX ; 
 int LZMA2_UNPACK_SIZE_MAX ; 
 scalar_t__ LzmaEnc_CodeOneMemBlock (int /*<<< orphan*/ ,void*,scalar_t__*,size_t*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ LzmaEnc_GetCurBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaEnc_RestoreState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LzmaEnc_SaveState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRF (int /*<<< orphan*/ ) ; 
 scalar_t__ SZ_ERROR_OUTPUT_EOF ; 
 scalar_t__ SZ_ERROR_WRITE ; 
 scalar_t__ SZ_OK ; 
 int True ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t stub1 (TYPE_1__*,scalar_t__*,size_t) ; 
 size_t stub2 (TYPE_1__*,scalar_t__*,size_t) ; 

__attribute__((used)) static SRes Lzma2EncInt_EncodeSubblock(CLzma2EncInt *p, Byte *outBuf,
    size_t *packSizeRes, ISeqOutStream *outStream)
{
  size_t packSizeLimit = *packSizeRes;
  size_t packSize = packSizeLimit;
  UInt32 unpackSize = LZMA2_UNPACK_SIZE_MAX;
  unsigned lzHeaderSize = 5 + (p->needInitProp ? 1 : 0);
  Bool useCopyBlock;
  SRes res;

  *packSizeRes = 0;
  if (packSize < lzHeaderSize)
    return SZ_ERROR_OUTPUT_EOF;
  packSize -= lzHeaderSize;
  
  LzmaEnc_SaveState(p->enc);
  res = LzmaEnc_CodeOneMemBlock(p->enc, p->needInitState,
      outBuf + lzHeaderSize, &packSize, LZMA2_PACK_SIZE_MAX, &unpackSize);
  
  PRF(printf("\npackSize = %7d unpackSize = %7d  ", packSize, unpackSize));

  if (unpackSize == 0)
    return res;

  if (res == SZ_OK)
    useCopyBlock = (packSize + 2 >= unpackSize || packSize > (1 << 16));
  else
  {
    if (res != SZ_ERROR_OUTPUT_EOF)
      return res;
    res = SZ_OK;
    useCopyBlock = True;
  }

  if (useCopyBlock)
  {
    size_t destPos = 0;
    PRF(printf("################# COPY           "));
    while (unpackSize > 0)
    {
      UInt32 u = (unpackSize < LZMA2_COPY_CHUNK_SIZE) ? unpackSize : LZMA2_COPY_CHUNK_SIZE;
      if (packSizeLimit - destPos < u + 3)
        return SZ_ERROR_OUTPUT_EOF;
      outBuf[destPos++] = (Byte)(p->srcPos == 0 ? LZMA2_CONTROL_COPY_RESET_DIC : LZMA2_CONTROL_COPY_NO_RESET);
      outBuf[destPos++] = (Byte)((u - 1) >> 8);
      outBuf[destPos++] = (Byte)(u - 1);
      memcpy(outBuf + destPos, LzmaEnc_GetCurBuf(p->enc) - unpackSize, u);
      unpackSize -= u;
      destPos += u;
      p->srcPos += u;
      if (outStream)
      {
        *packSizeRes += destPos;
        if (outStream->Write(outStream, outBuf, destPos) != destPos)
          return SZ_ERROR_WRITE;
        destPos = 0;
      }
      else
        *packSizeRes = destPos;
      /* needInitState = True; */
    }
    LzmaEnc_RestoreState(p->enc);
    return SZ_OK;
  }
  {
    size_t destPos = 0;
    UInt32 u = unpackSize - 1;
    UInt32 pm = (UInt32)(packSize - 1);
    unsigned mode = (p->srcPos == 0) ? 3 : (p->needInitState ? (p->needInitProp ? 2 : 1) : 0);

    PRF(printf("               "));

    outBuf[destPos++] = (Byte)(LZMA2_CONTROL_LZMA | (mode << 5) | ((u >> 16) & 0x1F));
    outBuf[destPos++] = (Byte)(u >> 8);
    outBuf[destPos++] = (Byte)u;
    outBuf[destPos++] = (Byte)(pm >> 8);
    outBuf[destPos++] = (Byte)pm;
    
    if (p->needInitProp)
      outBuf[destPos++] = p->props;
    
    p->needInitProp = False;
    p->needInitState = False;
    destPos += packSize;
    p->srcPos += unpackSize;

    if (outStream)
      if (outStream->Write(outStream, outBuf, destPos) != destPos)
        return SZ_ERROR_WRITE;
    *packSizeRes = destPos;
    return SZ_OK;
  }
}