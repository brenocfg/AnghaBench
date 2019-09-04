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
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

LPSTR RPCRT4_strndupA(LPCSTR src, INT slen)
{
  DWORD len;
  LPSTR s;
  if (!src) return NULL;
  if (slen == -1) slen = strlen(src);
  len = slen;
  s = HeapAlloc(GetProcessHeap(), 0, len+1);
  memcpy(s, src, len);
  s[len] = 0;
  return s;
}