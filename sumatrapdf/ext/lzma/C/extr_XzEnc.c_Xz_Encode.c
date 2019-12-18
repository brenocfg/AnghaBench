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
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  int /*<<< orphan*/  CXzStream ;
typedef  int /*<<< orphan*/  CXzProps ;
typedef  int /*<<< orphan*/  CLzma2WithFilters ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2WithFilters_Construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Lzma2WithFilters_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lzma2WithFilters_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ Xz_Compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Xz_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Xz_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_Alloc ; 
 int /*<<< orphan*/  g_BigAlloc ; 

SRes Xz_Encode(ISeqOutStream *outStream, ISeqInStream *inStream,
    const CXzProps *props, ICompressProgress *progress)
{
  SRes res;
  CXzStream xz;
  CLzma2WithFilters lzmaf;
  Xz_Construct(&xz);
  Lzma2WithFilters_Construct(&lzmaf, &g_Alloc, &g_BigAlloc);
  res = Lzma2WithFilters_Create(&lzmaf);
  if (res == SZ_OK)
    res = Xz_Compress(&xz, &lzmaf, outStream, inStream, props, progress);
  Lzma2WithFilters_Free(&lzmaf);
  Xz_Free(&xz, &g_Alloc);
  return res;
}