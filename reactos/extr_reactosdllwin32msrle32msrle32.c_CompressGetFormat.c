#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int fccHandler; } ;
struct TYPE_14__ {int biSize; int biPlanes; int biBitCount; int biClrUsed; scalar_t__ biClrImportant; int /*<<< orphan*/  biYPelsPerMeter; int /*<<< orphan*/  biXPelsPerMeter; int /*<<< orphan*/  biSizeImage; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
struct TYPE_13__ {int biBitCount; int biClrUsed; int biSize; int /*<<< orphan*/  biYPelsPerMeter; int /*<<< orphan*/  biXPelsPerMeter; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biWidth; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  int LRESULT ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  scalar_t__ LPBYTE ;
typedef  TYPE_2__* LPBITMAPINFOHEADER ;
typedef  TYPE_3__ CodecInfo ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RLE4 ; 
 int /*<<< orphan*/  BI_RLE8 ; 
 scalar_t__ CompressQuery (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
#define  FOURCC_MRLE 131 
#define  FOURCC_RLE 130 
#define  FOURCC_RLE4 129 
#define  FOURCC_RLE8 128 
 int ICERR_BADFORMAT ; 
 int ICERR_BADPARAM ; 
 int ICERR_ERROR ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  MSRLE32_GetMaxCompressedSize (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int min (int,int) ; 

__attribute__((used)) static LRESULT CompressGetFormat(CodecInfo *pi, LPCBITMAPINFOHEADER lpbiIn,
				 LPBITMAPINFOHEADER lpbiOut)
{
  LRESULT size;

  TRACE("(%p,%p,%p)\n",pi,lpbiIn,lpbiOut);

  /* pre-condition */
  assert(pi != NULL);

  /* check parameters -- need at least input format */
  if (lpbiIn == NULL) {
    if (lpbiOut != NULL)
      return ICERR_BADPARAM;
    return 0;
  }

  /* handle unsupported input format */
  if (CompressQuery(pi, lpbiIn, NULL) != ICERR_OK)
    return (lpbiOut == NULL ? ICERR_BADFORMAT : 0);

  assert(0 < lpbiIn->biBitCount && lpbiIn->biBitCount <= 8);

  switch (pi->fccHandler) {
  case FOURCC_RLE4:
    size = 1 << 4;
    break;
  case FOURCC_RLE8:
    size = 1 << 8;
    break;
  case FOURCC_RLE:
  case FOURCC_MRLE:
    size = (lpbiIn->biBitCount <= 4 ? 1 << 4 : 1 << 8);
    break;
  default:
    return ICERR_ERROR;
  }

  if (lpbiIn->biClrUsed != 0)
    size = lpbiIn->biClrUsed;

  size = sizeof(BITMAPINFOHEADER) + size * sizeof(RGBQUAD);

  if (lpbiOut != NULL) {
    lpbiOut->biSize          = sizeof(BITMAPINFOHEADER);
    lpbiOut->biWidth         = lpbiIn->biWidth;
    lpbiOut->biHeight        = lpbiIn->biHeight;
    lpbiOut->biPlanes        = 1;
    if (pi->fccHandler == FOURCC_RLE4 ||
	lpbiIn->biBitCount <= 4) {
      lpbiOut->biCompression = BI_RLE4;
      lpbiOut->biBitCount    = 4;
    } else {
      lpbiOut->biCompression = BI_RLE8;
      lpbiOut->biBitCount    = 8;
    }
    lpbiOut->biSizeImage     = MSRLE32_GetMaxCompressedSize(lpbiOut);
    lpbiOut->biXPelsPerMeter = lpbiIn->biXPelsPerMeter;
    lpbiOut->biYPelsPerMeter = lpbiIn->biYPelsPerMeter;
    if (lpbiIn->biClrUsed == 0)
      size = 1<<lpbiIn->biBitCount;
    else
      size = lpbiIn->biClrUsed;
    lpbiOut->biClrUsed       = min(size, 1 << lpbiOut->biBitCount);
    lpbiOut->biClrImportant  = 0;

    memcpy((LPBYTE)lpbiOut + lpbiOut->biSize,
	   (const BYTE*)lpbiIn + lpbiIn->biSize, lpbiOut->biClrUsed * sizeof(RGBQUAD));

    return ICERR_OK;
  } else
    return size;
}