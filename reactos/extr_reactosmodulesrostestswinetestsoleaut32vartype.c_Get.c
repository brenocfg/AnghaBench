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
typedef  int /*<<< orphan*/ * LPINTERNAL_BSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */

__attribute__((used)) static inline LPINTERNAL_BSTR Get(const BSTR lpszString)
{
  return lpszString ? (LPINTERNAL_BSTR)((char*)lpszString - sizeof(DWORD)) : NULL;
}