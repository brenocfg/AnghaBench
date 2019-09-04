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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  scalar_t__ LONG ;
typedef  void* INT ;

/* Variables and functions */
 scalar_t__ CP_UNICODE ; 
 void* MultiByteToWideChar (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 void* lstrlenW (int /*<<< orphan*/ *) ; 

LPWSTR ME_ToUnicode(LONG codepage, LPVOID psz, INT *len)
{
  *len = 0;
  if (!psz) return NULL;

  if (codepage == CP_UNICODE)
  {
    *len = lstrlenW(psz);
    return psz;
  }
  else {
    WCHAR *tmp;
    int nChars = MultiByteToWideChar(codepage, 0, psz, -1, NULL, 0);

    if(!nChars) return NULL;

    if((tmp = heap_alloc( nChars * sizeof(WCHAR) )) != NULL)
      *len = MultiByteToWideChar(codepage, 0, psz, -1, tmp, nChars) - 1;
    return tmp;
  }
}