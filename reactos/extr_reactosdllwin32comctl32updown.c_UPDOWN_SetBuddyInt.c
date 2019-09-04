#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  txt ;
typedef  char WCHAR ;
struct TYPE_4__ {int Flags; int Base; int dwStyle; int /*<<< orphan*/  Buddy; int /*<<< orphan*/  CurVal; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int FALSE ; 
 int FLAG_BUDDYINT ; 
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetWindowTextW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int UDS_NOTHOUSANDS ; 
 char UPDOWN_GetThousandSep () ; 
 scalar_t__ UPDOWN_IsBuddyListbox (TYPE_1__ const*) ; 
 scalar_t__ lstrcmpiW (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int wsprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL UPDOWN_SetBuddyInt (const UPDOWN_INFO *infoPtr)
{
    static const WCHAR fmt_hex[] = { '0', 'x', '%', '0', '4', 'X', 0 };
    static const WCHAR fmt_dec_oct[] = { '%', 'd', '\0' };
    const WCHAR *fmt;
    WCHAR txt[20], txt_old[20] = { 0 };
    int len;

    if (!((infoPtr->Flags & FLAG_BUDDYINT) && IsWindow(infoPtr->Buddy)))
        return FALSE;

    TRACE("set new value(%d) to buddy.\n", infoPtr->CurVal);

    /*if the buddy is a list window, we must set curr index */
    if (UPDOWN_IsBuddyListbox(infoPtr)) {
        return SendMessageW(infoPtr->Buddy, LB_SETCURSEL, infoPtr->CurVal, 0) != LB_ERR;
    }

    /* Regular window, so set caption to the number */
    fmt = (infoPtr->Base == 16) ? fmt_hex : fmt_dec_oct;
    len = wsprintfW(txt, fmt, infoPtr->CurVal);


    /* Do thousands separation if necessary */
    if ((infoPtr->Base == 10) && !(infoPtr->dwStyle & UDS_NOTHOUSANDS) && (len > 3)) {
        WCHAR tmp[ARRAY_SIZE(txt)], *src = tmp, *dst = txt;
        WCHAR sep = UPDOWN_GetThousandSep();
	int start = len % 3;

	memcpy(tmp, txt, sizeof(txt));
	if (start == 0) start = 3;
	dst += start;
	src += start;
        for (len=0; *src; len++) {
	    if (len % 3 == 0) *dst++ = sep;
	    *dst++ = *src++;
        }
        *dst = 0;
    }

    /* if nothing changed exit earlier */
    GetWindowTextW(infoPtr->Buddy, txt_old, ARRAY_SIZE(txt_old));
    if (lstrcmpiW(txt_old, txt) == 0) return FALSE;

    return SetWindowTextW(infoPtr->Buddy, txt);
}