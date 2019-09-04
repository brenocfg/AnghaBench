#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {scalar_t__ cp; TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_ctype_t ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCMAP_LINGUISTIC_CASING ; 
 int LCMAP_UPPERCASE ; 
 int /*<<< orphan*/  LCMapStringA (int /*<<< orphan*/ ,int,char*,int,char*,int) ; 
 int /*<<< orphan*/  MB_PRECOMPOSED ; 
 int /*<<< orphan*/  MultiByteToWideChar (scalar_t__,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int WC_COMPOSITECHECK ; 
 int WC_SEPCHARS ; 
 int /*<<< orphan*/  WideCharToMultiByte (scalar_t__,int,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ __GetDefaultCP (int /*<<< orphan*/ ) ; 

int _Locale_toupper(_Locale_ctype_t* ltype, int c) {
  char buf[2], out_buf[2];
  buf[0] = (char)c; buf[1] = 0;
  if ((UINT)__GetDefaultCP(ltype->lc.id) == ltype->cp) {
    LCMapStringA(ltype->lc.id, LCMAP_LINGUISTIC_CASING | LCMAP_UPPERCASE, buf, 2, out_buf, 2);
    return out_buf[0];
  }
  else {
    wchar_t wbuf[2];
    MultiByteToWideChar(ltype->cp, MB_PRECOMPOSED, buf, 2, wbuf, 2);
    WideCharToMultiByte(__GetDefaultCP(ltype->lc.id), WC_COMPOSITECHECK | WC_SEPCHARS, wbuf, 2, buf, 2, NULL, FALSE);

    LCMapStringA(ltype->lc.id, LCMAP_LINGUISTIC_CASING | LCMAP_UPPERCASE, buf, 2, out_buf, 2);

    MultiByteToWideChar(__GetDefaultCP(ltype->lc.id), MB_PRECOMPOSED, out_buf, 2, wbuf, 2);
    WideCharToMultiByte(ltype->cp, WC_COMPOSITECHECK | WC_SEPCHARS, wbuf, 2, out_buf, 2, NULL, FALSE);
    return out_buf[0];
  }
}