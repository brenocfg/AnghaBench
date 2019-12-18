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
struct iovec {int dummy; } ;

/* Variables and functions */
 int map_string_field_internal (char const*,char const**,struct iovec**,size_t*,size_t*,int) ; 

__attribute__((used)) static int map_string_field_printable(const char *field, const char **p, struct iovec **iov, size_t *n_iov_allocated, size_t *n_iov) {
        return map_string_field_internal(field, p, iov, n_iov_allocated, n_iov, true);
}