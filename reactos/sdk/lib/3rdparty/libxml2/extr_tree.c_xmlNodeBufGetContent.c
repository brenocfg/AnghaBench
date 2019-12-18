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
typedef  int /*<<< orphan*/  xmlNode ;
typedef  int /*<<< orphan*/ * xmlBufferPtr ;
typedef  int /*<<< orphan*/  xmlBufPtr ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlBufBackToBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlBufFromBuffer (int /*<<< orphan*/ *) ; 
 int xmlBufGetNodeContent (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int
xmlNodeBufGetContent(xmlBufferPtr buffer, const xmlNode *cur)
{
    xmlBufPtr buf;
    int ret;

    if ((cur == NULL) || (buffer == NULL)) return(-1);
    buf = xmlBufFromBuffer(buffer);
    ret = xmlBufGetNodeContent(buf, cur);
    buffer = xmlBufBackToBuffer(buf);
    if ((ret < 0) || (buffer == NULL))
        return(-1);
    return(0);
}