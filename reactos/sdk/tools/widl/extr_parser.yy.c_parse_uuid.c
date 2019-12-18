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
struct TYPE_4__ {void** Data4; void* Data3; void* Data2; void* Data1; } ;
typedef  TYPE_1__ UUID ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 void* strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* xmalloc (int) ; 

UUID *parse_uuid(const char *u)
{
  UUID* uuid = xmalloc(sizeof(UUID));
  char b[3];
  /* it would be nice to use UuidFromStringA */
  uuid->Data1 = strtoul(u, NULL, 16);
  uuid->Data2 = strtoul(u+9, NULL, 16);
  uuid->Data3 = strtoul(u+14, NULL, 16);
  b[2] = 0;
  memcpy(b, u+19, 2); uuid->Data4[0] = strtoul(b, NULL, 16);
  memcpy(b, u+21, 2); uuid->Data4[1] = strtoul(b, NULL, 16);
  memcpy(b, u+24, 2); uuid->Data4[2] = strtoul(b, NULL, 16);
  memcpy(b, u+26, 2); uuid->Data4[3] = strtoul(b, NULL, 16);
  memcpy(b, u+28, 2); uuid->Data4[4] = strtoul(b, NULL, 16);
  memcpy(b, u+30, 2); uuid->Data4[5] = strtoul(b, NULL, 16);
  memcpy(b, u+32, 2); uuid->Data4[6] = strtoul(b, NULL, 16);
  memcpy(b, u+34, 2); uuid->Data4[7] = strtoul(b, NULL, 16);
  return uuid;
}