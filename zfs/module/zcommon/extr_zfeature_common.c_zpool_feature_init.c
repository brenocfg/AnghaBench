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
typedef  int /*<<< orphan*/  spa_feature_t ;

/* Variables and functions */
 int /*<<< orphan*/  const SPA_FEATURE_ALLOCATION_CLASSES ; 
 int /*<<< orphan*/  const SPA_FEATURE_ASYNC_DESTROY ; 
#define  SPA_FEATURE_BOOKMARKS 134 
#define  SPA_FEATURE_BOOKMARK_V2 133 
 int /*<<< orphan*/  const SPA_FEATURE_BOOKMARK_WRITTEN ; 
#define  SPA_FEATURE_DEVICE_REMOVAL 132 
 int /*<<< orphan*/  const SPA_FEATURE_EDONR ; 
 int /*<<< orphan*/  const SPA_FEATURE_EMBEDDED_DATA ; 
 int /*<<< orphan*/  const SPA_FEATURE_EMPTY_BPOBJ ; 
#define  SPA_FEATURE_ENABLED_TXG 131 
 int /*<<< orphan*/  const SPA_FEATURE_ENCRYPTION ; 
#define  SPA_FEATURE_EXTENSIBLE_DATASET 130 
 int /*<<< orphan*/  const SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  const SPA_FEATURE_HOLE_BIRTH ; 
 int /*<<< orphan*/  const SPA_FEATURE_LARGE_BLOCKS ; 
 int /*<<< orphan*/  const SPA_FEATURE_LARGE_DNODE ; 
 int /*<<< orphan*/  const SPA_FEATURE_LIVELIST ; 
 int /*<<< orphan*/  const SPA_FEATURE_LOG_SPACEMAP ; 
 int /*<<< orphan*/  const SPA_FEATURE_LZ4_COMPRESS ; 
 int /*<<< orphan*/  const SPA_FEATURE_MULTI_VDEV_CRASH_DUMP ; 
#define  SPA_FEATURE_NONE 129 
 int /*<<< orphan*/  const SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  const SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  const SPA_FEATURE_PROJECT_QUOTA ; 
 int /*<<< orphan*/  const SPA_FEATURE_REDACTED_DATASETS ; 
 int /*<<< orphan*/  const SPA_FEATURE_REDACTION_BOOKMARKS ; 
 int /*<<< orphan*/  const SPA_FEATURE_RESILVER_DEFER ; 
 int /*<<< orphan*/  const SPA_FEATURE_SHA512 ; 
 int /*<<< orphan*/  const SPA_FEATURE_SKEIN ; 
 int /*<<< orphan*/  const SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
#define  SPA_FEATURE_SPACEMAP_V2 128 
 int /*<<< orphan*/  const SPA_FEATURE_USEROBJ_ACCOUNTING ; 
 int ZFEATURE_FLAG_ACTIVATE_ON_ENABLE ; 
 int ZFEATURE_FLAG_MOS ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 int ZFEATURE_FLAG_READONLY_COMPAT ; 
 int /*<<< orphan*/  ZFEATURE_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  ZFEATURE_TYPE_UINT64_ARRAY ; 
 int /*<<< orphan*/  zfeature_register (int /*<<< orphan*/  const,char*,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void
zpool_feature_init(void)
{
	zfeature_register(SPA_FEATURE_ASYNC_DESTROY,
	    "com.delphix:async_destroy", "async_destroy",
	    "Destroy filesystems asynchronously.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_EMPTY_BPOBJ,
	    "com.delphix:empty_bpobj", "empty_bpobj",
	    "Snapshots use less space.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_LZ4_COMPRESS,
	    "org.illumos:lz4_compress", "lz4_compress",
	    "LZ4 compression algorithm support.",
	    ZFEATURE_FLAG_ACTIVATE_ON_ENABLE, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_MULTI_VDEV_CRASH_DUMP,
	    "com.joyent:multi_vdev_crash_dump", "multi_vdev_crash_dump",
	    "Crash dumps to multiple vdev pools.",
	    0, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_SPACEMAP_HISTOGRAM,
	    "com.delphix:spacemap_histogram", "spacemap_histogram",
	    "Spacemaps maintain space histograms.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_ENABLED_TXG,
	    "com.delphix:enabled_txg", "enabled_txg",
	    "Record txg at which a feature is enabled",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);

	{
	static const spa_feature_t hole_birth_deps[] = {
		SPA_FEATURE_ENABLED_TXG,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_HOLE_BIRTH,
	    "com.delphix:hole_birth", "hole_birth",
	    "Retain hole birth txg for more precise zfs send",
	    ZFEATURE_FLAG_MOS | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    ZFEATURE_TYPE_BOOLEAN, hole_birth_deps);
	}

	zfeature_register(SPA_FEATURE_POOL_CHECKPOINT,
	    "com.delphix:zpool_checkpoint", "zpool_checkpoint",
	    "Pool state can be checkpointed, allowing rewind later.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_SPACEMAP_V2,
	    "com.delphix:spacemap_v2", "spacemap_v2",
	    "Space maps representing large segments are more efficient.",
	    ZFEATURE_FLAG_READONLY_COMPAT | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    ZFEATURE_TYPE_BOOLEAN, NULL);

	zfeature_register(SPA_FEATURE_EXTENSIBLE_DATASET,
	    "com.delphix:extensible_dataset", "extensible_dataset",
	    "Enhanced dataset functionality, used by other features.",
	    0, ZFEATURE_TYPE_BOOLEAN, NULL);

	{
	static const spa_feature_t bookmarks_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};

	zfeature_register(SPA_FEATURE_BOOKMARKS,
	    "com.delphix:bookmarks", "bookmarks",
	    "\"zfs bookmark\" command",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN,
	    bookmarks_deps);
	}

	{
	static const spa_feature_t filesystem_limits_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_FS_SS_LIMIT,
	    "com.joyent:filesystem_limits", "filesystem_limits",
	    "Filesystem and snapshot limits.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN,
	    filesystem_limits_deps);
	}

	zfeature_register(SPA_FEATURE_EMBEDDED_DATA,
	    "com.delphix:embedded_data", "embedded_data",
	    "Blocks which compress very well use even less space.",
	    ZFEATURE_FLAG_MOS | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    ZFEATURE_TYPE_BOOLEAN, NULL);

	{
	static const spa_feature_t livelist_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LIVELIST,
	    "com.delphix:livelist", "livelist",
	    "Improved clone deletion performance.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN,
	    livelist_deps);
	}

	{
	static const spa_feature_t log_spacemap_deps[] = {
		SPA_FEATURE_SPACEMAP_V2,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LOG_SPACEMAP,
	    "com.delphix:log_spacemap", "log_spacemap",
	    "Log metaslab changes on a single spacemap and "
	    "flush them periodically.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN,
	    log_spacemap_deps);
	}

	{
	static const spa_feature_t large_blocks_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LARGE_BLOCKS,
	    "org.open-zfs:large_blocks", "large_blocks",
	    "Support for blocks larger than 128KB.",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    large_blocks_deps);
	}

	{
	static const spa_feature_t large_dnode_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LARGE_DNODE,
	    "org.zfsonlinux:large_dnode", "large_dnode",
	    "Variable on-disk size of dnodes.",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    large_dnode_deps);
	}

	{
	static const spa_feature_t sha512_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_SHA512,
	    "org.illumos:sha512", "sha512",
	    "SHA-512/256 hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    sha512_deps);
	}

	{
	static const spa_feature_t skein_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_SKEIN,
	    "org.illumos:skein", "skein",
	    "Skein hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    skein_deps);
	}

	{
	static const spa_feature_t edonr_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_EDONR,
	    "org.illumos:edonr", "edonr",
	    "Edon-R hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    edonr_deps);
	}

	{
	static const spa_feature_t redact_books_deps[] = {
		SPA_FEATURE_BOOKMARK_V2,
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_BOOKMARKS,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_REDACTION_BOOKMARKS,
	    "com.delphix:redaction_bookmarks", "redaction_bookmarks",
	    "Support for bookmarks which store redaction lists for zfs "
	    "redacted send/recv.", 0, ZFEATURE_TYPE_BOOLEAN,
	    redact_books_deps);
	}

	{
	static const spa_feature_t redact_datasets_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_REDACTED_DATASETS,
	    "com.delphix:redacted_datasets", "redacted_datasets", "Support for "
	    "redacted datasets, produced by receiving a redacted zfs send "
	    "stream.", ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_UINT64_ARRAY,
	    redact_datasets_deps);
	}

	{
	static const spa_feature_t bookmark_written_deps[] = {
		SPA_FEATURE_BOOKMARK_V2,
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_BOOKMARKS,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_BOOKMARK_WRITTEN,
	    "com.delphix:bookmark_written", "bookmark_written",
	    "Additional accounting, enabling the written#<bookmark> property"
	    "(space written since a bookmark), and estimates of send stream "
	    "sizes for incrementals from bookmarks.",
	    0, ZFEATURE_TYPE_BOOLEAN, bookmark_written_deps);
	}

	zfeature_register(SPA_FEATURE_DEVICE_REMOVAL,
	    "com.delphix:device_removal", "device_removal",
	    "Top-level vdevs can be removed, reducing logical pool size.",
	    ZFEATURE_FLAG_MOS, ZFEATURE_TYPE_BOOLEAN, NULL);

	{
	static const spa_feature_t obsolete_counts_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_DEVICE_REMOVAL,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_OBSOLETE_COUNTS,
	    "com.delphix:obsolete_counts", "obsolete_counts",
	    "Reduce memory used by removed devices when their blocks are "
	    "freed or remapped.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN,
	    obsolete_counts_deps);
	}

	{
	static const spa_feature_t userobj_accounting_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_USEROBJ_ACCOUNTING,
	    "org.zfsonlinux:userobj_accounting", "userobj_accounting",
	    "User/Group object accounting.",
	    ZFEATURE_FLAG_READONLY_COMPAT | ZFEATURE_FLAG_PER_DATASET,
	    ZFEATURE_TYPE_BOOLEAN, userobj_accounting_deps);
	}

	{
	static const spa_feature_t bookmark_v2_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_BOOKMARKS,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_BOOKMARK_V2,
	    "com.datto:bookmark_v2", "bookmark_v2",
	    "Support for larger bookmarks",
	    0, ZFEATURE_TYPE_BOOLEAN, bookmark_v2_deps);
	}

	{
	static const spa_feature_t encryption_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_BOOKMARK_V2,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_ENCRYPTION,
	    "com.datto:encryption", "encryption",
	    "Support for dataset level encryption",
	    ZFEATURE_FLAG_PER_DATASET, ZFEATURE_TYPE_BOOLEAN,
	    encryption_deps);
	}

	{
	static const spa_feature_t project_quota_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_PROJECT_QUOTA,
	    "org.zfsonlinux:project_quota", "project_quota",
	    "space/object accounting based on project ID.",
	    ZFEATURE_FLAG_READONLY_COMPAT | ZFEATURE_FLAG_PER_DATASET,
	    ZFEATURE_TYPE_BOOLEAN, project_quota_deps);
	}

	{
	zfeature_register(SPA_FEATURE_ALLOCATION_CLASSES,
	    "org.zfsonlinux:allocation_classes", "allocation_classes",
	    "Support for separate allocation classes.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);
	}

	zfeature_register(SPA_FEATURE_RESILVER_DEFER,
	    "com.datto:resilver_defer", "resilver_defer",
	    "Support for deferring new resilvers when one is already running.",
	    ZFEATURE_FLAG_READONLY_COMPAT, ZFEATURE_TYPE_BOOLEAN, NULL);
}