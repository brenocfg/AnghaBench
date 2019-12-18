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
struct seq_file {int dummy; } ;
struct list_head {struct list_head* next; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* list_entry (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skc_list ; 
 int /*<<< orphan*/  slab_seq_show_headers (struct seq_file*) ; 
 struct list_head spl_kmem_cache_list ; 
 int /*<<< orphan*/  spl_kmem_cache_sem ; 
 int /*<<< orphan*/  spl_kmem_cache_t ; 

__attribute__((used)) static void *
slab_seq_start(struct seq_file *f, loff_t *pos)
{
	struct list_head *p;
	loff_t n = *pos;

	down_read(&spl_kmem_cache_sem);
	if (!n)
		slab_seq_show_headers(f);

	p = spl_kmem_cache_list.next;
	while (n--) {
		p = p->next;
		if (p == &spl_kmem_cache_list)
			return (NULL);
	}

	return (list_entry(p, spl_kmem_cache_t, skc_list));
}