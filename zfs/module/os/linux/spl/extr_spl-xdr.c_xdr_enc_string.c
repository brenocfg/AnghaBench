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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  xdrmem_enc_bytes (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  xdrmem_enc_uint (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static bool_t
xdr_enc_string(XDR *xdrs, char **sp, const uint_t maxsize)
{
	size_t slen = strlen(*sp);
	uint_t len;

	if (slen > maxsize)
		return (FALSE);

	len = slen;

	if (!xdrmem_enc_uint(xdrs, &len))
		return (FALSE);

	return (xdrmem_enc_bytes(xdrs, *sp, len));
}