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
typedef  TYPE_1__* xmlParserInputBufferPtr ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  context; int /*<<< orphan*/  (* closecallback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * encoder; int /*<<< orphan*/ * raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCharEncCloseFunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFree (TYPE_1__*) ; 

void
xmlFreeParserInputBuffer(xmlParserInputBufferPtr in) {
    if (in == NULL) return;

    if (in->raw) {
        xmlBufFree(in->raw);
	in->raw = NULL;
    }
    if (in->encoder != NULL) {
        xmlCharEncCloseFunc(in->encoder);
    }
    if (in->closecallback != NULL) {
	in->closecallback(in->context);
    }
    if (in->buffer != NULL) {
        xmlBufFree(in->buffer);
	in->buffer = NULL;
    }

    xmlFree(in);
}