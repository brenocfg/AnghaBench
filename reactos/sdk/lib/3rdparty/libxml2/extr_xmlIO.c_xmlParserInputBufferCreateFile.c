#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserInputBufferPtr ;
typedef  int /*<<< orphan*/  xmlCharEncoding ;
struct TYPE_4__ {int /*<<< orphan*/  closecallback; int /*<<< orphan*/  readcallback; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* xmlAllocParserInputBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFileFlush ; 
 int /*<<< orphan*/  xmlFileRead ; 
 scalar_t__ xmlInputCallbackInitialized ; 
 int /*<<< orphan*/  xmlRegisterDefaultInputCallbacks () ; 

xmlParserInputBufferPtr
xmlParserInputBufferCreateFile(FILE *file, xmlCharEncoding enc) {
    xmlParserInputBufferPtr ret;

    if (xmlInputCallbackInitialized == 0)
	xmlRegisterDefaultInputCallbacks();

    if (file == NULL) return(NULL);

    ret = xmlAllocParserInputBuffer(enc);
    if (ret != NULL) {
        ret->context = file;
	ret->readcallback = xmlFileRead;
	ret->closecallback = xmlFileFlush;
    }

    return(ret);
}