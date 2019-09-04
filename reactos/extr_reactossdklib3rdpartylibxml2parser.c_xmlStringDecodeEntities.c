#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlStringLenDecodeEntities (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlStrlen (int /*<<< orphan*/  const*) ; 

xmlChar *
xmlStringDecodeEntities(xmlParserCtxtPtr ctxt, const xmlChar *str, int what,
		        xmlChar end, xmlChar  end2, xmlChar end3) {
    if ((ctxt == NULL) || (str == NULL)) return(NULL);
    return(xmlStringLenDecodeEntities(ctxt, str, xmlStrlen(str), what,
           end, end2, end3));
}