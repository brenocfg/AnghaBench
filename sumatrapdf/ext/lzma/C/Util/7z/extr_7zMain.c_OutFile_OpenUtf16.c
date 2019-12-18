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
typedef  int /*<<< orphan*/  WRes ;
typedef  int /*<<< orphan*/  UInt16 ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  CSzFile ;
typedef  TYPE_1__ CBuf ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Buf_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  OutFile_Open (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  OutFile_OpenW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Utf16_To_Char (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  g_Alloc ; 

__attribute__((used)) static WRes OutFile_OpenUtf16(CSzFile *p, const UInt16 *name)
{
  #ifdef USE_WINDOWS_FILE
  return OutFile_OpenW(p, name);
  #else
  CBuf buf;
  WRes res;
  Buf_Init(&buf);
  RINOK(Utf16_To_Char(&buf, name, 1));
  res = OutFile_Open(p, (const char *)buf.data);
  Buf_Free(&buf, &g_Alloc);
  return res;
  #endif
}