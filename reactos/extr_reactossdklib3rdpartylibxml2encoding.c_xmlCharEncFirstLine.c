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
typedef  int /*<<< orphan*/  xmlCharEncodingHandler ;
typedef  int /*<<< orphan*/  xmlBufferPtr ;

/* Variables and functions */
 int xmlCharEncFirstLineInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
xmlCharEncFirstLine(xmlCharEncodingHandler *handler, xmlBufferPtr out,
                 xmlBufferPtr in) {
    return(xmlCharEncFirstLineInt(handler, out, in, -1));
}