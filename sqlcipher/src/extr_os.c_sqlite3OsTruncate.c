#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_5__ {int (* xTruncate ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sqlite3OsTruncate(sqlite3_file *id, i64 size){
  return id->pMethods->xTruncate(id, size);
}