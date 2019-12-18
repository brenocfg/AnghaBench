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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  fm_ena_generate_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcpuid () ; 
 int /*<<< orphan*/  kpreempt_disable () ; 
 int /*<<< orphan*/  kpreempt_enable () ; 

uint64_t
fm_ena_generate(uint64_t timestamp, uchar_t format)
{
	uint64_t ena;

	kpreempt_disable();
	ena = fm_ena_generate_cpu(timestamp, getcpuid(), format);
	kpreempt_enable();

	return (ena);
}