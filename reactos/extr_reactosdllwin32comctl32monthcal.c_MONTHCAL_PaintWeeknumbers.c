#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_15__ {int dwStyle; size_t firstDay; TYPE_1__* calendars; int /*<<< orphan*/ * pens; scalar_t__ height_increment; int /*<<< orphan*/ * colors; int /*<<< orphan*/ * brushes; } ;
struct TYPE_14__ {scalar_t__ bottom; int /*<<< orphan*/  right; scalar_t__ top; } ;
struct TYPE_13__ {size_t wDay; int wMonth; int wYear; } ;
struct TYPE_12__ {TYPE_3__ weeknums; TYPE_2__ month; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_4__ MONTHCAL_INFO ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 size_t BrushMonth ; 
 int DT_CENTER ; 
 int DT_SINGLELINE ; 
 int DT_VCENTER ; 
 int /*<<< orphan*/  DrawTextW (int /*<<< orphan*/ ,char*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_IFIRSTWEEKOFYEAR ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t MCSC_TITLEBK ; 
 int MCS_WEEKNUMBERS ; 
 size_t MONTHCAL_CalculateDayOfWeek (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_GetMinDate (TYPE_4__ const*,TYPE_2__*) ; 
 scalar_t__ MONTHCAL_MonthLength (size_t,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t PenText ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,size_t) ; 
 size_t atoiW (char*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,size_t) ; 

__attribute__((used)) static void MONTHCAL_PaintWeeknumbers(const MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps, INT calIdx)
{
  const SYSTEMTIME *date = &infoPtr->calendars[calIdx].month;
  static const WCHAR fmt_weekW[] = { '%','d',0 };
  INT mindays, weeknum, weeknum1, startofprescal;
  INT i, prev_month;
  SYSTEMTIME st;
  WCHAR buf[80];
  HPEN old_pen;
  RECT r;

  if (!(infoPtr->dwStyle & MCS_WEEKNUMBERS)) return;

  MONTHCAL_GetMinDate(infoPtr, &st);
  startofprescal = st.wDay;
  st = *date;

  prev_month = date->wMonth - 1;
  if(prev_month == 0) prev_month = 12;

  /*
     Rules what week to call the first week of a new year:
     LOCALE_IFIRSTWEEKOFYEAR == 0 (e.g US?):
     The week containing Jan 1 is the first week of year
     LOCALE_IFIRSTWEEKOFYEAR == 2 (e.g. Germany):
     First week of year must contain 4 days of the new year
     LOCALE_IFIRSTWEEKOFYEAR == 1  (what countries?)
     The first week of the year must contain only days of the new year
  */
  GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_IFIRSTWEEKOFYEAR, buf, ARRAY_SIZE(buf));
  weeknum = atoiW(buf);
  switch (weeknum)
  {
    case 1: mindays = 6;
	break;
    case 2: mindays = 3;
	break;
    case 0: mindays = 0;
        break;
    default:
        WARN("Unknown LOCALE_IFIRSTWEEKOFYEAR value %d, defaulting to 0\n", weeknum);
	mindays = 0;
  }

  if (date->wMonth == 1)
  {
    /* calculate all those exceptions for January */
    st.wDay = st.wMonth = 1;
    weeknum1 = MONTHCAL_CalculateDayOfWeek(&st, FALSE);
    if ((infoPtr->firstDay - weeknum1) % 7 > mindays)
	weeknum = 1;
    else
    {
	weeknum = 0;
	for(i = 0; i < 11; i++)
	   weeknum += MONTHCAL_MonthLength(i+1, date->wYear - 1);

	weeknum  += startofprescal + 7;
	weeknum  /= 7;
	st.wYear -= 1;
	weeknum1  = MONTHCAL_CalculateDayOfWeek(&st, FALSE);
	if ((infoPtr->firstDay - weeknum1) % 7 > mindays) weeknum++;
    }
  }
  else
  {
    weeknum = 0;
    for(i = 0; i < prev_month - 1; i++)
	weeknum += MONTHCAL_MonthLength(i+1, date->wYear);

    weeknum += startofprescal + 7;
    weeknum /= 7;
    st.wDay = st.wMonth = 1;
    weeknum1 = MONTHCAL_CalculateDayOfWeek(&st, FALSE);
    if ((infoPtr->firstDay - weeknum1) % 7 > mindays) weeknum++;
  }

  r = infoPtr->calendars[calIdx].weeknums;

  /* erase whole week numbers area */
  FillRect(hdc, &r, infoPtr->brushes[BrushMonth]);
  SetTextColor(hdc, infoPtr->colors[MCSC_TITLEBK]);

  /* reduce rectangle to one week number */
  r.bottom = r.top + infoPtr->height_increment;

  for(i = 0; i < 6; i++) {
    if((i == 0) && (weeknum > 50))
    {
        wsprintfW(buf, fmt_weekW, weeknum);
        weeknum = 0;
    }
    else if((i == 5) && (weeknum > 47))
    {
	wsprintfW(buf, fmt_weekW, 1);
    }
    else
	wsprintfW(buf, fmt_weekW, weeknum + i);

    DrawTextW(hdc, buf, -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    OffsetRect(&r, 0, infoPtr->height_increment);
  }

  /* line separator for week numbers column */
  old_pen = SelectObject(hdc, infoPtr->pens[PenText]);
  MoveToEx(hdc, infoPtr->calendars[calIdx].weeknums.right, infoPtr->calendars[calIdx].weeknums.top + 3 , NULL);
  LineTo(hdc,   infoPtr->calendars[calIdx].weeknums.right, infoPtr->calendars[calIdx].weeknums.bottom);
  SelectObject(hdc, old_pen);
}