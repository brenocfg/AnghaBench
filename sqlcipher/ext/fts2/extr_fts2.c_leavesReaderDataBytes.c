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
struct TYPE_3__ {int /*<<< orphan*/  leafReader; int /*<<< orphan*/  eof; } ;
typedef  TYPE_1__ LeavesReader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int leafReaderDataBytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int leavesReaderDataBytes(LeavesReader *pReader){
  assert( !pReader->eof );
  return leafReaderDataBytes(&pReader->leafReader);
}