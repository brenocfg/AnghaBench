#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int CHARSETINSTSIZE ; 
#define  IBackCommit 139 
#define  ICall 138 
#define  IChoice 137 
#define  ICommit 136 
#define  IJmp 135 
#define  IOpenCall 134 
#define  IPartialCommit 133 
#define  ISet 132 
#define  ISpan 131 
#define  ITestAny 130 
#define  ITestChar 129 
#define  ITestSet 128 

int sizei (const Instruction *i) {
  switch((Opcode)i->i.code) {
    case ISet: case ISpan: return CHARSETINSTSIZE;
    case ITestSet: return CHARSETINSTSIZE + 1;
    case ITestChar: case ITestAny: case IChoice: case IJmp: case ICall:
    case IOpenCall: case ICommit: case IPartialCommit: case IBackCommit:
      return 2;
    default: return 1;
  }
}