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
struct TYPE_4__ {scalar_t__ db; } ;
typedef  TYPE_1__ WorkerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 int /*<<< orphan*/  worker_trace (TYPE_1__*,char*) ; 

__attribute__((used)) static void worker_close_connection(WorkerInfo *p){
  if( p->db ){
    worker_trace(p, "close");
    sqlite3_close(p->db);
    p->db = 0;
  }
}