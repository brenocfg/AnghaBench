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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  HDN_BEGINDRAG 153 
#define  HDN_DIVIDERDBLCLICKA 152 
#define  HDN_DIVIDERDBLCLICKW 151 
#define  HDN_ENDDRAG 150 
#define  HDN_ENDTRACKA 149 
#define  HDN_ENDTRACKW 148 
#define  HDN_ITEMCHANGEDA 147 
#define  HDN_ITEMCHANGEDW 146 
#define  HDN_ITEMCHANGINGA 145 
#define  HDN_ITEMCHANGINGW 144 
#define  HDN_ITEMCLICKA 143 
#define  HDN_ITEMCLICKW 142 
#define  HDN_TRACKA 141 
#define  HDN_TRACKW 140 
#define  LVN_BEGINLABELEDITA 139 
#define  LVN_BEGINLABELEDITW 138 
#define  LVN_ENDLABELEDITA 137 
#define  LVN_ENDLABELEDITW 136 
#define  LVN_GETDISPINFOA 135 
#define  LVN_GETDISPINFOW 134 
#define  LVN_GETINFOTIPA 133 
#define  LVN_GETINFOTIPW 132 
#define  LVN_ODFINDITEMA 131 
#define  LVN_ODFINDITEMW 130 
#define  LVN_SETDISPINFOA 129 
#define  LVN_SETDISPINFOW 128 

__attribute__((used)) static int get_ansi_notification(UINT unicodeNotificationCode)
{
    switch (unicodeNotificationCode)
    {
    case LVN_BEGINLABELEDITA:
    case LVN_BEGINLABELEDITW: return LVN_BEGINLABELEDITA;
    case LVN_ENDLABELEDITA:
    case LVN_ENDLABELEDITW: return LVN_ENDLABELEDITA;
    case LVN_GETDISPINFOA:
    case LVN_GETDISPINFOW: return LVN_GETDISPINFOA;
    case LVN_SETDISPINFOA:
    case LVN_SETDISPINFOW: return LVN_SETDISPINFOA;
    case LVN_ODFINDITEMA:
    case LVN_ODFINDITEMW: return LVN_ODFINDITEMA;
    case LVN_GETINFOTIPA:
    case LVN_GETINFOTIPW: return LVN_GETINFOTIPA;
    /* header forwards */
    case HDN_TRACKA:
    case HDN_TRACKW: return HDN_TRACKA;
    case HDN_ENDTRACKA:
    case HDN_ENDTRACKW: return HDN_ENDTRACKA;
    case HDN_BEGINDRAG: return HDN_BEGINDRAG;
    case HDN_ENDDRAG: return HDN_ENDDRAG;
    case HDN_ITEMCHANGINGA:
    case HDN_ITEMCHANGINGW: return HDN_ITEMCHANGINGA;
    case HDN_ITEMCHANGEDA:
    case HDN_ITEMCHANGEDW: return HDN_ITEMCHANGEDA;
    case HDN_ITEMCLICKA:
    case HDN_ITEMCLICKW: return HDN_ITEMCLICKA;
    case HDN_DIVIDERDBLCLICKA:
    case HDN_DIVIDERDBLCLICKW: return HDN_DIVIDERDBLCLICKA;
    default: break;
    }
    FIXME("unknown notification %x\n", unicodeNotificationCode);
    return unicodeNotificationCode;
}