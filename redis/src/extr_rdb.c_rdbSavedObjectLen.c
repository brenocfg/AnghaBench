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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  robj ;

/* Variables and functions */
 int rdbSaveObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

size_t rdbSavedObjectLen(robj *o) {
    ssize_t len = rdbSaveObject(NULL,o,NULL);
    serverAssertWithInfo(NULL,o,len != -1);
    return len;
}