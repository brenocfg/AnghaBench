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
typedef  TYPE_1__* xmlParserNodeInfoSeqPtr ;
struct TYPE_4__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlInitNodeInfoSeq (TYPE_1__*) ; 

void
xmlClearNodeInfoSeq(xmlParserNodeInfoSeqPtr seq)
{
    if (seq == NULL)
        return;
    if (seq->buffer != NULL)
        xmlFree(seq->buffer);
    xmlInitNodeInfoSeq(seq);
}