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
typedef  int /*<<< orphan*/  pdfapp_t ;
struct TYPE_3__ {int icon_type; int button_group_type; int /*<<< orphan*/  button_pressed; int /*<<< orphan*/  title; int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ pdf_alert_event ;

/* Variables and functions */
#define  IDCANCEL 139 
#define  IDNO 138 
#define  IDOK 137 
#define  IDYES 136 
 int MB_ICONERROR ; 
 int MB_ICONINFORMATION ; 
 int MB_ICONQUESTION ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int MB_OKCANCEL ; 
 int MB_YESNO ; 
 int MB_YESNOCANCEL ; 
 int MessageBoxA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_CANCEL ; 
#define  PDF_ALERT_BUTTON_GROUP_OK 135 
#define  PDF_ALERT_BUTTON_GROUP_OK_CANCEL 134 
#define  PDF_ALERT_BUTTON_GROUP_YES_NO 133 
#define  PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL 132 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_NO ; 
 int PDF_ALERT_BUTTON_NONE ; 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_OK ; 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_YES ; 
#define  PDF_ALERT_ICON_ERROR 131 
#define  PDF_ALERT_ICON_QUESTION 130 
#define  PDF_ALERT_ICON_STATUS 129 
#define  PDF_ALERT_ICON_WARNING 128 
 int /*<<< orphan*/  hwndframe ; 

void winalert(pdfapp_t *app, pdf_alert_event *alert)
{
	int buttons = MB_OK;
	int icon = MB_ICONWARNING;
	int pressed = PDF_ALERT_BUTTON_NONE;

	switch (alert->icon_type)
	{
	case PDF_ALERT_ICON_ERROR:
		icon = MB_ICONERROR;
		break;
	case PDF_ALERT_ICON_WARNING:
		icon = MB_ICONWARNING;
		break;
	case PDF_ALERT_ICON_QUESTION:
		icon = MB_ICONQUESTION;
		break;
	case PDF_ALERT_ICON_STATUS:
		icon = MB_ICONINFORMATION;
		break;
	}

	switch (alert->button_group_type)
	{
	case PDF_ALERT_BUTTON_GROUP_OK:
		buttons = MB_OK;
		break;
	case PDF_ALERT_BUTTON_GROUP_OK_CANCEL:
		buttons = MB_OKCANCEL;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO:
		buttons = MB_YESNO;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL:
		buttons = MB_YESNOCANCEL;
		break;
	}

	pressed = MessageBoxA(hwndframe, alert->message, alert->title, icon|buttons);

	switch (pressed)
	{
	case IDOK:
		alert->button_pressed = PDF_ALERT_BUTTON_OK;
		break;
	case IDCANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_CANCEL;
		break;
	case IDNO:
		alert->button_pressed = PDF_ALERT_BUTTON_NO;
		break;
	case IDYES:
		alert->button_pressed = PDF_ALERT_BUTTON_YES;
	}
}