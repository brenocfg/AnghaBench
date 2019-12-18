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
struct TYPE_3__ {char* member_0; int member_1; } ;
typedef  TYPE_1__ zprop_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROP_DEFAULT ; 
 int /*<<< orphan*/  PROP_ONETIME ; 
 int /*<<< orphan*/  PROP_READONLY ; 
 int /*<<< orphan*/  PROP_TYPE_NUMBER ; 
 int /*<<< orphan*/  PROP_TYPE_STRING ; 
 int const SPA_AUTOTRIM_OFF ; 
 int /*<<< orphan*/  SPA_VERSION ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
#define  ZIO_FAILURE_MODE_CONTINUE 130 
#define  ZIO_FAILURE_MODE_PANIC 129 
#define  ZIO_FAILURE_MODE_WAIT 128 
 int /*<<< orphan*/  ZPOOL_PROP_ALLOCATED ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALTROOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOEXPAND ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOREPLACE ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOTRIM ; 
 int /*<<< orphan*/  ZPOOL_PROP_BOOTFS ; 
 int /*<<< orphan*/  ZPOOL_PROP_CACHEFILE ; 
 int /*<<< orphan*/  ZPOOL_PROP_CAPACITY ; 
 int /*<<< orphan*/  ZPOOL_PROP_CHECKPOINT ; 
 int /*<<< orphan*/  ZPOOL_PROP_COMMENT ; 
 int /*<<< orphan*/  ZPOOL_PROP_DEDUPDITTO ; 
 int /*<<< orphan*/  ZPOOL_PROP_DEDUPRATIO ; 
 int /*<<< orphan*/  ZPOOL_PROP_DELEGATION ; 
 int /*<<< orphan*/  ZPOOL_PROP_EXPANDSZ ; 
 int /*<<< orphan*/  ZPOOL_PROP_FAILUREMODE ; 
 int /*<<< orphan*/  ZPOOL_PROP_FRAGMENTATION ; 
 int /*<<< orphan*/  ZPOOL_PROP_FREE ; 
 int /*<<< orphan*/  ZPOOL_PROP_FREEING ; 
 int /*<<< orphan*/  ZPOOL_PROP_GUID ; 
 int /*<<< orphan*/  ZPOOL_PROP_HEALTH ; 
 int /*<<< orphan*/  ZPOOL_PROP_LEAKED ; 
 int /*<<< orphan*/  ZPOOL_PROP_LISTSNAPS ; 
 int /*<<< orphan*/  ZPOOL_PROP_LOAD_GUID ; 
 int /*<<< orphan*/  ZPOOL_PROP_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_MAXDNODESIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_MULTIHOST ; 
 int /*<<< orphan*/  ZPOOL_PROP_NAME ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 int /*<<< orphan*/  ZPOOL_PROP_SIZE ; 
 int /*<<< orphan*/  ZPOOL_PROP_TNAME ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 int /*<<< orphan*/  zprop_register_hidden (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zprop_register_index (int /*<<< orphan*/ ,char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  zprop_register_number (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  zprop_register_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

void
zpool_prop_init(void)
{
	static zprop_index_t boolean_table[] = {
		{ "off",	0},
		{ "on",		1},
		{ NULL }
	};

	static zprop_index_t failuremode_table[] = {
		{ "wait",	ZIO_FAILURE_MODE_WAIT },
		{ "continue",	ZIO_FAILURE_MODE_CONTINUE },
		{ "panic",	ZIO_FAILURE_MODE_PANIC },
		{ NULL }
	};

	/* string properties */
	zprop_register_string(ZPOOL_PROP_ALTROOT, "altroot", NULL, PROP_DEFAULT,
	    ZFS_TYPE_POOL, "<path>", "ALTROOT");
	zprop_register_string(ZPOOL_PROP_BOOTFS, "bootfs", NULL, PROP_DEFAULT,
	    ZFS_TYPE_POOL, "<filesystem>", "BOOTFS");
	zprop_register_string(ZPOOL_PROP_CACHEFILE, "cachefile", NULL,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "<file> | none", "CACHEFILE");
	zprop_register_string(ZPOOL_PROP_COMMENT, "comment", NULL,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "<comment-string>", "COMMENT");

	/* readonly number properties */
	zprop_register_number(ZPOOL_PROP_SIZE, "size", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<size>", "SIZE");
	zprop_register_number(ZPOOL_PROP_FREE, "free", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<size>", "FREE");
	zprop_register_number(ZPOOL_PROP_FREEING, "freeing", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<size>", "FREEING");
	zprop_register_number(ZPOOL_PROP_CHECKPOINT, "checkpoint", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<size>", "CKPOINT");
	zprop_register_number(ZPOOL_PROP_LEAKED, "leaked", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<size>", "LEAKED");
	zprop_register_number(ZPOOL_PROP_ALLOCATED, "allocated", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<size>", "ALLOC");
	zprop_register_number(ZPOOL_PROP_EXPANDSZ, "expandsize", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<size>", "EXPANDSZ");
	zprop_register_number(ZPOOL_PROP_FRAGMENTATION, "fragmentation", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<percent>", "FRAG");
	zprop_register_number(ZPOOL_PROP_CAPACITY, "capacity", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<size>", "CAP");
	zprop_register_number(ZPOOL_PROP_GUID, "guid", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<guid>", "GUID");
	zprop_register_number(ZPOOL_PROP_LOAD_GUID, "load_guid", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<load_guid>", "LOAD_GUID");
	zprop_register_number(ZPOOL_PROP_HEALTH, "health", 0, PROP_READONLY,
	    ZFS_TYPE_POOL, "<state>", "HEALTH");
	zprop_register_number(ZPOOL_PROP_DEDUPRATIO, "dedupratio", 0,
	    PROP_READONLY, ZFS_TYPE_POOL, "<1.00x or higher if deduped>",
	    "DEDUP");

	/* default number properties */
	zprop_register_number(ZPOOL_PROP_VERSION, "version", SPA_VERSION,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "<version>", "VERSION");
	zprop_register_number(ZPOOL_PROP_ASHIFT, "ashift", 0, PROP_DEFAULT,
	    ZFS_TYPE_POOL, "<ashift, 9-16, or 0=default>", "ASHIFT");

	/* default index (boolean) properties */
	zprop_register_index(ZPOOL_PROP_DELEGATION, "delegation", 1,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "DELEGATION",
	    boolean_table);
	zprop_register_index(ZPOOL_PROP_AUTOREPLACE, "autoreplace", 0,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "REPLACE", boolean_table);
	zprop_register_index(ZPOOL_PROP_LISTSNAPS, "listsnapshots", 0,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "LISTSNAPS",
	    boolean_table);
	zprop_register_index(ZPOOL_PROP_AUTOEXPAND, "autoexpand", 0,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "EXPAND", boolean_table);
	zprop_register_index(ZPOOL_PROP_READONLY, "readonly", 0,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "RDONLY", boolean_table);
	zprop_register_index(ZPOOL_PROP_MULTIHOST, "multihost", 0,
	    PROP_DEFAULT, ZFS_TYPE_POOL, "on | off", "MULTIHOST",
	    boolean_table);

	/* default index properties */
	zprop_register_index(ZPOOL_PROP_FAILUREMODE, "failmode",
	    ZIO_FAILURE_MODE_WAIT, PROP_DEFAULT, ZFS_TYPE_POOL,
	    "wait | continue | panic", "FAILMODE", failuremode_table);
	zprop_register_index(ZPOOL_PROP_AUTOTRIM, "autotrim",
	    SPA_AUTOTRIM_OFF, PROP_DEFAULT, ZFS_TYPE_POOL,
	    "on | off", "AUTOTRIM", boolean_table);

	/* hidden properties */
	zprop_register_hidden(ZPOOL_PROP_NAME, "name", PROP_TYPE_STRING,
	    PROP_READONLY, ZFS_TYPE_POOL, "NAME");
	zprop_register_hidden(ZPOOL_PROP_MAXBLOCKSIZE, "maxblocksize",
	    PROP_TYPE_NUMBER, PROP_READONLY, ZFS_TYPE_POOL, "MAXBLOCKSIZE");
	zprop_register_hidden(ZPOOL_PROP_TNAME, "tname", PROP_TYPE_STRING,
	    PROP_ONETIME, ZFS_TYPE_POOL, "TNAME");
	zprop_register_hidden(ZPOOL_PROP_MAXDNODESIZE, "maxdnodesize",
	    PROP_TYPE_NUMBER, PROP_READONLY, ZFS_TYPE_POOL, "MAXDNODESIZE");
	zprop_register_hidden(ZPOOL_PROP_DEDUPDITTO, "dedupditto",
	    PROP_TYPE_NUMBER, PROP_DEFAULT, ZFS_TYPE_POOL, "DEDUPDITTO");
}