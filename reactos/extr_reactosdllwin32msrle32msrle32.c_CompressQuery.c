#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ fccHandler; } ;
struct TYPE_8__ {int biBitCount; int biWidth; scalar_t__ biHeight; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  TYPE_2__ CodecInfo ;

/* Variables and functions */
 scalar_t__ FOURCC_RLE4 ; 
 int /*<<< orphan*/  ICERR_BADFORMAT ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  ICERR_UNSUPPORTED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isSupportedDIB (TYPE_1__*) ; 
 int /*<<< orphan*/  isSupportedMRLE (TYPE_1__*) ; 

__attribute__((used)) static LRESULT CompressQuery(const CodecInfo *pi, LPCBITMAPINFOHEADER lpbiIn,
			     LPCBITMAPINFOHEADER lpbiOut)
{
  /* pre-condition */
  assert(pi != NULL);

  /* need at least one format */
  if (lpbiIn == NULL && lpbiOut == NULL)
    return ICERR_BADPARAM;

  /* check input format if given */
  if (lpbiIn != NULL) {
    if (!isSupportedDIB(lpbiIn))
      return ICERR_BADFORMAT;

    /* for 4-bit need an even width */
    if (lpbiIn->biBitCount <= 4 && (lpbiIn->biWidth % 2))
      return ICERR_BADFORMAT;

    if (pi->fccHandler == FOURCC_RLE4 && lpbiIn->biBitCount > 4)
      return ICERR_UNSUPPORTED;
    else if (lpbiIn->biBitCount > 8)
      return ICERR_UNSUPPORTED;
  }

  /* check output format if given */
  if (lpbiOut != NULL) {
    if (!isSupportedMRLE(lpbiOut))
      return ICERR_BADFORMAT;

    if (lpbiIn != NULL) {
      if (lpbiIn->biWidth  != lpbiOut->biWidth)
	return ICERR_UNSUPPORTED;
      if (lpbiIn->biHeight != lpbiOut->biHeight)
	return ICERR_UNSUPPORTED;
      if (lpbiIn->biBitCount > lpbiOut->biBitCount)
	return ICERR_UNSUPPORTED;
    }
  }

  return ICERR_OK;
}