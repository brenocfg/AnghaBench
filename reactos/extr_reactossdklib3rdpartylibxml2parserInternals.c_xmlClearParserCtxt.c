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
struct TYPE_4__ {int /*<<< orphan*/  node_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlClearNodeInfoSeq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlCtxtReset (TYPE_1__*) ; 

void
xmlClearParserCtxt(xmlParserCtxtPtr ctxt)
{
  if (ctxt==NULL)
    return;
  xmlClearNodeInfoSeq(&ctxt->node_seq);
  xmlCtxtReset(ctxt);
}