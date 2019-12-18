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
struct TYPE_4__ {scalar_t__ nBuffer; int /*<<< orphan*/  iBufferOfst; int /*<<< orphan*/  aBuffer; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 int SQLITE_OK ; 
 int demoDirectWrite (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demoFlushBuffer(DemoFile *p){
  int rc = SQLITE_OK;
  if( p->nBuffer ){
    rc = demoDirectWrite(p, p->aBuffer, p->nBuffer, p->iBufferOfst);
    p->nBuffer = 0;
  }
  return rc;
}