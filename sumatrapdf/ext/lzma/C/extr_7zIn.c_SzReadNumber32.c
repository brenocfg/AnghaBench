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
typedef  int UInt64 ;
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  CSzData ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzReadNumber (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static SRes SzReadNumber32(CSzData *sd, UInt32 *value)
{
  UInt64 value64;
  RINOK(SzReadNumber(sd, &value64));
  if (value64 >= 0x80000000)
    return SZ_ERROR_UNSUPPORTED;
  if (value64 >= ((UInt64)(1) << ((sizeof(size_t) - 1) * 8 + 2)))
    return SZ_ERROR_UNSUPPORTED;
  *value = (UInt32)value64;
  return SZ_OK;
}