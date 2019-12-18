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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  Mem ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3VdbeMemSetStr (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,void (*) (void*)) ; 

void sqlite3ValueSetStr(
  sqlite3_value *v,     /* Value to be set */
  int n,                /* Length of string z */
  const void *z,        /* Text of the new string */
  u8 enc,               /* Encoding to use */
  void (*xDel)(void*)   /* Destructor for the string */
){
  if( v ) sqlite3VdbeMemSetStr((Mem *)v, z, n, enc, xDel);
}