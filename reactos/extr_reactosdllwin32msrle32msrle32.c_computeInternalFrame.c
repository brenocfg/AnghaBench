#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int WORD ;
typedef  size_t UINT ;
struct TYPE_7__ {unsigned int* pCurFrame; } ;
struct TYPE_6__ {int biWidth; scalar_t__ biClrUsed; int biSize; scalar_t__ biHeight; int biBitCount; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  unsigned int* LPWORD ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  scalar_t__ LONG ;
typedef  unsigned int DWORD ;
typedef  TYPE_2__ CodecInfo ;
typedef  size_t BYTE ;

/* Variables and functions */
 unsigned int DIBWIDTHBYTES (TYPE_1__) ; 
 unsigned int Intensity (int /*<<< orphan*/  const) ; 
 unsigned int WIDTHBYTES (unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 

void computeInternalFrame(CodecInfo *pi, LPCBITMAPINFOHEADER lpbiIn, const BYTE *lpIn)
{
  WORD   wIntensityTbl[256];
  DWORD  lInLine, lOutLine;
  LPWORD lpOut;
  UINT   i;
  LONG   y;

  /* pre-conditions */
  assert(pi != NULL && lpbiIn != NULL && lpIn != NULL);
  assert(pi->pCurFrame != NULL);

  lInLine  = DIBWIDTHBYTES(*lpbiIn);
  lOutLine = WIDTHBYTES((WORD)lpbiIn->biWidth * 8u * sizeof(WORD)) / 2u;
  lpOut    = pi->pCurFrame;

  assert(lpbiIn->biClrUsed != 0);

  {
    const RGBQUAD *lp =
      (const RGBQUAD *)((const BYTE*)lpbiIn + lpbiIn->biSize);

    for (i = 0; i < lpbiIn->biClrUsed; i++)
      wIntensityTbl[i] = Intensity(lp[i]);
  }

  for (y = 0; y < lpbiIn->biHeight; y++) {
    LONG x;

    switch (lpbiIn->biBitCount) {
    case 1:
      for (x = 0; x < lpbiIn->biWidth / 8; x++) {
	for (i = 0; i < 7; i++)
	  lpOut[8 * x + i] = wIntensityTbl[(lpIn[x] >> (7 - i)) & 1];
      }
      break;
    case 4:
      for (x = 0; x < lpbiIn->biWidth / 2; x++) {
	lpOut[2 * x + 0] = wIntensityTbl[(lpIn[x] >> 4)];
	lpOut[2 * x + 1] = wIntensityTbl[(lpIn[x] & 0x0F)];
      }
      break;
    case 8:
      for (x = 0; x < lpbiIn->biWidth; x++)
	lpOut[x] = wIntensityTbl[lpIn[x]];
      break;
    }

    lpIn  += lInLine;
    lpOut += lOutLine;
  }
}