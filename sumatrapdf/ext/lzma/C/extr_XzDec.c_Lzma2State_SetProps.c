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
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  CLzma2Dec ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Dec_Allocate (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 

__attribute__((used)) static SRes Lzma2State_SetProps(void *pp, const Byte *props, size_t propSize, ISzAlloc *alloc)
{
  if (propSize != 1)
    return SZ_ERROR_UNSUPPORTED;
  return Lzma2Dec_Allocate((CLzma2Dec *)pp, props[0], alloc);
}