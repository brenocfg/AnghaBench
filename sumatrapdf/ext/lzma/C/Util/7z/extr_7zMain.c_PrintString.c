#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UInt16 ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  scalar_t__ SRes ;
typedef  TYPE_1__ CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Buf_Init (TYPE_1__*) ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ Utf16_To_Char (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_Alloc ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static SRes PrintString(const UInt16 *s)
{
  CBuf buf;
  SRes res;
  Buf_Init(&buf);
  res = Utf16_To_Char(&buf, s, 0);
  if (res == SZ_OK)
    fputs((const char *)buf.data, stdout);
  Buf_Free(&buf, &g_Alloc);
  return res;
}