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
typedef  int /*<<< orphan*/  DLWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  dlrDocData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrDocDataBytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlwCopy(DLWriter *pWriter, DLReader *pReader){
  dlwAppend(pWriter, dlrDocData(pReader), dlrDocDataBytes(pReader),
            dlrDocid(pReader), dlrDocid(pReader));
}