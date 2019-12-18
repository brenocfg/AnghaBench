#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {long QuadPart; int LowPart; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  size_t INT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CHAR_ZERO ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LOWORD (int) ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SZ_PERCENTD ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/ * pdwOrders ; 
 int /*<<< orphan*/  szDecimal ; 
 scalar_t__* szFormat ; 
 int wsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,...) ; 

LPTSTR
ShortSizeFormatInternal(LPTSTR szBuf, LARGE_INTEGER qw)
{
   INT i;
   UINT uInt, uLen, uDec;
   TCHAR szTemp[10], szOrder[20];

   LARGE_INTEGER qConstant;
   DWORD dw;

   qConstant.QuadPart = 1024L;

   if (qw.QuadPart < qConstant.QuadPart)
   {
      wsprintf(szTemp, SZ_PERCENTD, LOWORD(qw.LowPart));
      i = 0;
      goto AddOrder;
   }

   qConstant.QuadPart = (1024L * 1000L - 1);

   for ( i = 1;
         (qw.QuadPart > qConstant.QuadPart);
		 qw.QuadPart = qw.QuadPart / 1024L, ++i)

      /* do nothing */
      ;

   dw = qw.LowPart;

   uInt = (UINT) (dw / 1024);
   uLen = wsprintf(szTemp, SZ_PERCENTD, uInt);
   if (uLen < 3) {
      uDec = (dw - uInt * 1024L) * 1000 / 1024;

      //
      // At this point, uDec should be between 0 and 1000
      // we want get the top one (or two) digits.
      //
      uDec /= 10;
      if (uLen == 2) {
         uDec /= 10;
      }

      //
      // Note that we need to set the format before getting the
      // intl CHAR.
      //
      szFormat[4] = CHAR_ZERO + 3 - uLen;
      uLen += wsprintf(szTemp+uLen, szFormat, szDecimal, uDec);
   }

AddOrder:
   LoadString(hAppInstance, pdwOrders[i], szOrder, COUNTOF(szOrder));
   wsprintf(szBuf, szOrder, szTemp);

   return(szBuf);
}