#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int key; scalar_t__ tag; } ;
typedef  TYPE_1__ TTree ;

/* Variables and functions */
 scalar_t__ TCall ; 
 scalar_t__ TRule ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sib2 (TYPE_1__*) ; 

__attribute__((used)) static int callrecursive (TTree *tree, int f (TTree *t), int def) {
  int key = tree->key;
  assert(tree->tag == TCall);
  assert(sib2(tree)->tag == TRule);
  if (key == 0)  /* node already visited? */
    return def;  /* return default value */
  else {  /* first visit */
    int result;
    tree->key = 0;  /* mark call as already visited */
    result = f(sib2(tree));  /* go to called rule */
    tree->key = key;  /* restore tree */
    return result;
  }
}