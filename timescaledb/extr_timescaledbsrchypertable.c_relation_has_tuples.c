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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
relation_has_tuples(Relation rel)
{
	HeapScanDesc scandesc = heap_beginscan(rel, GetActiveSnapshot(), 0, NULL);
	bool hastuples = HeapTupleIsValid(heap_getnext(scandesc, ForwardScanDirection));

	heap_endscan(scandesc);
	return hastuples;
}