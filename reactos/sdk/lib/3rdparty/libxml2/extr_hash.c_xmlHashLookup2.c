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
typedef  int /*<<< orphan*/  xmlHashTablePtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 void* xmlHashLookup3 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void *
xmlHashLookup2(xmlHashTablePtr table, const xmlChar *name,
	      const xmlChar *name2) {
    return(xmlHashLookup3(table, name, name2, NULL));
}