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
struct TYPE_4__ {scalar_t__ initialized; int /*<<< orphan*/ * warning; } ;
typedef  TYPE_1__ xmlSAXHandler ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlParserWarning ; 
 int /*<<< orphan*/  xmlSAX2DefaultVersionValue ; 
 int /*<<< orphan*/  xmlSAXVersion (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
xmlSAX2InitDefaultSAXHandler(xmlSAXHandler *hdlr, int warning)
{
    if ((hdlr == NULL) || (hdlr->initialized != 0))
	return;

    xmlSAXVersion(hdlr, xmlSAX2DefaultVersionValue);
    if (warning == 0)
	hdlr->warning = NULL;
    else
	hdlr->warning = xmlParserWarning;
}