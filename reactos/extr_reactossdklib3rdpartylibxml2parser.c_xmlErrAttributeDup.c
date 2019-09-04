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
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_4__ {int disableSAX; scalar_t__ instate; scalar_t__ recovery; scalar_t__ wellFormed; int /*<<< orphan*/  errNo; } ;

/* Variables and functions */
 int /*<<< orphan*/  XML_ERR_ATTRIBUTE_REDEFINED ; 
 int /*<<< orphan*/  XML_ERR_FATAL ; 
 int /*<<< orphan*/  XML_FROM_PARSER ; 
 scalar_t__ XML_PARSER_EOF ; 
 int /*<<< orphan*/  __xmlRaiseError (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,...) ; 

__attribute__((used)) static void
xmlErrAttributeDup(xmlParserCtxtPtr ctxt, const xmlChar * prefix,
                   const xmlChar * localname)
{
    if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != NULL)
	ctxt->errNo = XML_ERR_ATTRIBUTE_REDEFINED;

    if (prefix == NULL)
        __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_PARSER,
                        XML_ERR_ATTRIBUTE_REDEFINED, XML_ERR_FATAL, NULL, 0,
                        (const char *) localname, NULL, NULL, 0, 0,
                        "Attribute %s redefined\n", localname);
    else
        __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_PARSER,
                        XML_ERR_ATTRIBUTE_REDEFINED, XML_ERR_FATAL, NULL, 0,
                        (const char *) prefix, (const char *) localname,
                        NULL, 0, 0, "Attribute %s:%s redefined\n", prefix,
                        localname);
    if (ctxt != NULL) {
	ctxt->wellFormed = 0;
	if (ctxt->recovery == 0)
	    ctxt->disableSAX = 1;
    }
}