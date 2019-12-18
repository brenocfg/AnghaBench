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
typedef  int /*<<< orphan*/  xmlHashTablePtr ;
typedef  int /*<<< orphan*/  xmlHashScanner ;
struct TYPE_3__ {int /*<<< orphan*/  hashscanner; void* data; } ;
typedef  TYPE_1__ stubData ;

/* Variables and functions */
 int /*<<< orphan*/  stubHashScannerFull ; 
 int /*<<< orphan*/  xmlHashScanFull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
xmlHashScan(xmlHashTablePtr table, xmlHashScanner f, void *data) {
    stubData stubdata;
    stubdata.data = data;
    stubdata.hashscanner = f;
    xmlHashScanFull (table, stubHashScannerFull, &stubdata);
}