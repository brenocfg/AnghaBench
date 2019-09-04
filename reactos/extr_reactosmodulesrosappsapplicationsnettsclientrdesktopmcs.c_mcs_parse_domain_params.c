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
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_TAG_DOMAIN_PARAMS ; 
 int /*<<< orphan*/  ber_parse_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
mcs_parse_domain_params(STREAM s)
{
	int length;

	ber_parse_header(s, MCS_TAG_DOMAIN_PARAMS, &length);
	in_uint8s(s, length);

	return s_check(s);
}