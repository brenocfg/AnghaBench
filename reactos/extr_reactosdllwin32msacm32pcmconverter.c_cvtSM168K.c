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
 int /*<<< orphan*/  C168 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R16 (unsigned char const*) ; 
 int /*<<< orphan*/  TRACE (char*,unsigned char const*,int,unsigned char*) ; 

__attribute__((used)) static	void cvtSM168K(const unsigned char* src, int ns, unsigned char* dst)
{
    TRACE("(%p, %d, %p)\n", src, ns, dst);

    while (ns--) {
	*dst++ = C168(M16(R16(src), R16(src + 2)));
	src += 4;
    }
}