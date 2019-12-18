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
struct TYPE_3__ {char* title; char* message; int button_group_type; int /*<<< orphan*/  button_pressed; } ;
typedef  TYPE_1__ pdf_alert_event ;

/* Variables and functions */
#define  PDF_ALERT_BUTTON_GROUP_OK 131 
#define  PDF_ALERT_BUTTON_GROUP_OK_CANCEL 130 
#define  PDF_ALERT_BUTTON_GROUP_YES_NO 129 
#define  PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL 128 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_OK ; 
 int /*<<< orphan*/  PDF_ALERT_BUTTON_YES ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void winalert(pdfapp_t *app, pdf_alert_event *alert)
{
	char buf[1024];
	snprintf(buf, sizeof buf, "Alert %s: %s", alert->title, alert->message);
	fprintf(stderr, "%s\n", buf);
	switch (alert->button_group_type)
	{
	case PDF_ALERT_BUTTON_GROUP_OK:
	case PDF_ALERT_BUTTON_GROUP_OK_CANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_OK;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO:
	case PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_YES;
		break;
	}
}