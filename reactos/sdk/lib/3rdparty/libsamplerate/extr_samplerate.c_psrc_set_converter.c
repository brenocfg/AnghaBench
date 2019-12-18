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
typedef  int /*<<< orphan*/  SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_CONVERTER ; 
 scalar_t__ SRC_ERR_NO_ERROR ; 
 scalar_t__ linear_set_converter (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sinc_set_converter (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zoh_set_converter (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
psrc_set_converter (SRC_PRIVATE	*psrc, int converter_type)
{
	if (sinc_set_converter (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	if (zoh_set_converter (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	if (linear_set_converter (psrc, converter_type) == SRC_ERR_NO_ERROR)
		return SRC_ERR_NO_ERROR ;

	return SRC_ERR_BAD_CONVERTER ;
}