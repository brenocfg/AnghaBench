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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_2__ {int /*<<< orphan*/  interp; } ;
typedef  TYPE_1__ echo_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  appendToEchoModule (int /*<<< orphan*/ ,char*) ; 
 int echoDestructor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int echoDisconnect(sqlite3_vtab *pVtab){
  appendToEchoModule(((echo_vtab *)pVtab)->interp, "xDisconnect");
  return echoDestructor(pVtab);
}