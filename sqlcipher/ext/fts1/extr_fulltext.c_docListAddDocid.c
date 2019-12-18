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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_4__ {scalar_t__ iLastPos; } ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 int /*<<< orphan*/  appendVarint (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void docListAddDocid(DocList *d, sqlite_int64 iDocid){
  appendVarint(d, iDocid);
  d->iLastPos = 0;
}