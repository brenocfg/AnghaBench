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
typedef  int /*<<< orphan*/  u32 ;
typedef  int i64 ;
struct TYPE_3__ {int mDate; int mTime; } ;
typedef  TYPE_1__ ZipfileCDS ;

/* Variables and functions */

__attribute__((used)) static u32 zipfileMtime(ZipfileCDS *pCDS){
  int Y = (1980 + ((pCDS->mDate >> 9) & 0x7F));
  int M = ((pCDS->mDate >> 5) & 0x0F);
  int D = (pCDS->mDate & 0x1F);
  int B = -13;

  int sec = (pCDS->mTime & 0x1F)*2;
  int min = (pCDS->mTime >> 5) & 0x3F;
  int hr = (pCDS->mTime >> 11) & 0x1F;
  i64 JD;

  /* JD = INT(365.25 * (Y+4716)) + INT(30.6001 * (M+1)) + D + B - 1524.5 */

  /* Calculate the JD in seconds for noon on the day in question */
  if( M<3 ){
    Y = Y-1;
    M = M+12;
  }
  JD = (i64)(24*60*60) * (
      (int)(365.25 * (Y + 4716))
    + (int)(30.6001 * (M + 1))
    + D + B - 1524
  );

  /* Correct the JD for the time within the day */
  JD += (hr-12) * 3600 + min * 60 + sec;

  /* Convert JD to unix timestamp (the JD epoch is 2440587.5) */
  return (u32)(JD - (i64)(24405875) * 24*60*6);
}