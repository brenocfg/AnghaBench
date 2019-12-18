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

/* Variables and functions */
 int /*<<< orphan*/  xmlFileClose ; 
 int /*<<< orphan*/  xmlFileMatch ; 
 int /*<<< orphan*/  xmlFileOpen ; 
 int /*<<< orphan*/  xmlFileRead ; 
 int /*<<< orphan*/  xmlGzfileClose ; 
 int /*<<< orphan*/  xmlGzfileMatch ; 
 int /*<<< orphan*/  xmlGzfileOpen ; 
 int /*<<< orphan*/  xmlGzfileRead ; 
 int /*<<< orphan*/  xmlIOFTPClose ; 
 int /*<<< orphan*/  xmlIOFTPMatch ; 
 int /*<<< orphan*/  xmlIOFTPOpen ; 
 int /*<<< orphan*/  xmlIOFTPRead ; 
 int /*<<< orphan*/  xmlIOHTTPClose ; 
 int /*<<< orphan*/  xmlIOHTTPMatch ; 
 int /*<<< orphan*/  xmlIOHTTPOpen ; 
 int /*<<< orphan*/  xmlIOHTTPRead ; 
 int xmlInputCallbackInitialized ; 
 int /*<<< orphan*/  xmlRegisterInputCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlXzfileClose ; 
 int /*<<< orphan*/  xmlXzfileMatch ; 
 int /*<<< orphan*/  xmlXzfileOpen ; 
 int /*<<< orphan*/  xmlXzfileRead ; 

void
xmlRegisterDefaultInputCallbacks(void) {
    if (xmlInputCallbackInitialized)
	return;

    xmlRegisterInputCallbacks(xmlFileMatch, xmlFileOpen,
	                      xmlFileRead, xmlFileClose);
#ifdef LIBXML_ZLIB_ENABLED
    xmlRegisterInputCallbacks(xmlGzfileMatch, xmlGzfileOpen,
	                      xmlGzfileRead, xmlGzfileClose);
#endif /* LIBXML_ZLIB_ENABLED */
#ifdef LIBXML_LZMA_ENABLED
    xmlRegisterInputCallbacks(xmlXzfileMatch, xmlXzfileOpen,
	                      xmlXzfileRead, xmlXzfileClose);
#endif /* LIBXML_LZMA_ENABLED */

#ifdef LIBXML_HTTP_ENABLED
    xmlRegisterInputCallbacks(xmlIOHTTPMatch, xmlIOHTTPOpen,
	                      xmlIOHTTPRead, xmlIOHTTPClose);
#endif /* LIBXML_HTTP_ENABLED */

#ifdef LIBXML_FTP_ENABLED
    xmlRegisterInputCallbacks(xmlIOFTPMatch, xmlIOFTPOpen,
	                      xmlIOFTPRead, xmlIOFTPClose);
#endif /* LIBXML_FTP_ENABLED */
    xmlInputCallbackInitialized = 1;
}