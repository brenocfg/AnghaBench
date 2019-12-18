#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_userquota_prop_t ;
typedef  int /*<<< orphan*/  zfs_sort_column_t ;
typedef  int /*<<< orphan*/  uu_avl_t ;
typedef  int /*<<< orphan*/  uu_avl_pool_t ;
typedef  int /*<<< orphan*/  uu_avl_index_t ;
struct TYPE_11__ {scalar_t__ member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ us_sort_info_t ;
struct TYPE_12__ {int /*<<< orphan*/ * usn_nvl; int /*<<< orphan*/  usn_avlnode; } ;
typedef  TYPE_2__ us_node_t ;
struct TYPE_13__ {scalar_t__ cb_prop; size_t* cb_width; scalar_t__ cb_nicenum; scalar_t__ cb_sid2posix; scalar_t__ cb_numname; int /*<<< orphan*/ * cb_sortcol; int /*<<< orphan*/ * cb_avl; int /*<<< orphan*/ * cb_avl_pool; } ;
typedef  TYPE_3__ us_cbdata_t ;
typedef  int uint64_t ;
typedef  int uid_t ;
typedef  int u_longlong_t ;
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
typedef  int /*<<< orphan*/  sizebuf ;
typedef  int /*<<< orphan*/  sid ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/ * directory_error_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 unsigned int USTYPE_PROJ ; 
 unsigned int USTYPE_PSX_GRP ; 
 unsigned int USTYPE_PSX_USR ; 
 unsigned int USTYPE_SMB_GRP ; 
 unsigned int USTYPE_SMB_USR ; 
 scalar_t__ ZFS_PROP_GROUPOBJQUOTA ; 
 scalar_t__ ZFS_PROP_GROUPOBJUSED ; 
 scalar_t__ ZFS_PROP_GROUPQUOTA ; 
 scalar_t__ ZFS_PROP_GROUPUSED ; 
 scalar_t__ ZFS_PROP_PROJECTOBJQUOTA ; 
 scalar_t__ ZFS_PROP_PROJECTOBJUSED ; 
 scalar_t__ ZFS_PROP_PROJECTQUOTA ; 
 scalar_t__ ZFS_PROP_PROJECTUSED ; 
 scalar_t__ ZFS_PROP_USEROBJQUOTA ; 
 scalar_t__ ZFS_PROP_USEROBJUSED ; 
 scalar_t__ ZFS_PROP_USERQUOTA ; 
 scalar_t__ ZFS_PROP_USERUSED ; 
 int /*<<< orphan*/  directory_error_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * directory_name_from_sid (int /*<<< orphan*/ *,char*,char**,int*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 struct group* getgrgid (int) ; 
 struct passwd* getpwuid (int) ; 
 char* gettext (char const*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ nvlist_add_uint32 (int /*<<< orphan*/ *,char*,unsigned int) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* safe_malloc (int) ; 
 int sid_to_id (char*,int /*<<< orphan*/ ,int*) ; 
 size_t snprintf (char*,int,char*,...) ; 
 size_t strlen (char*) ; 
 int us_field_index (char*) ; 
 char* us_type2str (unsigned int) ; 
 TYPE_2__* uu_avl_find (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_node_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_nicebytes (int,char*,int) ; 
 int /*<<< orphan*/  zfs_nicenum (int,char*,int) ; 
 scalar_t__ zfs_prop_is_group (scalar_t__) ; 
 scalar_t__ zfs_prop_is_user (scalar_t__) ; 

__attribute__((used)) static int
userspace_cb(void *arg, const char *domain, uid_t rid, uint64_t space)
{
	us_cbdata_t *cb = (us_cbdata_t *)arg;
	zfs_userquota_prop_t prop = cb->cb_prop;
	char *name = NULL;
	char *propname;
	char sizebuf[32];
	us_node_t *node;
	uu_avl_pool_t *avl_pool = cb->cb_avl_pool;
	uu_avl_t *avl = cb->cb_avl;
	uu_avl_index_t idx;
	nvlist_t *props;
	us_node_t *n;
	zfs_sort_column_t *sortcol = cb->cb_sortcol;
	unsigned type = 0;
	const char *typestr;
	size_t namelen;
	size_t typelen;
	size_t sizelen;
	int typeidx, nameidx, sizeidx;
	us_sort_info_t sortinfo = { sortcol, cb->cb_numname };
	boolean_t smbentity = B_FALSE;

	if (nvlist_alloc(&props, NV_UNIQUE_NAME, 0) != 0)
		nomem();
	node = safe_malloc(sizeof (us_node_t));
	uu_avl_node_init(node, &node->usn_avlnode, avl_pool);
	node->usn_nvl = props;

	if (domain != NULL && domain[0] != '\0') {
#ifdef HAVE_IDMAP
		/* SMB */
		char sid[MAXNAMELEN + 32];
		uid_t id;
		uint64_t classes;
		int err;
		directory_error_t e;

		smbentity = B_TRUE;

		(void) snprintf(sid, sizeof (sid), "%s-%u", domain, rid);

		if (prop == ZFS_PROP_GROUPUSED || prop == ZFS_PROP_GROUPQUOTA) {
			type = USTYPE_SMB_GRP;
			err = sid_to_id(sid, B_FALSE, &id);
		} else {
			type = USTYPE_SMB_USR;
			err = sid_to_id(sid, B_TRUE, &id);
		}

		if (err == 0) {
			rid = id;
			if (!cb->cb_sid2posix) {
				e = directory_name_from_sid(NULL, sid, &name,
				    &classes);
				if (e != NULL)
					directory_error_free(e);
				if (name == NULL)
					name = sid;
			}
		}
#else
		nvlist_free(props);
		free(node);

		return (-1);
#endif /* HAVE_IDMAP */
	}

	if (cb->cb_sid2posix || domain == NULL || domain[0] == '\0') {
		/* POSIX or -i */
		if (zfs_prop_is_group(prop)) {
			type = USTYPE_PSX_GRP;
			if (!cb->cb_numname) {
				struct group *g;

				if ((g = getgrgid(rid)) != NULL)
					name = g->gr_name;
			}
		} else if (zfs_prop_is_user(prop)) {
			type = USTYPE_PSX_USR;
			if (!cb->cb_numname) {
				struct passwd *p;

				if ((p = getpwuid(rid)) != NULL)
					name = p->pw_name;
			}
		} else {
			type = USTYPE_PROJ;
		}
	}

	/*
	 * Make sure that the type/name combination is unique when doing
	 * SID to POSIX ID translation (hence changing the type from SMB to
	 * POSIX).
	 */
	if (cb->cb_sid2posix &&
	    nvlist_add_boolean_value(props, "smbentity", smbentity) != 0)
		nomem();

	/* Calculate/update width of TYPE field */
	typestr = us_type2str(type);
	typelen = strlen(gettext(typestr));
	typeidx = us_field_index("type");
	if (typelen > cb->cb_width[typeidx])
		cb->cb_width[typeidx] = typelen;
	if (nvlist_add_uint32(props, "type", type) != 0)
		nomem();

	/* Calculate/update width of NAME field */
	if ((cb->cb_numname && cb->cb_sid2posix) || name == NULL) {
		if (nvlist_add_uint64(props, "name", rid) != 0)
			nomem();
		namelen = snprintf(NULL, 0, "%u", rid);
	} else {
		if (nvlist_add_string(props, "name", name) != 0)
			nomem();
		namelen = strlen(name);
	}
	nameidx = us_field_index("name");
	if (nameidx >= 0 && namelen > cb->cb_width[nameidx])
		cb->cb_width[nameidx] = namelen;

	/*
	 * Check if this type/name combination is in the list and update it;
	 * otherwise add new node to the list.
	 */
	if ((n = uu_avl_find(avl, node, &sortinfo, &idx)) == NULL) {
		uu_avl_insert(avl, node, idx);
	} else {
		nvlist_free(props);
		free(node);
		node = n;
		props = node->usn_nvl;
	}

	/* Calculate/update width of USED/QUOTA fields */
	if (cb->cb_nicenum) {
		if (prop == ZFS_PROP_USERUSED || prop == ZFS_PROP_GROUPUSED ||
		    prop == ZFS_PROP_USERQUOTA || prop == ZFS_PROP_GROUPQUOTA ||
		    prop == ZFS_PROP_PROJECTUSED ||
		    prop == ZFS_PROP_PROJECTQUOTA) {
			zfs_nicebytes(space, sizebuf, sizeof (sizebuf));
		} else {
			zfs_nicenum(space, sizebuf, sizeof (sizebuf));
		}
	} else {
		(void) snprintf(sizebuf, sizeof (sizebuf), "%llu",
		    (u_longlong_t)space);
	}
	sizelen = strlen(sizebuf);
	if (prop == ZFS_PROP_USERUSED || prop == ZFS_PROP_GROUPUSED ||
	    prop == ZFS_PROP_PROJECTUSED) {
		propname = "used";
		if (!nvlist_exists(props, "quota"))
			(void) nvlist_add_uint64(props, "quota", 0);
	} else if (prop == ZFS_PROP_USERQUOTA || prop == ZFS_PROP_GROUPQUOTA ||
	    prop == ZFS_PROP_PROJECTQUOTA) {
		propname = "quota";
		if (!nvlist_exists(props, "used"))
			(void) nvlist_add_uint64(props, "used", 0);
	} else if (prop == ZFS_PROP_USEROBJUSED ||
	    prop == ZFS_PROP_GROUPOBJUSED || prop == ZFS_PROP_PROJECTOBJUSED) {
		propname = "objused";
		if (!nvlist_exists(props, "objquota"))
			(void) nvlist_add_uint64(props, "objquota", 0);
	} else if (prop == ZFS_PROP_USEROBJQUOTA ||
	    prop == ZFS_PROP_GROUPOBJQUOTA ||
	    prop == ZFS_PROP_PROJECTOBJQUOTA) {
		propname = "objquota";
		if (!nvlist_exists(props, "objused"))
			(void) nvlist_add_uint64(props, "objused", 0);
	} else {
		return (-1);
	}
	sizeidx = us_field_index(propname);
	if (sizeidx >= 0 && sizelen > cb->cb_width[sizeidx])
		cb->cb_width[sizeidx] = sizelen;

	if (nvlist_add_uint64(props, propname, space) != 0)
		nomem();

	return (0);
}