#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int freq; int sym; scalar_t__ pathlength; unsigned short code; struct TYPE_9__* right; struct TYPE_9__* parent; struct TYPE_9__* left; } ;
typedef  TYPE_1__ ih_elem ;
struct TYPE_10__ {int codelength; int code; } ;
typedef  TYPE_2__ huff_entry ;
typedef  TYPE_1__ h_elem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_leaves ; 
 int /*<<< orphan*/  cmp_pathlengths ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
build_huffman_tree(int nelem, int max_code_length, int *freq, huff_entry *tree)
{
  h_elem *leaves = malloc(nelem * sizeof(h_elem));
  ih_elem *inodes;
  ih_elem *next_inode;
  ih_elem *cur_inode;
  h_elem *cur_leaf;
  int leaves_left;
  int nleaves;
  int pathlength;
  unsigned short cur_code;
  short codes_too_long = 0;
  ih_elem *f1, *f2;
  int i;

  for (i = 0; i < nelem; i++) {
    leaves[i].freq = freq[i];
    leaves[i].sym = i;
    leaves[i].pathlength = 0;
  }
  qsort(leaves, nelem, sizeof(h_elem), cmp_leaves);
  for (leaves_left = 0; leaves_left < nelem; leaves_left++) {
#ifdef DEBUG_HUFFMAN
    fprintf(stderr, "%3d: %3d '%c'\n", leaves_left, leaves[leaves_left].freq,
	    leaves[leaves_left].sym);
#endif
    if (!leaves[leaves_left].freq) break;
  }
  nleaves = leaves_left;

  if (nleaves >= 2) {
    inodes = malloc((nelem-1) * sizeof(ih_elem));
    do {
      if (codes_too_long) {
	for (leaves_left = 0; leaves_left < nelem; leaves_left++) {
	  if (!leaves[leaves_left].freq) break;
	  if (leaves[leaves_left].freq != 1) {
	    leaves[leaves_left].freq >>= 1;
	    codes_too_long = 0;
	  }
	}
	assert (!codes_too_long);
      }
      
      cur_leaf = leaves;
      next_inode = cur_inode = inodes;
      
      do {
	f1 = f2 = NULL;
	if (leaves_left && 
	    ((cur_inode == next_inode) ||
	     (cur_leaf->freq <= cur_inode->freq))) {
	  f1 = (ih_elem *)cur_leaf++;
	  leaves_left--;
	}
	else if (cur_inode != next_inode) {
	  f1 = cur_inode++;
	}
	
	if (leaves_left && 
	    ((cur_inode == next_inode) ||
	     (cur_leaf->freq <= cur_inode->freq))) {
	  f2 = (ih_elem *)cur_leaf++;
	  leaves_left--;
	}
	else if (cur_inode != next_inode) {
	  f2 = cur_inode++;
	}
	
#ifdef DEBUG_HUFFMAN
	fprintf(stderr, "%d %d\n", f1, f2);
#endif
	if (f1 && f2) {
	  next_inode->freq = f1->freq + f2->freq;
	  next_inode->sym = -1;
	  next_inode->left = f1;
	  next_inode->right = f2;
	  next_inode->parent = NULL;
	  f1->parent = next_inode;
	  f2->parent = next_inode;
	  if (f1->pathlength > f2->pathlength)
	    next_inode->pathlength = f1->pathlength + 1;
	  else
	    next_inode->pathlength = f2->pathlength + 1;
	  if (next_inode->pathlength > max_code_length) {
	    codes_too_long = 1;
	    break;
	  }
	  next_inode++;
	}
      }
      while (f1 && f2);
    }
    while (codes_too_long);
    
#ifdef DEBUG_HUFFMAN
    cur_inode = inodes;
    while (cur_inode < next_inode) {
      fprintf(stderr, "%d l: %3d%c  r: %3d%c  freq: %8d\n", 
	      cur_inode - inodes,
	      (cur_inode->left->sym!=-1)?(((struct h_elem *)cur_inode->left)-leaves):(cur_inode->left-inodes),
	      (cur_inode->left->sym!=-1)?'l':'i',
	      (cur_inode->right->sym!=-1)?(((struct h_elem *)cur_inode->right)-leaves):(cur_inode->right-inodes),
	      (cur_inode->right->sym!=-1)?'l':'i',
	      (cur_inode->freq)
	      );
      cur_inode++;
    }
#endif
    
    /* now traverse tree depth-first */
    cur_inode = next_inode - 1;
    pathlength = 0;
    cur_inode->pathlength = -1;
    do {
      /* precondition: at unmarked node*/
      if (cur_inode->sym == -1) /*&& (cur_inode->left)*/ {
	/* left node of unmarked node is unmarked */
	cur_inode = cur_inode->left;
	cur_inode->pathlength = -1;
	pathlength++;
      }
      else {
	/* mark node */
	cur_inode->pathlength = pathlength;
#if 0 
	if (cur_inode->right) {
	  /* right node of previously unmarked node is unmarked */
	  cur_inode = cur_inode->right;
	  cur_inode->pathlength = -1;
	  pathlength++;
	}
	else 
#endif
	  {
	    
	    /* time to come up.  Keep coming up until an unmarked node is reached */
	    /* or the tree is exhausted */
	    do {
	      cur_inode = cur_inode->parent;
	      pathlength--;
	    }
	    while (cur_inode && (cur_inode->pathlength != -1));
	    if (cur_inode) {
	      /* found unmarked node; mark it and go right */
	      cur_inode->pathlength = pathlength;
	      cur_inode = cur_inode->right;
	      cur_inode->pathlength = -1;
	      pathlength++;
	      /* would be complex if cur_inode could be null here.  It can't */
	    }
	  }
      }
    }
    while (cur_inode);
    
#ifdef DEBUG_HUFFMAN
    cur_inode = inodes;
    while (cur_inode < next_inode) {
      fprintf(stderr, "%d l: %3d%c  r: %3d%c  freq: %8d  pathlength %4d\n", 
	      cur_inode - inodes,
	      (cur_inode->left->sym!=-1)?(((struct h_elem *)cur_inode->left)-leaves):(cur_inode->left-inodes),
	      (cur_inode->left->sym!=-1)?'l':'i',
	      (cur_inode->right->sym!=-1)?(((struct h_elem *)cur_inode->right)-leaves):(cur_inode->right-inodes),
	      (cur_inode->right->sym!=-1)?'l':'i',	
	      (cur_inode->freq),
	      (cur_inode->pathlength)
	      );
      cur_inode++;
    }
#endif
    free(inodes);
    
    /* the pathlengths are already in order, so this sorts by symbol */
    qsort(leaves, nelem, sizeof(h_elem), cmp_pathlengths);
    
    /** 
	Microsoft's second condition on its canonical huffman codes is:

	For each level, starting at the deepest level of the tree and then
	moving upwards, leaf nodes must start as far left as possible. An
	alternative way of stating this constraint is that if any tree node
	has children then all tree nodes to the left of it with the same path
	length must also have children.
	
	These 'alternatives' are not equivalent.  The latter alternative gives
	the common canonical code where the longest code is all zeros.  The former
	gives an opposite code where the longest code is all ones.  Microsoft uses the
	former alternative.
    **/
    
#if 0
    pathlength = leaves[0].pathlength;
    cur_code = 0;
    for (i = 0; i < nleaves; i++) {
      while (leaves[i].pathlength < pathlength) {
	assert(!(cur_code & 1));
	cur_code >>= 1;
	pathlength--;
      }
      leaves[i].code = cur_code;
      cur_code++;
    }
#else
    pathlength = leaves[nleaves-1].pathlength;
    assert(leaves[0].pathlength <= 16); /* this method cannot deal with bigger codes, though
					   the other canonical method can in some cases
					   (because it starts with zeros ) */
    cur_code = 0;
    for (i = nleaves - 1; i >= 0; i--) {
      while (leaves[i].pathlength > pathlength) {
	cur_code <<= 1;
	pathlength++;
      }
      leaves[i].code = cur_code;
      cur_code++;
    }
#endif
    
#ifdef DEBUG_HUFFMAN
    for (i = 0; i < nleaves; i++) {
      char code[18];
      int j;
      
      cur_code = leaves[i].code;
      code[leaves[i].pathlength] = 0;
      for (j = leaves[i].pathlength-1; j >= 0; j--) {
	if (cur_code & 1) code[j] = '1';
	else code[j] = '0';
	cur_code >>= 1;
      }
      fprintf(stderr, "%3d: %3d %3d %-16.16s '%c'\n", i, leaves[i].freq, leaves[i].pathlength, code,
	      leaves[i].sym);
    }
#endif
  }
  else if (nleaves == 1) {
    /* 0 symbols is OK (not according to doc, but according to Caie) */
    /* but if only one symbol is present, two symbols are required */
    nleaves = 2;
    leaves[0].pathlength = leaves[1].pathlength = 1;
    if (leaves[1].sym > leaves[0].sym) {
      leaves[1].code = 1;
      leaves[0].code = 0;
    }
    else {
      leaves[0].code = 1;
      leaves[1].code = 0;
    }
  }
   
  memset(tree, 0, nelem * sizeof(huff_entry));
  for (i = 0; i < nleaves; i++) {
    tree[leaves[i].sym].codelength = leaves[i].pathlength;
    tree[leaves[i].sym].code = leaves[i].code;
  }
  
  free(leaves);
}