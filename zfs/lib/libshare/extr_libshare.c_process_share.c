#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__* sa_share_impl_t ;
typedef  TYPE_3__* sa_handle_impl_t ;
struct TYPE_20__ {struct TYPE_20__* next; TYPE_1__* ops; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ sa_fstype_t ;
typedef  void* boolean_t ;
struct TYPE_19__ {TYPE_2__* shares; } ;
struct TYPE_18__ {char* dataset; struct TYPE_18__* next; TYPE_3__* handle; } ;
struct TYPE_17__ {int (* update_shareopts ) (TYPE_2__*,char*,char*) ;} ;
struct TYPE_16__ {char* resource; void* active; } ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 TYPE_13__* FSINFO (TYPE_2__*,TYPE_4__*) ; 
 int SA_BAD_PATH ; 
 int SA_INVALID_PROTOCOL ; 
 int SA_NO_MEMORY ; 
 int SA_OK ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_2__* alloc_share (char*) ; 
 TYPE_2__* find_share (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_share (TYPE_2__*) ; 
 TYPE_4__* fstypes ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 int stub1 (TYPE_2__*,char*,char*) ; 

__attribute__((used)) static int
process_share(sa_handle_impl_t impl_handle, sa_share_impl_t impl_share,
    char *pathname, char *resource, char *proto,
    char *options, char *description, char *dataset,
    boolean_t from_sharetab)
{
	struct stat statbuf;
	int rc;
	char *resource_dup = NULL, *dataset_dup = NULL;
	boolean_t new_share;
	sa_fstype_t *fstype;

	new_share = B_FALSE;

	if (impl_share == NULL)
		impl_share = find_share(impl_handle, pathname);

	if (impl_share == NULL) {
		if (lstat(pathname, &statbuf) != 0 ||
		    !S_ISDIR(statbuf.st_mode))
			return (SA_BAD_PATH);

		impl_share = alloc_share(pathname);

		if (impl_share == NULL) {
			rc = SA_NO_MEMORY;
			goto err;
		}

		new_share = B_TRUE;
	}

	if (dataset != NULL) {
		dataset_dup = strdup(dataset);

		if (dataset_dup == NULL) {
			rc = SA_NO_MEMORY;
			goto err;
		}
	}

	free(impl_share->dataset);
	impl_share->dataset = dataset_dup;

	rc = SA_INVALID_PROTOCOL;

	fstype = fstypes;
	while (fstype != NULL) {
		if (strcmp(fstype->name, proto) == 0) {
			if (resource != NULL) {
				resource_dup = strdup(resource);

				if (resource_dup == NULL) {
					rc = SA_NO_MEMORY;
					goto err;
				}
			}

			free(FSINFO(impl_share, fstype)->resource);
			FSINFO(impl_share, fstype)->resource = resource_dup;

			rc = fstype->ops->update_shareopts(impl_share,
			    resource, options);

			if (rc == SA_OK && from_sharetab)
				FSINFO(impl_share, fstype)->active = B_TRUE;

			break;
		}

		fstype = fstype->next;
	}

	if (rc != SA_OK)
		goto err;

	if (new_share) {
		impl_share->handle = impl_handle;

		impl_share->next = impl_handle->shares;
		impl_handle->shares = impl_share;

	}

err:
	if (rc != SA_OK) {
		if (new_share)
			free_share(impl_share);
	}

	return (rc);
}