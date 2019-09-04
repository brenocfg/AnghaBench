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
 int /*<<< orphan*/  C2416 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R24 (unsigned char const*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned char const*,int,unsigned char*) ; 
 int /*<<< orphan*/  W16 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void cvtSM2416K(const unsigned char* src, int ns, unsigned char* dst)
{
    TRACE("(%p, %d, %p)\n", src, ns, dst);

    while (ns--) {
	W16(dst, C2416(M24(R24(src), R24(src + 3))));
	dst += 2;
	src += 6;
    }
}