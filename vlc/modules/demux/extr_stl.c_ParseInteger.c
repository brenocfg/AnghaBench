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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 size_t strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t ParseInteger(uint8_t *data, size_t size)
{
    char tmp[16];
    assert(size < sizeof(tmp));
    memcpy(tmp, data, size);
    tmp[size] = '\0';

    return strtol(tmp, NULL, 10);
}