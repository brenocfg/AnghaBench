#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* aNode; int nNode; int iOff; int /*<<< orphan*/  iChild; } ;
typedef  TYPE_1__ NodeReader ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int nodeReaderNext (TYPE_1__*) ; 
 int sqlite3Fts3GetVarint (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nodeReaderInit(NodeReader *p, const char *aNode, int nNode){
  memset(p, 0, sizeof(NodeReader));
  p->aNode = aNode;
  p->nNode = nNode;

  /* Figure out if this is a leaf or an internal node. */
  if( p->aNode[0] ){
    /* An internal node. */
    p->iOff = 1 + sqlite3Fts3GetVarint(&p->aNode[1], &p->iChild);
  }else{
    p->iOff = 1;
  }

  return nodeReaderNext(p);
}