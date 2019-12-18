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
typedef  int const uint_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KM_NOSLEEP ; 
 scalar_t__ TRUE ; 
 int UINT_MAX ; 
 char* kmem_alloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int const) ; 
 int /*<<< orphan*/ * memchr (char*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  xdrmem_dec_bytes (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  xdrmem_dec_uint (int /*<<< orphan*/ *,int const*) ; 

__attribute__((used)) static bool_t
xdr_dec_string(XDR *xdrs, char **sp, const uint_t maxsize)
{
	uint_t size;
	bool_t alloc = FALSE;

	if (!xdrmem_dec_uint(xdrs, &size))
		return (FALSE);

	if (size > maxsize || size > UINT_MAX - 1)
		return (FALSE);

	/*
	 * Solaris man page: "If *sp is NULL when decoding, xdr_string()
	 * allocates memory and *sp points to it".
	 */
	if (*sp == NULL) {
		BUILD_BUG_ON(sizeof (uint_t) > sizeof (size_t));

		*sp = kmem_alloc(size + 1, KM_NOSLEEP);
		if (*sp == NULL)
			return (FALSE);

		alloc = TRUE;
	}

	if (!xdrmem_dec_bytes(xdrs, *sp, size))
		goto fail;

	if (memchr(*sp, 0, size) != NULL)
		goto fail;

	(*sp)[size] = '\0';

	return (TRUE);

fail:
	if (alloc)
		kmem_free(*sp, size + 1);

	return (FALSE);
}