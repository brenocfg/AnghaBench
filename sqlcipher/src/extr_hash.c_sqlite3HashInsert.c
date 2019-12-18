#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int count; int htsize; int /*<<< orphan*/ * ht; } ;
struct TYPE_11__ {char const* pKey; void* data; } ;
typedef  TYPE_1__ HashElem ;
typedef  TYPE_2__ Hash ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* findElementWithHash (TYPE_2__*,char const*,unsigned int*) ; 
 int /*<<< orphan*/  insertElement (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ rehash (TYPE_2__*,int) ; 
 int /*<<< orphan*/  removeElementGivenHash (TYPE_2__*,TYPE_1__*,unsigned int) ; 
 scalar_t__ sqlite3Malloc (int) ; 
 unsigned int strHash (char const*) ; 

void *sqlite3HashInsert(Hash *pH, const char *pKey, void *data){
  unsigned int h;       /* the hash of the key modulo hash table size */
  HashElem *elem;       /* Used to loop thru the element list */
  HashElem *new_elem;   /* New element added to the pH */

  assert( pH!=0 );
  assert( pKey!=0 );
  elem = findElementWithHash(pH,pKey,&h);
  if( elem->data ){
    void *old_data = elem->data;
    if( data==0 ){
      removeElementGivenHash(pH,elem,h);
    }else{
      elem->data = data;
      elem->pKey = pKey;
    }
    return old_data;
  }
  if( data==0 ) return 0;
  new_elem = (HashElem*)sqlite3Malloc( sizeof(HashElem) );
  if( new_elem==0 ) return data;
  new_elem->pKey = pKey;
  new_elem->data = data;
  pH->count++;
  if( pH->count>=10 && pH->count > 2*pH->htsize ){
    if( rehash(pH, pH->count*2) ){
      assert( pH->htsize>0 );
      h = strHash(pKey) % pH->htsize;
    }
  }
  insertElement(pH, pH->ht ? &pH->ht[h] : 0, new_elem);
  return 0;
}