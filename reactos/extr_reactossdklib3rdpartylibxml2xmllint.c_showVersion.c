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
 int /*<<< orphan*/  XML_WITH_AUTOMATA ; 
 int /*<<< orphan*/  XML_WITH_C14N ; 
 int /*<<< orphan*/  XML_WITH_CATALOG ; 
 int /*<<< orphan*/  XML_WITH_DEBUG ; 
 int /*<<< orphan*/  XML_WITH_DEBUG_MEM ; 
 int /*<<< orphan*/  XML_WITH_DEBUG_RUN ; 
 int /*<<< orphan*/  XML_WITH_EXPR ; 
 int /*<<< orphan*/  XML_WITH_FTP ; 
 int /*<<< orphan*/  XML_WITH_HTML ; 
 int /*<<< orphan*/  XML_WITH_HTTP ; 
 int /*<<< orphan*/  XML_WITH_ICONV ; 
 int /*<<< orphan*/  XML_WITH_ICU ; 
 int /*<<< orphan*/  XML_WITH_ISO8859X ; 
 int /*<<< orphan*/  XML_WITH_LEGACY ; 
 int /*<<< orphan*/  XML_WITH_LZMA ; 
 int /*<<< orphan*/  XML_WITH_MODULES ; 
 int /*<<< orphan*/  XML_WITH_OUTPUT ; 
 int /*<<< orphan*/  XML_WITH_PATTERN ; 
 int /*<<< orphan*/  XML_WITH_PUSH ; 
 int /*<<< orphan*/  XML_WITH_READER ; 
 int /*<<< orphan*/  XML_WITH_REGEXP ; 
 int /*<<< orphan*/  XML_WITH_SAX1 ; 
 int /*<<< orphan*/  XML_WITH_SCHEMAS ; 
 int /*<<< orphan*/  XML_WITH_SCHEMATRON ; 
 int /*<<< orphan*/  XML_WITH_THREAD ; 
 int /*<<< orphan*/  XML_WITH_TREE ; 
 int /*<<< orphan*/  XML_WITH_UNICODE ; 
 int /*<<< orphan*/  XML_WITH_VALID ; 
 int /*<<< orphan*/  XML_WITH_WRITER ; 
 int /*<<< orphan*/  XML_WITH_XINCLUDE ; 
 int /*<<< orphan*/  XML_WITH_XPATH ; 
 int /*<<< orphan*/  XML_WITH_XPTR ; 
 int /*<<< orphan*/  XML_WITH_ZLIB ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xmlHasFeature (int /*<<< orphan*/ ) ; 
 char* xmlParserVersion ; 

__attribute__((used)) static void showVersion(const char *name) {
    fprintf(stderr, "%s: using libxml version %s\n", name, xmlParserVersion);
    fprintf(stderr, "   compiled with: ");
    if (xmlHasFeature(XML_WITH_THREAD)) fprintf(stderr, "Threads ");
    if (xmlHasFeature(XML_WITH_TREE)) fprintf(stderr, "Tree ");
    if (xmlHasFeature(XML_WITH_OUTPUT)) fprintf(stderr, "Output ");
    if (xmlHasFeature(XML_WITH_PUSH)) fprintf(stderr, "Push ");
    if (xmlHasFeature(XML_WITH_READER)) fprintf(stderr, "Reader ");
    if (xmlHasFeature(XML_WITH_PATTERN)) fprintf(stderr, "Patterns ");
    if (xmlHasFeature(XML_WITH_WRITER)) fprintf(stderr, "Writer ");
    if (xmlHasFeature(XML_WITH_SAX1)) fprintf(stderr, "SAXv1 ");
    if (xmlHasFeature(XML_WITH_FTP)) fprintf(stderr, "FTP ");
    if (xmlHasFeature(XML_WITH_HTTP)) fprintf(stderr, "HTTP ");
    if (xmlHasFeature(XML_WITH_VALID)) fprintf(stderr, "DTDValid ");
    if (xmlHasFeature(XML_WITH_HTML)) fprintf(stderr, "HTML ");
    if (xmlHasFeature(XML_WITH_LEGACY)) fprintf(stderr, "Legacy ");
    if (xmlHasFeature(XML_WITH_C14N)) fprintf(stderr, "C14N ");
    if (xmlHasFeature(XML_WITH_CATALOG)) fprintf(stderr, "Catalog ");
    if (xmlHasFeature(XML_WITH_XPATH)) fprintf(stderr, "XPath ");
    if (xmlHasFeature(XML_WITH_XPTR)) fprintf(stderr, "XPointer ");
    if (xmlHasFeature(XML_WITH_XINCLUDE)) fprintf(stderr, "XInclude ");
    if (xmlHasFeature(XML_WITH_ICONV)) fprintf(stderr, "Iconv ");
    if (xmlHasFeature(XML_WITH_ICU)) fprintf(stderr, "ICU ");
    if (xmlHasFeature(XML_WITH_ISO8859X)) fprintf(stderr, "ISO8859X ");
    if (xmlHasFeature(XML_WITH_UNICODE)) fprintf(stderr, "Unicode ");
    if (xmlHasFeature(XML_WITH_REGEXP)) fprintf(stderr, "Regexps ");
    if (xmlHasFeature(XML_WITH_AUTOMATA)) fprintf(stderr, "Automata ");
    if (xmlHasFeature(XML_WITH_EXPR)) fprintf(stderr, "Expr ");
    if (xmlHasFeature(XML_WITH_SCHEMAS)) fprintf(stderr, "Schemas ");
    if (xmlHasFeature(XML_WITH_SCHEMATRON)) fprintf(stderr, "Schematron ");
    if (xmlHasFeature(XML_WITH_MODULES)) fprintf(stderr, "Modules ");
    if (xmlHasFeature(XML_WITH_DEBUG)) fprintf(stderr, "Debug ");
    if (xmlHasFeature(XML_WITH_DEBUG_MEM)) fprintf(stderr, "MemDebug ");
    if (xmlHasFeature(XML_WITH_DEBUG_RUN)) fprintf(stderr, "RunDebug ");
    if (xmlHasFeature(XML_WITH_ZLIB)) fprintf(stderr, "Zlib ");
    if (xmlHasFeature(XML_WITH_LZMA)) fprintf(stderr, "Lzma ");
    fprintf(stderr, "\n");
}