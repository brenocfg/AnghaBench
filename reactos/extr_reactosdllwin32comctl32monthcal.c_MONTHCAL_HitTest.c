#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int wDay; int /*<<< orphan*/  wYear; scalar_t__ wMonth; } ;
struct TYPE_22__ {int cbSize; int iOffset; TYPE_5__ st; int /*<<< orphan*/  iRow; int /*<<< orphan*/  iCol; int /*<<< orphan*/  rc; void* uHit; int /*<<< orphan*/  pt; } ;
struct TYPE_21__ {TYPE_1__* calendars; int /*<<< orphan*/  titlebtnnext; int /*<<< orphan*/  titlebtnprev; int /*<<< orphan*/  todayrect; } ;
struct TYPE_20__ {int wDay; int /*<<< orphan*/  wYear; scalar_t__ wMonth; } ;
struct TYPE_19__ {int /*<<< orphan*/  days; int /*<<< orphan*/  weeknums; int /*<<< orphan*/  wdays; TYPE_2__ month; int /*<<< orphan*/  title; int /*<<< orphan*/  titleyear; int /*<<< orphan*/  titlemonth; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  TYPE_4__ MCHITTESTINFO ;
typedef  int LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int MCHITTESTINFO_V1_SIZE ; 
 void* MCHT_CALENDARBK ; 
 void* MCHT_CALENDARDATE ; 
 void* MCHT_CALENDARDATENEXT ; 
 void* MCHT_CALENDARDATEPREV ; 
 void* MCHT_CALENDARDAY ; 
 void* MCHT_CALENDARWEEKNUM ; 
 void* MCHT_TITLE ; 
 void* MCHT_TITLEBTNNEXT ; 
 void* MCHT_TITLEBTNPREV ; 
 void* MCHT_TITLEMONTH ; 
 void* MCHT_TITLEYEAR ; 
 void* MCHT_TODAYLINK ; 
 int /*<<< orphan*/  MONTHCAL_CalculateDayOfWeek (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int MONTHCAL_GetCalCount (TYPE_3__ const*) ; 
 int MONTHCAL_GetCalendarFromPoint (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int MONTHCAL_GetDayFromPos (TYPE_3__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayPos (TYPE_3__ const*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetDayRectI (TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MONTHCAL_GetNextMonth (TYPE_5__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetPrevMonth (TYPE_5__*) ; 
 int MONTHCAL_MonthLength (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int fill_hittest_info (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_5__ st_null ; 

__attribute__((used)) static LRESULT
MONTHCAL_HitTest(const MONTHCAL_INFO *infoPtr, MCHITTESTINFO *lpht)
{
  MCHITTESTINFO htinfo;
  SYSTEMTIME *ht_month;
  INT day, calIdx;

  if(!lpht || lpht->cbSize < MCHITTESTINFO_V1_SIZE) return -1;

  htinfo.st = st_null;

  /* we should preserve passed fields if hit area doesn't need them */
  if (lpht->cbSize == sizeof(MCHITTESTINFO))
    memcpy(&htinfo.rc, &lpht->rc, sizeof(MCHITTESTINFO) - MCHITTESTINFO_V1_SIZE);

  /* guess in what calendar we are */
  calIdx = MONTHCAL_GetCalendarFromPoint(infoPtr, &lpht->pt);
  if (calIdx == -1)
  {
    if (PtInRect(&infoPtr->todayrect, lpht->pt))
    {
      htinfo.uHit = MCHT_TODAYLINK;
      htinfo.rc = infoPtr->todayrect;
    }
    else
      /* outside of calendar area? What's left must be background :-) */
      htinfo.uHit = MCHT_CALENDARBK;

    return fill_hittest_info(&htinfo, lpht);
  }

  /* are we in the header? */
  if (PtInRect(&infoPtr->calendars[calIdx].title, lpht->pt)) {
    /* FIXME: buttons hittesting could be optimized cause maximum
              two calendars have buttons */
    if (calIdx == 0 && PtInRect(&infoPtr->titlebtnprev, lpht->pt))
    {
      htinfo.uHit = MCHT_TITLEBTNPREV;
      htinfo.rc = infoPtr->titlebtnprev;
    }
    else if (PtInRect(&infoPtr->titlebtnnext, lpht->pt))
    {
      htinfo.uHit = MCHT_TITLEBTNNEXT;
      htinfo.rc = infoPtr->titlebtnnext;
    }
    else if (PtInRect(&infoPtr->calendars[calIdx].titlemonth, lpht->pt))
    {
      htinfo.uHit = MCHT_TITLEMONTH;
      htinfo.rc = infoPtr->calendars[calIdx].titlemonth;
      htinfo.iOffset = calIdx;
    }
    else if (PtInRect(&infoPtr->calendars[calIdx].titleyear, lpht->pt))
    {
      htinfo.uHit = MCHT_TITLEYEAR;
      htinfo.rc = infoPtr->calendars[calIdx].titleyear;
      htinfo.iOffset = calIdx;
    }
    else
    {
      htinfo.uHit = MCHT_TITLE;
      htinfo.rc = infoPtr->calendars[calIdx].title;
      htinfo.iOffset = calIdx;
    }

    return fill_hittest_info(&htinfo, lpht);
  }

  ht_month = &infoPtr->calendars[calIdx].month;
  /* days area (including week days and week numbers) */
  day = MONTHCAL_GetDayFromPos(infoPtr, lpht->pt, calIdx);
  if (PtInRect(&infoPtr->calendars[calIdx].wdays, lpht->pt))
  {
    htinfo.uHit = MCHT_CALENDARDAY;
    htinfo.iOffset = calIdx;
    htinfo.st.wYear  = ht_month->wYear;
    htinfo.st.wMonth = (day < 1) ? ht_month->wMonth -1 : ht_month->wMonth;
    htinfo.st.wDay   = (day < 1) ?
      MONTHCAL_MonthLength(ht_month->wMonth-1, ht_month->wYear) - day : day;

    MONTHCAL_GetDayPos(infoPtr, &htinfo.st, &htinfo.iCol, &htinfo.iRow, calIdx);
  }
  else if(PtInRect(&infoPtr->calendars[calIdx].weeknums, lpht->pt))
  {
    htinfo.uHit = MCHT_CALENDARWEEKNUM;
    htinfo.st.wYear = ht_month->wYear;
    htinfo.iOffset = calIdx;

    if (day < 1)
    {
      htinfo.st.wMonth = ht_month->wMonth - 1;
      htinfo.st.wDay = MONTHCAL_MonthLength(ht_month->wMonth-1, ht_month->wYear) - day;
    }
    else if (day > MONTHCAL_MonthLength(ht_month->wMonth, ht_month->wYear))
    {
      htinfo.st.wMonth = ht_month->wMonth + 1;
      htinfo.st.wDay = day - MONTHCAL_MonthLength(ht_month->wMonth, ht_month->wYear);
    }
    else
    {
      htinfo.st.wMonth = ht_month->wMonth;
      htinfo.st.wDay = day;
    }
  }
  else if(PtInRect(&infoPtr->calendars[calIdx].days, lpht->pt))
  {
      htinfo.iOffset = calIdx;
      htinfo.st.wDay = ht_month->wDay;
      htinfo.st.wYear  = ht_month->wYear;
      htinfo.st.wMonth = ht_month->wMonth;
      /* previous month only valid for first calendar */
      if (day < 1 && calIdx == 0)
      {
	  htinfo.uHit = MCHT_CALENDARDATEPREV;
	  MONTHCAL_GetPrevMonth(&htinfo.st);
	  htinfo.st.wDay = MONTHCAL_MonthLength(htinfo.st.wMonth, htinfo.st.wYear) + day;
      }
      /* next month only valid for last calendar */
      else if (day > MONTHCAL_MonthLength(ht_month->wMonth, ht_month->wYear) &&
               calIdx == MONTHCAL_GetCalCount(infoPtr)-1)
      {
	  htinfo.uHit = MCHT_CALENDARDATENEXT;
	  MONTHCAL_GetNextMonth(&htinfo.st);
	  htinfo.st.wDay = day - MONTHCAL_MonthLength(ht_month->wMonth, ht_month->wYear);
      }
      /* multiple calendars case - blank areas for previous/next month */
      else if (day < 1 || day > MONTHCAL_MonthLength(ht_month->wMonth, ht_month->wYear))
      {
          htinfo.uHit = MCHT_CALENDARBK;
      }
      else
      {
	htinfo.uHit = MCHT_CALENDARDATE;
	htinfo.st.wDay = day;
      }

      MONTHCAL_GetDayPos(infoPtr, &htinfo.st, &htinfo.iCol, &htinfo.iRow, calIdx);
      MONTHCAL_GetDayRectI(infoPtr, &htinfo.rc, htinfo.iCol, htinfo.iRow, calIdx);
      /* always update day of week */
      MONTHCAL_CalculateDayOfWeek(&htinfo.st, TRUE);
  }

  return fill_hittest_info(&htinfo, lpht);
}