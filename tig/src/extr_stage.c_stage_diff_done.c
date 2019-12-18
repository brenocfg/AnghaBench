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
struct line {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LINE_DIFF_CHUNK ; 
 scalar_t__ LINE_DIFF_HEADER ; 

__attribute__((used)) static inline bool
stage_diff_done(struct line *line, struct line *end)
{
	return line >= end ||
	       line->type == LINE_DIFF_CHUNK ||
	       line->type == LINE_DIFF_HEADER;
}