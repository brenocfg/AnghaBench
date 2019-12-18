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
typedef  int /*<<< orphan*/  PLWriter ;
typedef  int /*<<< orphan*/  PLReader ;

/* Variables and functions */
 int /*<<< orphan*/  plrColumn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrEndOffset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrPosition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plrStartOffset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plwCopy(PLWriter *pWriter, PLReader *pReader){
  plwAdd(pWriter, plrColumn(pReader), plrPosition(pReader),
         plrStartOffset(pReader), plrEndOffset(pReader));
}