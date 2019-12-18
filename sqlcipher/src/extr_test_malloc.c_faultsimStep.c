#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ iCountdown; scalar_t__ nFail; scalar_t__ isBenignMode; scalar_t__ nRepeat; scalar_t__ enable; int /*<<< orphan*/  nBenign; int /*<<< orphan*/  nOkBefore; int /*<<< orphan*/  nOkAfter; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 TYPE_1__ memfault ; 
 int /*<<< orphan*/  sqlite3Fault () ; 
 int /*<<< orphan*/  sqlite3FirstFault () ; 

__attribute__((used)) static int faultsimStep(void){
  if( likely(!memfault.enable) ){
    memfault.nOkAfter++;
    return 0;
  }
  if( memfault.iCountdown>0 ){
    memfault.iCountdown--;
    memfault.nOkBefore++;
    return 0;
  }
  if( memfault.nFail==0 ) sqlite3FirstFault();
  sqlite3Fault();
  memfault.nFail++;
  if( memfault.isBenignMode>0 ){
    memfault.nBenign++;
  }
  memfault.nRepeat--;
  if( memfault.nRepeat<=0 ){
    memfault.enable = 0;
  }
  return 1;  
}