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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/  XHTML_FRAME_PUBLIC_ID ; 
 int /*<<< orphan*/  XHTML_FRAME_SYSTEM_ID ; 
 int /*<<< orphan*/  XHTML_STRICT_PUBLIC_ID ; 
 int /*<<< orphan*/  XHTML_STRICT_SYSTEM_ID ; 
 int /*<<< orphan*/  XHTML_TRANS_PUBLIC_ID ; 
 int /*<<< orphan*/  XHTML_TRANS_SYSTEM_ID ; 
 scalar_t__ xmlStrEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
xmlIsXHTML(const xmlChar *systemID, const xmlChar *publicID) {
    if ((systemID == NULL) && (publicID == NULL))
	return(-1);
    if (publicID != NULL) {
	if (xmlStrEqual(publicID, XHTML_STRICT_PUBLIC_ID)) return(1);
	if (xmlStrEqual(publicID, XHTML_FRAME_PUBLIC_ID)) return(1);
	if (xmlStrEqual(publicID, XHTML_TRANS_PUBLIC_ID)) return(1);
    }
    if (systemID != NULL) {
	if (xmlStrEqual(systemID, XHTML_STRICT_SYSTEM_ID)) return(1);
	if (xmlStrEqual(systemID, XHTML_FRAME_SYSTEM_ID)) return(1);
	if (xmlStrEqual(systemID, XHTML_TRANS_SYSTEM_ID)) return(1);
    }
    return(0);
}