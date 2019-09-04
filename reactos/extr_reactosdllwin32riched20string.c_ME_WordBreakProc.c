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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;

/* Variables and functions */
 int ME_IsWSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,int,int) ; 
#define  WB_ISDELIMITER 132 
#define  WB_LEFT 131 
#define  WB_MOVEWORDLEFT 130 
#define  WB_MOVEWORDRIGHT 129 
#define  WB_RIGHT 128 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ME_WordBreakProc(LPWSTR s, INT start, INT len, INT code)
{
  /* FIXME: Native also knows about punctuation */
  TRACE("s==%s, start==%d, len==%d, code==%d\n",
        debugstr_wn(s, len), start, len, code);

  switch (code)
  {
    case WB_ISDELIMITER:
      return ME_IsWSpace(s[start]);
    case WB_LEFT:
    case WB_MOVEWORDLEFT:
      while (start && ME_IsWSpace(s[start - 1]))
        start--;
      while (start && !ME_IsWSpace(s[start - 1]))
        start--;
      return start;
    case WB_RIGHT:
    case WB_MOVEWORDRIGHT:
      while (start < len && !ME_IsWSpace(s[start]))
        start++;
      while (start < len && ME_IsWSpace(s[start]))
        start++;
      return start;
  }
  return 0;
}