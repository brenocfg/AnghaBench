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
struct TYPE_3__ {int Data1; int Data2; int Data3; int* Data4; } ;
typedef  TYPE_1__ UUID ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char const*,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void write_guid(FILE *f, const char *guid_prefix, const char *name, const UUID *uuid)
{
  if (!uuid) return;
  fprintf(f, "DEFINE_GUID(%s_%s, 0x%08x, 0x%04x, 0x%04x, 0x%02x,0x%02x, 0x%02x,"
        "0x%02x,0x%02x,0x%02x,0x%02x,0x%02x);\n",
        guid_prefix, name, uuid->Data1, uuid->Data2, uuid->Data3, uuid->Data4[0],
        uuid->Data4[1], uuid->Data4[2], uuid->Data4[3], uuid->Data4[4], uuid->Data4[5],
        uuid->Data4[6], uuid->Data4[7]);
}