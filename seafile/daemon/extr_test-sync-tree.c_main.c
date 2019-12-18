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
struct SyncStatusTree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sync_status_tree_add (struct SyncStatusTree*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_status_tree_del (struct SyncStatusTree*,char*) ; 
 int sync_status_tree_exists (struct SyncStatusTree*,char*) ; 
 struct SyncStatusTree* sync_status_tree_new () ; 

int main (int argc, char **argv)
{
    struct SyncStatusTree *tree;
    int val;

    tree = sync_status_tree_new ();

    sync_status_tree_add (tree, "a/b/c.txt", S_IFREG);
    sync_status_tree_add (tree, "a/b/c/d", S_IFDIR);
    sync_status_tree_add (tree, "a/xxx.txt", S_IFREG);

    printf ("test after add\n");

    val = sync_status_tree_exists (tree, "a/b/c.txt");
    printf ("a/b/c.txt: %d\n", val);

    val = sync_status_tree_exists (tree, "a/b/c/d");
    printf ("a/b/c/d: %d\n", val);

    val = sync_status_tree_exists (tree, "a/d/f.foo");
    printf ("a/d/f.foo: %d\n", val);

    val = sync_status_tree_exists (tree, "a/b");
    printf ("a/b: %d\n", val);

    sync_status_tree_del (tree, "a/b/c.txt");
    sync_status_tree_del (tree, "a/b/c/d");
    sync_status_tree_del (tree, "a/xxx.txt");
    sync_status_tree_del (tree, "a/c.pdf");

    printf ("test after del\n");

    val = sync_status_tree_exists (tree, "a/b/c.txt");
    printf ("a/b/c.txt: %d\n", val);

    val = sync_status_tree_exists (tree, "a/b/c/d");
    printf ("a/b/c/d: %d\n", val);

    val = sync_status_tree_exists (tree, "a/b");
    printf ("a/b: %d\n", val);

    val = sync_status_tree_exists (tree, "a");
    printf ("a: %d\n", val);
}