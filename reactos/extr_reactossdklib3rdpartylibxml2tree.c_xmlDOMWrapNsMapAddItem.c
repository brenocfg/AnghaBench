#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* xmlNsPtr ;
typedef  TYPE_1__* xmlNsMapPtr ;
typedef  TYPE_1__* xmlNsMapItemPtr ;
struct xmlNsMapItem {int dummy; } ;
struct xmlNsMap {int dummy; } ;
struct TYPE_6__ {int shadowDepth; int depth; void* newNs; void* oldNs; struct TYPE_6__* first; struct TYPE_6__* next; struct TYPE_6__* prev; struct TYPE_6__* last; struct TYPE_6__* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlTreeErrMemory (char*) ; 

__attribute__((used)) static xmlNsMapItemPtr
xmlDOMWrapNsMapAddItem(xmlNsMapPtr *nsmap, int position,
		       xmlNsPtr oldNs, xmlNsPtr newNs, int depth)
{
    xmlNsMapItemPtr ret;
    xmlNsMapPtr map;

    if (nsmap == NULL)
	return(NULL);
    if ((position != -1) && (position != 0))
	return(NULL);
    map = *nsmap;

    if (map == NULL) {
	/*
	* Create the ns-map.
	*/
	map = (xmlNsMapPtr) xmlMalloc(sizeof(struct xmlNsMap));
	if (map == NULL) {
	    xmlTreeErrMemory("allocating namespace map");
	    return (NULL);
	}
	memset(map, 0, sizeof(struct xmlNsMap));
	*nsmap = map;
    }

    if (map->pool != NULL) {
	/*
	* Reuse an item from the pool.
	*/
	ret = map->pool;
	map->pool = ret->next;
	memset(ret, 0, sizeof(struct xmlNsMapItem));
    } else {
	/*
	* Create a new item.
	*/
	ret = (xmlNsMapItemPtr) xmlMalloc(sizeof(struct xmlNsMapItem));
	if (ret == NULL) {
	    xmlTreeErrMemory("allocating namespace map item");
	    return (NULL);
	}
	memset(ret, 0, sizeof(struct xmlNsMapItem));
    }

    if (map->first == NULL) {
	/*
	* First ever.
	*/
	map->first = ret;
	map->last = ret;
    } else if (position == -1) {
	/*
	* Append.
	*/
	ret->prev = map->last;
	map->last->next = ret;
	map->last = ret;
    } else if (position == 0) {
	/*
	* Set on first position.
	*/
	map->first->prev = ret;
	ret->next = map->first;
	map->first = ret;
    }

    ret->oldNs = oldNs;
    ret->newNs = newNs;
    ret->shadowDepth = -1;
    ret->depth = depth;
    return (ret);
}