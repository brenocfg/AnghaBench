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
typedef  TYPE_1__* xmlDictPtr ;
typedef  TYPE_2__* xmlDictEntryPtr ;
typedef  int /*<<< orphan*/  xmlDictEntry ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_10__ {scalar_t__ valid; unsigned long okey; unsigned int len; struct TYPE_10__* next; int /*<<< orphan*/  const* name; } ;
struct TYPE_9__ {unsigned long size; int /*<<< orphan*/  nbElems; TYPE_2__* dict; struct TYPE_9__* subdict; } ;

/* Variables and functions */
 int MAX_DICT_HASH ; 
 unsigned long MAX_HASH_LEN ; 
 unsigned long MIN_DICT_SIZE ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/ * xmlDictAddQString (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned long xmlDictComputeQKey (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  xmlDictGrow (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  const* xmlDictLookup (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 TYPE_2__* xmlMalloc (int) ; 
 scalar_t__ xmlStrQEqual (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

const xmlChar *
xmlDictQLookup(xmlDictPtr dict, const xmlChar *prefix, const xmlChar *name) {
    unsigned long okey, key, nbi = 0;
    xmlDictEntryPtr entry;
    xmlDictEntryPtr insert;
    const xmlChar *ret;
    unsigned int len, plen, l;

    if ((dict == NULL) || (name == NULL))
	return(NULL);
    if (prefix == NULL)
        return(xmlDictLookup(dict, name, -1));

    l = len = strlen((const char *) name);
    plen = strlen((const char *) prefix);
    len += 1 + plen;

    /*
     * Check for duplicate and insertion location.
     */
    okey = xmlDictComputeQKey(dict, prefix, plen, name, l);
    key = okey % dict->size;
    if (dict->dict[key].valid == 0) {
	insert = NULL;
    } else {
	for (insert = &(dict->dict[key]); insert->next != NULL;
	     insert = insert->next) {
	    if ((insert->okey == okey) && (insert->len == len) &&
	        (xmlStrQEqual(prefix, name, insert->name)))
		return(insert->name);
	    nbi++;
	}
	if ((insert->okey == okey) && (insert->len == len) &&
	    (xmlStrQEqual(prefix, name, insert->name)))
	    return(insert->name);
    }

    if (dict->subdict) {
        unsigned long skey;

        /* we cannot always reuse the same okey for the subdict */
        if (((dict->size == MIN_DICT_SIZE) &&
	     (dict->subdict->size != MIN_DICT_SIZE)) ||
            ((dict->size != MIN_DICT_SIZE) &&
	     (dict->subdict->size == MIN_DICT_SIZE)))
	    skey = xmlDictComputeQKey(dict->subdict, prefix, plen, name, l);
	else
	    skey = okey;

	key = skey % dict->subdict->size;
	if (dict->subdict->dict[key].valid != 0) {
	    xmlDictEntryPtr tmp;
	    for (tmp = &(dict->subdict->dict[key]); tmp->next != NULL;
		 tmp = tmp->next) {
		if ((tmp->okey == skey) && (tmp->len == len) &&
		    (xmlStrQEqual(prefix, name, tmp->name)))
		    return(tmp->name);
		nbi++;
	    }
	    if ((tmp->okey == skey) && (tmp->len == len) &&
		(xmlStrQEqual(prefix, name, tmp->name)))
		return(tmp->name);
	}
	key = okey % dict->size;
    }

    ret = xmlDictAddQString(dict, prefix, plen, name, l);
    if (ret == NULL)
        return(NULL);
    if (insert == NULL) {
	entry = &(dict->dict[key]);
    } else {
	entry = xmlMalloc(sizeof(xmlDictEntry));
	if (entry == NULL)
	     return(NULL);
    }
    entry->name = ret;
    entry->len = len;
    entry->next = NULL;
    entry->valid = 1;
    entry->okey = okey;

    if (insert != NULL)
	insert->next = entry;

    dict->nbElems++;

    if ((nbi > MAX_HASH_LEN) &&
        (dict->size <= ((MAX_DICT_HASH / 2) / MAX_HASH_LEN)))
	xmlDictGrow(dict, MAX_HASH_LEN * 2 * dict->size);
    /* Note that entry may have been freed at this point by xmlDictGrow */

    return(ret);
}