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
typedef  int /*<<< orphan*/  fz_pool ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

char *fz_pool_strdup(fz_context *ctx, fz_pool *pool, const char *s)
{
	size_t n = strlen(s) + 1;
	char *p = fz_pool_alloc(ctx, pool, n);
	memcpy(p, s, n);
	return p;
}