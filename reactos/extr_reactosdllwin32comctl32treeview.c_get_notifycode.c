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
struct TYPE_3__ {int /*<<< orphan*/  bNtfUnicode; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  int INT ;

/* Variables and functions */
 int TVN_BEGINDRAGA ; 
#define  TVN_BEGINDRAGW 139 
 int TVN_BEGINLABELEDITA ; 
#define  TVN_BEGINLABELEDITW 138 
 int TVN_BEGINRDRAGA ; 
#define  TVN_BEGINRDRAGW 137 
 int TVN_DELETEITEMA ; 
#define  TVN_DELETEITEMW 136 
 int TVN_ENDLABELEDITA ; 
#define  TVN_ENDLABELEDITW 135 
 int TVN_GETDISPINFOA ; 
#define  TVN_GETDISPINFOW 134 
 int TVN_GETINFOTIPA ; 
#define  TVN_GETINFOTIPW 133 
 int TVN_ITEMEXPANDEDA ; 
#define  TVN_ITEMEXPANDEDW 132 
 int TVN_ITEMEXPANDINGA ; 
#define  TVN_ITEMEXPANDINGW 131 
 int TVN_SELCHANGEDA ; 
#define  TVN_SELCHANGEDW 130 
 int TVN_SELCHANGINGA ; 
#define  TVN_SELCHANGINGW 129 
 int TVN_SETDISPINFOA ; 
#define  TVN_SETDISPINFOW 128 

__attribute__((used)) static INT get_notifycode(const TREEVIEW_INFO *infoPtr, INT code)
{
    if (!infoPtr->bNtfUnicode) {
	switch (code) {
	case TVN_SELCHANGINGW:	  return TVN_SELCHANGINGA;
	case TVN_SELCHANGEDW:	  return TVN_SELCHANGEDA;
	case TVN_GETDISPINFOW:	  return TVN_GETDISPINFOA;
	case TVN_SETDISPINFOW:	  return TVN_SETDISPINFOA;
	case TVN_ITEMEXPANDINGW:  return TVN_ITEMEXPANDINGA;
	case TVN_ITEMEXPANDEDW:	  return TVN_ITEMEXPANDEDA;
	case TVN_BEGINDRAGW:	  return TVN_BEGINDRAGA;
	case TVN_BEGINRDRAGW:	  return TVN_BEGINRDRAGA;
	case TVN_DELETEITEMW:	  return TVN_DELETEITEMA;
	case TVN_BEGINLABELEDITW: return TVN_BEGINLABELEDITA;
	case TVN_ENDLABELEDITW:	  return TVN_ENDLABELEDITA;
	case TVN_GETINFOTIPW:	  return TVN_GETINFOTIPA;
	}
    }
    return code;
}