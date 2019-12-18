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
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 scalar_t__ abd_is_linear (int /*<<< orphan*/ *) ; 
 unsigned int abd_scatter_bio_map_off (struct bio*,int /*<<< orphan*/ *,unsigned int,size_t) ; 
 scalar_t__ abd_to_buf (int /*<<< orphan*/ *) ; 
 unsigned int bio_map (struct bio*,char*,unsigned int) ; 

__attribute__((used)) static unsigned int
bio_map_abd_off(struct bio *bio, abd_t *abd, unsigned int size, size_t off)
{
	if (abd_is_linear(abd))
		return (bio_map(bio, ((char *)abd_to_buf(abd)) + off, size));

	return (abd_scatter_bio_map_off(bio, abd, size, off));
}