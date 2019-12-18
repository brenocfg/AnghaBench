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
struct TYPE_3__ {scalar_t__ type; scalar_t__* content; } ;
typedef  TYPE_1__ xmlNode ;
typedef  scalar_t__ xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  IS_BLANK_CH (scalar_t__ const) ; 
 scalar_t__ XML_CDATA_SECTION_NODE ; 
 scalar_t__ XML_TEXT_NODE ; 

int
xmlIsBlankNode(const xmlNode *node) {
    const xmlChar *cur;
    if (node == NULL) return(0);

    if ((node->type != XML_TEXT_NODE) &&
        (node->type != XML_CDATA_SECTION_NODE))
	return(0);
    if (node->content == NULL) return(1);
    cur = node->content;
    while (*cur != 0) {
	if (!IS_BLANK_CH(*cur)) return(0);
	cur++;
    }

    return(1);
}