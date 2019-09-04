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
struct chmcTreeNode {int sect_id; int /*<<< orphan*/  list; void* len; void* offset; int /*<<< orphan*/ * buf; int /*<<< orphan*/  prefixlen; int /*<<< orphan*/  name; scalar_t__ flags; } ;
struct chmcFile {int sections_num; int /*<<< orphan*/  entries_num; int /*<<< orphan*/  entries_list; } ;
typedef  void* UInt64 ;
typedef  int /*<<< orphan*/  UInt16 ;
typedef  int /*<<< orphan*/  UChar ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (char*,char*,int) ; 
 int /*<<< orphan*/  assert (struct chmcFile*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct chmcTreeNode* malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct chmcTreeNode *chmc_add_entry(struct chmcFile *chm, const char *name,
                                    UInt16 prefixlen, int sect_id, UChar *buf,
                                    UInt64 offset, UInt64 len)
{
	struct chmcTreeNode *node;

	assert(chm);

	if (sect_id >= (chm->sections_num)) {
		fprintf(stderr,"sect_id %d >= chm->sections_num %d\n",
		        sect_id, chm->sections_num);
		return NULL;
	}

	node = malloc(sizeof(struct chmcTreeNode));
	if (node) {
		node->flags = 0;
		node->name = strdup( name );
		node->prefixlen = prefixlen;
		node->sect_id = sect_id;
		node->buf = buf;
		node->offset = offset;
		node->len = len;
		list_add_tail(&node->list, &chm->entries_list);
		chm->entries_num++;
	}
	else
		BUG_ON("FIXME: %s: %d\n", __FILE__, __LINE__);

	return node;
}