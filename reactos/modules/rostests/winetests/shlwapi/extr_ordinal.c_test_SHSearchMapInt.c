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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pSHSearchMapInt (int*,int*,int,int) ; 

__attribute__((used)) static void test_SHSearchMapInt(void)
{
  int keys[8], values[8];
  int i = 0;

  if (!pSHSearchMapInt)
    return;

  memset(keys, 0, sizeof(keys));
  memset(values, 0, sizeof(values));
  keys[0] = 99; values[0] = 101;

  /* NULL key/value lists crash native, so skip testing them */

  /* 1 element */
  i = pSHSearchMapInt(keys, values, 1, keys[0]);
  ok(i == values[0], "Len 1, expected %d, got %d\n", values[0], i);

  /* Key doesn't exist */
  i = pSHSearchMapInt(keys, values, 1, 100);
  ok(i == -1, "Len 1 - bad key, expected -1, got %d\n", i);

  /* Len = 0 => not found */
  i = pSHSearchMapInt(keys, values, 0, keys[0]);
  ok(i == -1, "Len 1 - passed len 0, expected -1, got %d\n", i);

  /* 2 elements, len = 1 */
  keys[1] = 98; values[1] = 102;
  i = pSHSearchMapInt(keys, values, 1, keys[1]);
  ok(i == -1, "Len 1 - array len 2, expected -1, got %d\n", i);

  /* 2 elements, len = 2 */
  i = pSHSearchMapInt(keys, values, 2, keys[1]);
  ok(i == values[1], "Len 2, expected %d, got %d\n", values[1], i);

  /* Searches forward */
  keys[2] = 99; values[2] = 103;
  i = pSHSearchMapInt(keys, values, 3, keys[0]);
  ok(i == values[0], "Len 3, expected %d, got %d\n", values[0], i);
}