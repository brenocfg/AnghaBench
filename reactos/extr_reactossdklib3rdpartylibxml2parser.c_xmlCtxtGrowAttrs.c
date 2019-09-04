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
struct TYPE_4__ {int* attallocs; int maxatts; int /*<<< orphan*/  const** atts; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ xmlMalloc (int) ; 
 scalar_t__ xmlRealloc (void*,int) ; 

__attribute__((used)) static int
xmlCtxtGrowAttrs(xmlParserCtxtPtr ctxt, int nr) {
    const xmlChar **atts;
    int *attallocs;
    int maxatts;

    if (ctxt->atts == NULL) {
	maxatts = 55; /* allow for 10 attrs by default */
	atts = (const xmlChar **)
	       xmlMalloc(maxatts * sizeof(xmlChar *));
	if (atts == NULL) goto mem_error;
	ctxt->atts = atts;
	attallocs = (int *) xmlMalloc((maxatts / 5) * sizeof(int));
	if (attallocs == NULL) goto mem_error;
	ctxt->attallocs = attallocs;
	ctxt->maxatts = maxatts;
    } else if (nr + 5 > ctxt->maxatts) {
	maxatts = (nr + 5) * 2;
	atts = (const xmlChar **) xmlRealloc((void *) ctxt->atts,
				     maxatts * sizeof(const xmlChar *));
	if (atts == NULL) goto mem_error;
	ctxt->atts = atts;
	attallocs = (int *) xmlRealloc((void *) ctxt->attallocs,
	                             (maxatts / 5) * sizeof(int));
	if (attallocs == NULL) goto mem_error;
	ctxt->attallocs = attallocs;
	ctxt->maxatts = maxatts;
    }
    return(ctxt->maxatts);
mem_error:
    xmlErrMemory(ctxt, NULL);
    return(-1);
}