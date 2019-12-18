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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t mpi_len (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static size_t read_mpi(uint8_t *dst, const uint8_t *buf, size_t buflen, size_t bits)
{
    if (buflen < 2)
        return 0;

    size_t n = mpi_len(buf);

    if (n * 8 > bits)
        return 0;

    n += 2;

    if (buflen < n)
        return 0;

    memcpy(dst, buf, n);
    return n;
}