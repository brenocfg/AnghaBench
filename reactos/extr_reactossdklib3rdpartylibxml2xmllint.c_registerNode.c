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
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_3__ {int /*<<< orphan*/ * _private; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMLLINT_ERR_MEM ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  nbregister ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void registerNode(xmlNodePtr node)
{
    node->_private = malloc(sizeof(long));
    if (node->_private == NULL) {
        fprintf(stderr, "Out of memory in xmllint:registerNode()\n");
	exit(XMLLINT_ERR_MEM);
    }
    *(long*)node->_private = (long) 0x81726354;
    nbregister++;
}