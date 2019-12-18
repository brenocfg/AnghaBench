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
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_3__ {char* za_name; int za_integer_length; int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_num_integers; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int dsl_prop_getflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int DSL_PROP_GET_INHERITING ; 
 int DSL_PROP_GET_LOCAL ; 
 int DSL_PROP_GET_RECEIVED ; 
 int DSL_PROP_GET_SNAPSHOT ; 
 int ENOENT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZAP_MAXNAMELEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  ZPROP_INHERIT_SUFFIX ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_RECVD_SUFFIX ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 char const* ZPROP_SOURCE_VAL_RECVD ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmem_asprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int zap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int /*<<< orphan*/  zfs_prop_inheritable (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_valid_for_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_prop_get_all_impl(objset_t *mos, uint64_t propobj,
    const char *setpoint, dsl_prop_getflags_t flags, nvlist_t *nv)
{
	zap_cursor_t zc;
	zap_attribute_t za;
	int err = 0;

	for (zap_cursor_init(&zc, mos, propobj);
	    (err = zap_cursor_retrieve(&zc, &za)) == 0;
	    zap_cursor_advance(&zc)) {
		nvlist_t *propval;
		zfs_prop_t prop;
		char buf[ZAP_MAXNAMELEN];
		char *valstr;
		const char *suffix;
		const char *propname;
		const char *source;

		suffix = strchr(za.za_name, '$');

		if (suffix == NULL) {
			/*
			 * Skip local properties if we only want received
			 * properties.
			 */
			if (flags & DSL_PROP_GET_RECEIVED)
				continue;

			propname = za.za_name;
			source = setpoint;
		} else if (strcmp(suffix, ZPROP_INHERIT_SUFFIX) == 0) {
			/* Skip explicitly inherited entries. */
			continue;
		} else if (strcmp(suffix, ZPROP_RECVD_SUFFIX) == 0) {
			if (flags & DSL_PROP_GET_LOCAL)
				continue;

			(void) strncpy(buf, za.za_name, (suffix - za.za_name));
			buf[suffix - za.za_name] = '\0';
			propname = buf;

			if (!(flags & DSL_PROP_GET_RECEIVED)) {
				/* Skip if locally overridden. */
				err = zap_contains(mos, propobj, propname);
				if (err == 0)
					continue;
				if (err != ENOENT)
					break;

				/* Skip if explicitly inherited. */
				valstr = kmem_asprintf("%s%s", propname,
				    ZPROP_INHERIT_SUFFIX);
				err = zap_contains(mos, propobj, valstr);
				kmem_strfree(valstr);
				if (err == 0)
					continue;
				if (err != ENOENT)
					break;
			}

			source = ((flags & DSL_PROP_GET_INHERITING) ?
			    setpoint : ZPROP_SOURCE_VAL_RECVD);
		} else {
			/*
			 * For backward compatibility, skip suffixes we don't
			 * recognize.
			 */
			continue;
		}

		prop = zfs_name_to_prop(propname);

		/* Skip non-inheritable properties. */
		if ((flags & DSL_PROP_GET_INHERITING) && prop != ZPROP_INVAL &&
		    !zfs_prop_inheritable(prop))
			continue;

		/* Skip properties not valid for this type. */
		if ((flags & DSL_PROP_GET_SNAPSHOT) && prop != ZPROP_INVAL &&
		    !zfs_prop_valid_for_type(prop, ZFS_TYPE_SNAPSHOT, B_FALSE))
			continue;

		/* Skip properties already defined. */
		if (nvlist_exists(nv, propname))
			continue;

		VERIFY(nvlist_alloc(&propval, NV_UNIQUE_NAME, KM_SLEEP) == 0);
		if (za.za_integer_length == 1) {
			/*
			 * String property
			 */
			char *tmp = kmem_alloc(za.za_num_integers,
			    KM_SLEEP);
			err = zap_lookup(mos, propobj,
			    za.za_name, 1, za.za_num_integers, tmp);
			if (err != 0) {
				kmem_free(tmp, za.za_num_integers);
				break;
			}
			VERIFY(nvlist_add_string(propval, ZPROP_VALUE,
			    tmp) == 0);
			kmem_free(tmp, za.za_num_integers);
		} else {
			/*
			 * Integer property
			 */
			ASSERT(za.za_integer_length == 8);
			(void) nvlist_add_uint64(propval, ZPROP_VALUE,
			    za.za_first_integer);
		}

		VERIFY(nvlist_add_string(propval, ZPROP_SOURCE, source) == 0);
		VERIFY(nvlist_add_nvlist(nv, propname, propval) == 0);
		nvlist_free(propval);
	}
	zap_cursor_fini(&zc);
	if (err == ENOENT)
		err = 0;
	return (err);
}