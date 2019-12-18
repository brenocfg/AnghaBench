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
typedef  int /*<<< orphan*/  xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;

/* Variables and functions */
 int /*<<< orphan*/  __xmlParserInputBufferCreateFilename (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlParserInputBufferCreateFilenameValue (char const*,int /*<<< orphan*/ ) ; 

xmlParserInputBufferPtr
xmlParserInputBufferCreateFilename(const char *URI, xmlCharEncoding enc) {
    if ((xmlParserInputBufferCreateFilenameValue)) {
		return xmlParserInputBufferCreateFilenameValue(URI, enc);
	}
	return __xmlParserInputBufferCreateFilename(URI, enc);
}