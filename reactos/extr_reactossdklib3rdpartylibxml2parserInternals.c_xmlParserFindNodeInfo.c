#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * const node; } ;
typedef  TYPE_1__ xmlParserNodeInfo ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/ * xmlNodePtr ;
struct TYPE_8__ {unsigned long length; TYPE_1__ const* buffer; } ;
struct TYPE_7__ {TYPE_3__ node_seq; } ;

/* Variables and functions */
 unsigned long xmlParserFindNodeInfoIndex (TYPE_3__*,int /*<<< orphan*/ * const) ; 

const xmlParserNodeInfo *
xmlParserFindNodeInfo(const xmlParserCtxtPtr ctx, const xmlNodePtr node)
{
    unsigned long pos;

    if ((ctx == NULL) || (node == NULL))
        return (NULL);
    /* Find position where node should be at */
    pos = xmlParserFindNodeInfoIndex(&ctx->node_seq, node);
    if (pos < ctx->node_seq.length
        && ctx->node_seq.buffer[pos].node == node)
        return &ctx->node_seq.buffer[pos];
    else
        return NULL;
}