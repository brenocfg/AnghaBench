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
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_atan2 () ; 
 int /*<<< orphan*/  test_cos () ; 
 int /*<<< orphan*/  test_length () ; 
 int /*<<< orphan*/  test_rotate () ; 
 int /*<<< orphan*/  test_sin () ; 
 int /*<<< orphan*/  test_tan () ; 
 int /*<<< orphan*/  test_unit () ; 

int main( void )
  {
    test_cos();
    test_sin();
    test_tan();
    test_atan2();
    test_unit();
    test_length();
    test_rotate();

    if (!error)
      printf( "trigonometry test ok !\n" );

    return !error;
  }