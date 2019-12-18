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
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline float
bits_get_float(uint32 bits)
{
	float out;
	StaticAssertStmt(sizeof(float) == sizeof(uint32), "float is not IEEE double wide float");
	/* yes, this is the correct way to extract the bits of a floating point number in C */
	memcpy(&out, &bits, sizeof(uint32));
	return out;
}