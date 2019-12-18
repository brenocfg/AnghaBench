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

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool FindSVGmarker(int *position, const uint8_t *data, const int size, const char *marker)
{
    for( int i = *position; i < size; i++)
    {
        if (memcmp(&data[i], marker, strlen(marker)) == 0)
        {
            *position = i;
            return true;
        }
    }
    return false;
}