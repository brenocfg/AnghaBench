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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ **) ; 
 unsigned char* WdtpInterfacePointer_UserUnmarshal (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *interface_variant_unmarshal(ULONG *pFlags, unsigned char *Buffer,
                                                  REFIID riid, IUnknown **ppunk)
{
  DWORD ptr;
  
  TRACE("pFlags=%d, Buffer=%p, ppUnk=%p\n", *pFlags, Buffer, ppunk);

  /* skip pointer part itself */
  ptr = *(DWORD*)Buffer;
  Buffer += sizeof(DWORD);

  if(!ptr)
      return Buffer;

  return WdtpInterfacePointer_UserUnmarshal(pFlags, Buffer, ppunk, riid);
}