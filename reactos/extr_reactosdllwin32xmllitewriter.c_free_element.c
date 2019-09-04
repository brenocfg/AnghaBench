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
typedef  int /*<<< orphan*/  xmlwriter ;
struct element {struct element* qname; } ;

/* Variables and functions */
 int /*<<< orphan*/  writer_free (int /*<<< orphan*/ *,struct element*) ; 

__attribute__((used)) static void free_element(xmlwriter *writer, struct element *element)
{
    writer_free(writer, element->qname);
    writer_free(writer, element);
}