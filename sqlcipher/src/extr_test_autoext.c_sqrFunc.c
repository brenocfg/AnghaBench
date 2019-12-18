#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqrFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  double r = sqlite3_value_double(argv[0]);
  sqlite3_result_double(context, r*r);
}