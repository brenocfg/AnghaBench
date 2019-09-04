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
 int /*<<< orphan*/  M16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R16 (unsigned char const*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned char const*,int,unsigned char*) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void cvtSM1616K(const unsigned char* src, int ns, unsigned char* dst)
{
    TRACE("(%p, %d, %p)\n", src, ns, dst);

    while (ns--) {
	W16(dst, M16(R16(src),R16(src+2)));	dst += 2;
	src += 4;
    }
}