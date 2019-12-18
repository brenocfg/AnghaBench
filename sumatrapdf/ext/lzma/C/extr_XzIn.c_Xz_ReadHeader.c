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
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  CXzStreamFlags ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_NO_ARCHIVE ; 
 int /*<<< orphan*/  SeqInStream_Read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XZ_SIG ; 
 int /*<<< orphan*/  XZ_SIG_SIZE ; 
 int XZ_STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  Xz_ParseHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SRes Xz_ReadHeader(CXzStreamFlags *p, ISeqInStream *inStream)
{
  Byte sig[XZ_STREAM_HEADER_SIZE];
  RINOK(SeqInStream_Read2(inStream, sig, XZ_STREAM_HEADER_SIZE, SZ_ERROR_NO_ARCHIVE));
  if (memcmp(sig, XZ_SIG, XZ_SIG_SIZE) != 0)
    return SZ_ERROR_NO_ARCHIVE;
  return Xz_ParseHeader(p, sig);
}