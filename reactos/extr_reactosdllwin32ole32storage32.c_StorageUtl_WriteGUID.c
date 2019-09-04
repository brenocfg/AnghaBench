#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {int /*<<< orphan*/  Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  StorageUtl_WriteDWord (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageUtl_WriteWord (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void StorageUtl_WriteGUID(BYTE* buffer, ULONG offset, const GUID* value)
{
  StorageUtl_WriteDWord(buffer, offset,   value->Data1);
  StorageUtl_WriteWord(buffer,  offset+4, value->Data2);
  StorageUtl_WriteWord(buffer,  offset+6, value->Data3);

  memcpy(buffer+offset+8, value->Data4, sizeof(value->Data4));
}