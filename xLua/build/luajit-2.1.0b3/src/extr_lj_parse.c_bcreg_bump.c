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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ freereg; scalar_t__ framesize; int /*<<< orphan*/  ls; } ;
typedef  TYPE_1__ FuncState ;
typedef  scalar_t__ BCReg ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_ERR_XSLOTS ; 
 scalar_t__ LJ_MAX_SLOTS ; 
 int /*<<< orphan*/  err_syntax (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcreg_bump(FuncState *fs, BCReg n)
{
  BCReg sz = fs->freereg + n;
  if (sz > fs->framesize) {
    if (sz >= LJ_MAX_SLOTS)
      err_syntax(fs->ls, LJ_ERR_XSLOTS);
    fs->framesize = (uint8_t)sz;
  }
}