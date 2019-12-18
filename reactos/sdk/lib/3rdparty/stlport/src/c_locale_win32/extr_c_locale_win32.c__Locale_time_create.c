#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int id; } ;
struct TYPE_8__ {char** month; char** abbrev_month; char** dayofweek; char** abbrev_dayofweek; char* date_format; char* long_date_format; char* time_format; char* date_time_format; char* long_date_time_format; char* am; char* pm; int /*<<< orphan*/  cp; TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_time_t ;
typedef  int /*<<< orphan*/  _Locale_lcid_t ;

/* Variables and functions */
 int GetLocaleInfoA (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INVARIANT_LCID ; 
 int LOCALE_S1159 ; 
 int LOCALE_S2359 ; 
 int LOCALE_SABBREVDAYNAME1 ; 
 int LOCALE_SABBREVDAYNAME7 ; 
 int LOCALE_SABBREVMONTHNAME1 ; 
 int LOCALE_SABBREVMONTHNAME12 ; 
 int LOCALE_SDAYNAME1 ; 
 int LOCALE_SDAYNAME7 ; 
 int LOCALE_SLONGDATE ; 
 int LOCALE_SMONTHNAME1 ; 
 int LOCALE_SMONTHNAME12 ; 
 int LOCALE_SSHORTDATE ; 
 int LOCALE_STIMEFORMAT ; 
 int /*<<< orphan*/  _Locale_time_destroy (TYPE_2__*) ; 
 int _STLP_LOC_NO_MEMORY ; 
 int _STLP_LOC_UNKNOWN_NAME ; 
 int /*<<< orphan*/  _STLP_STRCAT (char*,size_t,char*) ; 
 int /*<<< orphan*/  _STLP_STRCPY (char*,size_t,char*) ; 
 int __ConvertDate (char*,char*,int) ; 
 int __ConvertTime (char*,char*,int) ; 
 int __GetLCIDFromName (char const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __GetLocaleInfoUsingACP (int,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

_Locale_time_t* _Locale_time_create(const char * name, _Locale_lcid_t* lc_hint, int *__err_code) {
  int size, month, dayofweek;
  size_t length;
  char fmt80[80];
  wchar_t wbuf80[80];

  _Locale_time_t *ltime = (_Locale_time_t*)malloc(sizeof(_Locale_time_t));
  
  if (!ltime) { *__err_code = _STLP_LOC_NO_MEMORY; return ltime; }
  memset(ltime, 0, sizeof(_Locale_time_t));

  if (__GetLCIDFromName(name, &ltime->lc.id, ltime->cp, lc_hint) == -1)
  { free(ltime); *__err_code = _STLP_LOC_UNKNOWN_NAME; return NULL; }

#if defined (__BORLANDC__)
  if ( ltime->lc.id == INVARIANT_LCID && name[0] == 'C' && name[1] == 0 )
  { ltime->lc.id = 0x409; }
#endif

  for (month = LOCALE_SMONTHNAME1; month <= LOCALE_SMONTHNAME12; ++month) { /* Small hack :-) */
    size = GetLocaleInfoA(ltime->lc.id, month, NULL, 0);
    ltime->month[month - LOCALE_SMONTHNAME1] = (char*)malloc(size);
    if (!ltime->month[month - LOCALE_SMONTHNAME1])
    { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, month, ltime->month[month - LOCALE_SMONTHNAME1], size, wbuf80, 80);
  }

  for (month = LOCALE_SABBREVMONTHNAME1; month <= LOCALE_SABBREVMONTHNAME12; ++month) {
    size = GetLocaleInfoA(ltime->lc.id, month, NULL, 0);
    ltime->abbrev_month[month - LOCALE_SABBREVMONTHNAME1] = (char*)malloc(size);
    if (!ltime->abbrev_month[month - LOCALE_SABBREVMONTHNAME1])
    { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, month, ltime->abbrev_month[month - LOCALE_SABBREVMONTHNAME1], size, wbuf80, 80);
  }

  for (dayofweek = LOCALE_SDAYNAME1; dayofweek <= LOCALE_SDAYNAME7; ++dayofweek) {
    int dayindex = ( dayofweek != LOCALE_SDAYNAME7 ) ? dayofweek - LOCALE_SDAYNAME1 + 1 : 0;
    size = GetLocaleInfoA(ltime->lc.id, dayofweek, NULL, 0);
    ltime->dayofweek[dayindex] = (char*)malloc(size);
    if (!ltime->dayofweek[dayindex])
    { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, dayofweek, ltime->dayofweek[dayindex], size, wbuf80, 80);
  }

  for (dayofweek = LOCALE_SABBREVDAYNAME1; dayofweek <= LOCALE_SABBREVDAYNAME7; ++dayofweek) {
    int dayindex = ( dayofweek != LOCALE_SABBREVDAYNAME7 ) ? dayofweek - LOCALE_SABBREVDAYNAME1 + 1 : 0;
    size = GetLocaleInfoA(ltime->lc.id, dayofweek, NULL, 0);
    ltime->abbrev_dayofweek[dayindex] = (char*)malloc(size);
    if (!ltime->abbrev_dayofweek[dayindex])
    { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
    __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, dayofweek, ltime->abbrev_dayofweek[dayindex], size, wbuf80, 80);
  }

  __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, LOCALE_SSHORTDATE, fmt80, 80, wbuf80, 80);
  size = __ConvertDate(fmt80, NULL, 0);
  ltime->date_format = (char*)malloc(size);
  if (!ltime->date_format)
  { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
  __ConvertDate(fmt80, ltime->date_format, size);

  __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, LOCALE_SLONGDATE, fmt80, 80, wbuf80, 80);
  size = __ConvertDate(fmt80, NULL, 0);
  ltime->long_date_format = (char*)malloc(size);
  if (!ltime->long_date_format)
  { _Locale_time_destroy(ltime);*__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
  __ConvertDate(fmt80, ltime->long_date_format, size);

  __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, LOCALE_STIMEFORMAT, fmt80, 80, wbuf80, 80);
  size = __ConvertTime(fmt80, NULL, 0);
  ltime->time_format = (char*)malloc(size);
  if (!ltime->time_format)
  { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
  __ConvertTime(fmt80, ltime->time_format, size);

  /* NT doesn't provide this information, we must simulate. */
  length = strlen(ltime->date_format) + strlen(ltime->time_format) + 1 /* space */ + 1 /* trailing 0 */;
  ltime->date_time_format = (char*)malloc(length);
  if (!ltime->date_time_format)
  { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
  _STLP_STRCPY(ltime->date_time_format, length, ltime->date_format);
  _STLP_STRCAT(ltime->date_time_format, length, " ");
  _STLP_STRCAT(ltime->date_time_format, length, ltime->time_format);

  /* NT doesn't provide this information, we must simulate. */
  length = strlen(ltime->long_date_format) + strlen(ltime->time_format) + 1 /* space */ + 1 /* trailing 0 */;
  ltime->long_date_time_format = (char*)malloc(length);
  if (!ltime->long_date_time_format)
  { _Locale_time_destroy(ltime); *__err_code = _STLP_LOC_NO_MEMORY; return NULL; }
  _STLP_STRCPY(ltime->long_date_time_format, length, ltime->long_date_format);
  _STLP_STRCAT(ltime->long_date_time_format, length, " ");
  _STLP_STRCAT(ltime->long_date_time_format, length, ltime->time_format);

  __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, LOCALE_S1159, ltime->am, 9, wbuf80, 80);
  __GetLocaleInfoUsingACP(ltime->lc.id, ltime->cp, LOCALE_S2359, ltime->pm, 9, wbuf80, 80);

  return ltime;
}