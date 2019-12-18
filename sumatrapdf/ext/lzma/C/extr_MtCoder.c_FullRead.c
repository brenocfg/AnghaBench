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
struct TYPE_4__ {int /*<<< orphan*/  (* Read ) (TYPE_1__*,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ISeqInStream ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static SRes FullRead(ISeqInStream *stream, Byte *data, size_t *processedSize)
{
  size_t size = *processedSize;
  *processedSize = 0;
  while (size != 0)
  {
    size_t curSize = size;
    SRes res = stream->Read(stream, data, &curSize);
    *processedSize += curSize;
    data += curSize;
    size -= curSize;
    RINOK(res);
    if (curSize == 0)
      return SZ_OK;
  }
  return SZ_OK;
}