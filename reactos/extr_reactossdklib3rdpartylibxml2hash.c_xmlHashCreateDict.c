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
typedef  TYPE_1__* xmlHashTablePtr ;
typedef  int /*<<< orphan*/  xmlDictPtr ;
struct TYPE_4__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlDictReference (int /*<<< orphan*/ ) ; 
 TYPE_1__* xmlHashCreate (int) ; 

xmlHashTablePtr
xmlHashCreateDict(int size, xmlDictPtr dict) {
    xmlHashTablePtr table;

    table = xmlHashCreate(size);
    if (table != NULL) {
        table->dict = dict;
	xmlDictReference(dict);
    }
    return(table);
}