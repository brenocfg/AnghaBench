#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputPtr ;
typedef  int /*<<< orphan*/  xmlParserInput ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
struct TYPE_8__ {int /*<<< orphan*/  input_id; } ;
struct TYPE_7__ {int line; int col; int standalone; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_2__*,char*) ; 
 scalar_t__ xmlMalloc (int) ; 

xmlParserInputPtr
xmlNewInputStream(xmlParserCtxtPtr ctxt) {
    xmlParserInputPtr input;

    input = (xmlParserInputPtr) xmlMalloc(sizeof(xmlParserInput));
    if (input == NULL) {
        xmlErrMemory(ctxt,  "couldn't allocate a new input stream\n");
	return(NULL);
    }
    memset(input, 0, sizeof(xmlParserInput));
    input->line = 1;
    input->col = 1;
    input->standalone = -1;

    /*
     * If the context is NULL the id cannot be initialized, but that
     * should not happen while parsing which is the situation where
     * the id is actually needed.
     */
    if (ctxt != NULL)
        input->id = ctxt->input_id++;

    return(input);
}