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
struct ibuf {size_t max; } ;

/* Variables and functions */
 struct ibuf* ibuf_open (size_t) ; 

struct ibuf *
ibuf_dynamic(size_t len, size_t max)
{
	struct ibuf	*buf;

	if (max < len)
		return (NULL);

	if ((buf = ibuf_open(len)) == NULL)
		return (NULL);

	if (max > 0)
		buf->max = max;

	return (buf);
}