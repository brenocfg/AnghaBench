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
typedef  int /*<<< orphan*/  xmlOutputBufferCreateFilenameFunc ;

/* Variables and functions */
 int /*<<< orphan*/  xmlOutputBufferCreateFilenameValue ; 

xmlOutputBufferCreateFilenameFunc
xmlOutputBufferCreateFilenameDefault(xmlOutputBufferCreateFilenameFunc func)
{
    xmlOutputBufferCreateFilenameFunc old = xmlOutputBufferCreateFilenameValue;
#ifdef LIBXML_OUTPUT_ENABLED
    if (old == NULL) {
		old = __xmlOutputBufferCreateFilename;
	}
#endif
    xmlOutputBufferCreateFilenameValue = func;
    return(old);
}