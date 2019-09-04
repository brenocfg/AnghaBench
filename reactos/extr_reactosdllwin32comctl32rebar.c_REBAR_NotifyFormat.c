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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int bUnicode; scalar_t__ hwndSelf; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ NFR_ANSI ; 
 scalar_t__ NFR_UNICODE ; 
 int /*<<< orphan*/  NF_QUERY ; 
 scalar_t__ NF_REQUERY ; 
 int /*<<< orphan*/  REBAR_GetNotifyParent (TYPE_1__*) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFYFORMAT ; 

__attribute__((used)) static LRESULT
REBAR_NotifyFormat (REBAR_INFO *infoPtr, LPARAM cmd)
{
    INT i;

    if (cmd == NF_REQUERY) {
	i = SendMessageW(REBAR_GetNotifyParent (infoPtr),
			 WM_NOTIFYFORMAT, (WPARAM)infoPtr->hwndSelf, NF_QUERY);
        if ((i != NFR_ANSI) && (i != NFR_UNICODE)) {
	    ERR("wrong response to WM_NOTIFYFORMAT (%d), assuming ANSI\n", i);
	    i = NFR_ANSI;
	}
        infoPtr->bUnicode = (i == NFR_UNICODE);
	return (LRESULT)i;
    }
    return (LRESULT)((infoPtr->bUnicode) ? NFR_UNICODE : NFR_ANSI);
}