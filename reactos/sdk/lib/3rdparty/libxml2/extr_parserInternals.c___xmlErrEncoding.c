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
typedef  int /*<<< orphan*/  xmlParserErrors ;
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int disableSAX; scalar_t__ instate; scalar_t__ recovery; scalar_t__ wellFormed; int /*<<< orphan*/  errNo; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_FATAL ; 
 int /*<<< orphan*/  XML_FROM_PARSER ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void
__xmlErrEncoding(xmlParserCtxtPtr ctxt, xmlParserErrors xmlerr,
                 const char *msg, const xmlChar * str1, const xmlChar * str2)
{
    if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != NULL)
        ctxt->errNo = xmlerr;
    __xmlRaiseError(NULL, NULL, NULL,
                    ctxt, NULL, XML_FROM_PARSER, xmlerr, XML_ERR_FATAL,
                    NULL, 0, (const char *) str1, (const char *) str2,
                    NULL, 0, 0, msg, str1, str2);
    if (ctxt != NULL) {
        ctxt->wellFormed = 0;
        if (ctxt->recovery == 0)
            ctxt->disableSAX = 1;
    }
}