#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct dentry* dentry; } ;
typedef  TYPE_1__ xattr_filldir_t ;
struct xattr_handler {int /*<<< orphan*/  (* list ) (struct xattr_handler const*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ;} ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dentry*) ; 
 int /*<<< orphan*/  stub2 (struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct xattr_handler const*,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 struct xattr_handler* zpl_xattr_handler (char const*) ; 

__attribute__((used)) static int
zpl_xattr_permission(xattr_filldir_t *xf, const char *name, int name_len)
{
	static const struct xattr_handler *handler;
	struct dentry *d = xf->dentry;

	handler = zpl_xattr_handler(name);
	if (!handler)
		return (0);

	if (handler->list) {
#if defined(HAVE_XATTR_LIST_SIMPLE)
		if (!handler->list(d))
			return (0);
#elif defined(HAVE_XATTR_LIST_DENTRY)
		if (!handler->list(d, NULL, 0, name, name_len, 0))
			return (0);
#elif defined(HAVE_XATTR_LIST_HANDLER)
		if (!handler->list(handler, d, NULL, 0, name, name_len))
			return (0);
#endif
	}

	return (1);
}