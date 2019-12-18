#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_4__ {scalar_t__ szSector; } ;
typedef  TYPE_1__ LogWriter ;

/* Variables and functions */
 scalar_t__ firstByteOnSector (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static i64 lastByteOnSector(LogWriter *pLog, i64 iOff){
  return firstByteOnSector(pLog, iOff) + pLog->szSector - 1;
}