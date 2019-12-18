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
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  xmlTextReaderLocatorPtr ;
typedef  int /*<<< orphan*/  xmlParserSeverities ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int,char const*) ; 
 int xmlTextReaderLocatorLineNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReaderErrorHandler( void *p_arg, const char *p_msg,
                                xmlParserSeverities severity,
                                xmlTextReaderLocatorPtr locator)
{
    VLC_UNUSED(severity);
    xml_reader_t *p_reader = (xml_reader_t *)p_arg;
    int line = xmlTextReaderLocatorLineNumber( locator );
    msg_Err( p_reader, "XML parser error (line %d) : %s", line, p_msg );
}