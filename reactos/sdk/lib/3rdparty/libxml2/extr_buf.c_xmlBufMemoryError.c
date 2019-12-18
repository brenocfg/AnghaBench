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
typedef  TYPE_1__* xmlBufPtr ;
struct TYPE_3__ {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ XML_ERR_NO_MEMORY ; 
 int /*<<< orphan*/  XML_FROM_BUFFER ; 
 int /*<<< orphan*/  __xmlSimpleError (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
xmlBufMemoryError(xmlBufPtr buf, const char *extra)
{
    __xmlSimpleError(XML_FROM_BUFFER, XML_ERR_NO_MEMORY, NULL, NULL, extra);
    if ((buf) && (buf->error == 0))
        buf->error = XML_ERR_NO_MEMORY;
}