#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_7__ {char* decimal_point; char* thousands_sep; char* grouping; TYPE_1__ lc; int /*<<< orphan*/  cp; } ;
typedef  TYPE_2__ _Locale_numeric_t ;
typedef  int /*<<< orphan*/  _Locale_lcid_t ;

/* Variables and functions */
 int GetLocaleInfoA (scalar_t__,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ INVARIANT_LCID ; 
 int /*<<< orphan*/  LOCALE_SDECIMAL ; 
 int /*<<< orphan*/  LOCALE_SGROUPING ; 
 int /*<<< orphan*/  LOCALE_STHOUSAND ; 
 int _STLP_LOC_NO_MEMORY ; 
 int _STLP_LOC_UNKNOWN_NAME ; 
 int /*<<< orphan*/  __FixGrouping (char*) ; 
 int __GetLCIDFromName (char const*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __GetLocaleInfoUsingACP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

_Locale_numeric_t* _Locale_numeric_create(const char * name, _Locale_lcid_t* lc_hint, int *__err_code) {
  wchar_t wbuf[4];
  char *GroupingBuffer;
  int BufferSize;

  _Locale_numeric_t *lnum = (_Locale_numeric_t*)malloc(sizeof(_Locale_numeric_t));
  if (!lnum) { *__err_code = _STLP_LOC_NO_MEMORY; return lnum; }
  memset(lnum, 0, sizeof(_Locale_numeric_t));

  if (__GetLCIDFromName(name, &lnum->lc.id, lnum->cp, lc_hint) == -1)
  { free(lnum); *__err_code = _STLP_LOC_UNKNOWN_NAME; return NULL; }

#if defined (__BORLANDC__)
  if (lnum->lc.id != INVARIANT_LCID) {
#endif
  __GetLocaleInfoUsingACP(lnum->lc.id, lnum->cp, LOCALE_SDECIMAL, lnum->decimal_point, 4, wbuf, 4);
  __GetLocaleInfoUsingACP(lnum->lc.id, lnum->cp, LOCALE_STHOUSAND, lnum->thousands_sep, 4, wbuf, 4);
#if defined (__BORLANDC__)
  }
  else
    lnum->decimal_point[0] = '.';
#endif

  if (lnum->lc.id != INVARIANT_LCID) {
    BufferSize = GetLocaleInfoA(lnum->lc.id, LOCALE_SGROUPING, NULL, 0);
    GroupingBuffer = (char*)malloc(BufferSize);
    if (!GroupingBuffer) { free(lnum); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    GetLocaleInfoA(lnum->lc.id, LOCALE_SGROUPING, GroupingBuffer, BufferSize);
    __FixGrouping(GroupingBuffer);
    lnum->grouping = GroupingBuffer;
  }
  else {
    lnum->grouping = (char*)malloc(1);
    if (!lnum->grouping) { free(lnum); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    lnum->grouping[0] = 0;
  }

  return lnum;
}