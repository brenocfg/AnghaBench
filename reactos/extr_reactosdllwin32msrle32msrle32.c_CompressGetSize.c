#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/ * LPCBITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  CodecInfo ;

/* Variables and functions */
 scalar_t__ CompressQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  MSRLE32_GetMaxCompressedSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT CompressGetSize(CodecInfo *pi, LPCBITMAPINFOHEADER lpbiIn,
			       LPCBITMAPINFOHEADER lpbiOut)
{
  /* pre-condition */
  assert(pi != NULL);

  TRACE("(%p,%p,%p)\n",pi,lpbiIn,lpbiOut);

  /* check parameter -- need at least one format */
  if (lpbiIn == NULL && lpbiOut == NULL)
    return 0;
  /* check if the given format is supported */
  if (CompressQuery(pi, lpbiIn, lpbiOut) != ICERR_OK)
    return 0;

  /* the worst case is coding the complete image in absolute mode. */
  if (lpbiIn)
    return MSRLE32_GetMaxCompressedSize(lpbiIn);
  else
    return MSRLE32_GetMaxCompressedSize(lpbiOut);
}