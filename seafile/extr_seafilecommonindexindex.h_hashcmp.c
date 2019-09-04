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
 int memcmp (unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static inline int hashcmp(const unsigned char *sha1, const unsigned char *sha2)
{
    return memcmp(sha1, sha2, 20);
}