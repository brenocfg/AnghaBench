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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void print_speed_test_help(){
  printf(
"\n"
"Repeat the following $repeat times:\n"
"  1. Insert $write key-value pairs. One transaction for each write op.\n"
"  2. Pause for $pause ms.\n"
"  3. Perform $fetch queries on the database.\n"
"\n"
"  Keys are $keysize bytes in size. Values are $valsize bytes in size\n"
"  Both keys and values are pseudo-randomly generated\n"
"\n"
"Options are:\n"
"  -repeat  $repeat                 (default value 10)\n"
"  -write   $write                  (default value 10000)\n"
"  -pause   $pause                  (default value 0)\n"
"  -fetch   $fetch                  (default value 0)\n"
"  -keysize $keysize                (default value 12)\n"
"  -valsize $valsize                (default value 100)\n"
"  -system  $system                 (default value \"lsm\")\n"
"  -trans   $trans                  (default value 0)\n"
"\n"
);
}