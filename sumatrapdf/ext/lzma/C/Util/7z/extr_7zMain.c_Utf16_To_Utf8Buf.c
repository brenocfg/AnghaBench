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
typedef  int /*<<< orphan*/  UInt16 ;
struct TYPE_4__ {scalar_t__* data; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CBuf ;
typedef  scalar_t__ Bool ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_EnsureSize (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  SZ_ERROR_FAIL ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 
 int /*<<< orphan*/  SZ_OK ; 
 scalar_t__ Utf16_To_Utf8 (scalar_t__*,size_t*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static SRes Utf16_To_Utf8Buf(CBuf *dest, const UInt16 *src, size_t srcLen)
{
  size_t destLen = 0;
  Bool res;
  Utf16_To_Utf8(NULL, &destLen, src, srcLen);
  destLen += 1;
  if (!Buf_EnsureSize(dest, destLen))
    return SZ_ERROR_MEM;
  res = Utf16_To_Utf8(dest->data, &destLen, src, srcLen);
  dest->data[destLen] = 0;
  return res ? SZ_OK : SZ_ERROR_FAIL;
}