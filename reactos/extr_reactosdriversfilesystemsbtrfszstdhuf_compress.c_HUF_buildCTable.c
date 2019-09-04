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
typedef  int /*<<< orphan*/  nodeTable ;
typedef  int /*<<< orphan*/  huffNodeTable ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  HUF_CElt ;

/* Variables and functions */
 size_t HUF_buildCTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

size_t HUF_buildCTable (HUF_CElt* tree, const U32* count, U32 maxSymbolValue, U32 maxNbBits)
{
    huffNodeTable nodeTable;
    return HUF_buildCTable_wksp(tree, count, maxSymbolValue, maxNbBits, nodeTable, sizeof(nodeTable));
}