#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlDictPtr ;
typedef  TYPE_2__* xmlDictEntryPtr ;
typedef  int /*<<< orphan*/  xmlDictEntry ;
typedef  int /*<<< orphan*/  xmlChar ;
struct TYPE_9__ {scalar_t__ valid; unsigned long okey; unsigned int len; struct TYPE_9__* next; int /*<<< orphan*/  const* name; } ;
struct TYPE_8__ {unsigned int limit; unsigned long size; int /*<<< orphan*/  nbElems; TYPE_2__* dict; struct TYPE_8__* subdict; } ;

/* Variables and functions */
 int INT_MAX ; 
 int MAX_DICT_HASH ; 
 unsigned long MAX_HASH_LEN ; 
 unsigned long MIN_DICT_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/ * xmlDictAddString (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned long xmlDictComputeKey (TYPE_1__*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ xmlDictGrow (TYPE_1__*,unsigned long) ; 
 TYPE_2__* xmlMalloc (int) ; 
 int /*<<< orphan*/  xmlStrncmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

const xmlChar *
xmlDictLookup(xmlDictPtr dict, const xmlChar *name, int len) {
    unsigned long key, okey, nbi = 0;
    xmlDictEntryPtr entry;
    xmlDictEntryPtr insert;
    const xmlChar *ret;
    unsigned int l;

    if ((dict == NULL) || (name == NULL))
	return(NULL);

    if (len < 0)
        l = strlen((const char *) name);
    else
        l = len;

    if (((dict->limit > 0) && (l >= dict->limit)) ||
        (l > INT_MAX / 2))
        return(NULL);

    /*
     * Check for duplicate and insertion location.
     */
    okey = xmlDictComputeKey(dict, name, l);
    key = okey % dict->size;
    if (dict->dict[key].valid == 0) {
	insert = NULL;
    } else {
	for (insert = &(dict->dict[key]); insert->next != NULL;
	     insert = insert->next) {
#ifdef __GNUC__
	    if ((insert->okey == okey) && (insert->len == l)) {
		if (!memcmp(insert->name, name, l))
		    return(insert->name);
	    }
#else
	    if ((insert->okey == okey) && (insert->len == l) &&
	        (!xmlStrncmp(insert->name, name, l)))
		return(insert->name);
#endif
	    nbi++;
	}
#ifdef __GNUC__
	if ((insert->okey == okey) && (insert->len == l)) {
	    if (!memcmp(insert->name, name, l))
		return(insert->name);
	}
#else
	if ((insert->okey == okey) && (insert->len == l) &&
	    (!xmlStrncmp(insert->name, name, l)))
	    return(insert->name);
#endif
    }

    if (dict->subdict) {
        unsigned long skey;

        /* we cannot always reuse the same okey for the subdict */
        if (((dict->size == MIN_DICT_SIZE) &&
	     (dict->subdict->size != MIN_DICT_SIZE)) ||
            ((dict->size != MIN_DICT_SIZE) &&
	     (dict->subdict->size == MIN_DICT_SIZE)))
	    skey = xmlDictComputeKey(dict->subdict, name, l);
	else
	    skey = okey;

	key = skey % dict->subdict->size;
	if (dict->subdict->dict[key].valid != 0) {
	    xmlDictEntryPtr tmp;

	    for (tmp = &(dict->subdict->dict[key]); tmp->next != NULL;
		 tmp = tmp->next) {
#ifdef __GNUC__
		if ((tmp->okey == skey) && (tmp->len == l)) {
		    if (!memcmp(tmp->name, name, l))
			return(tmp->name);
		}
#else
		if ((tmp->okey == skey) && (tmp->len == l) &&
		    (!xmlStrncmp(tmp->name, name, l)))
		    return(tmp->name);
#endif
		nbi++;
	    }
#ifdef __GNUC__
	    if ((tmp->okey == skey) && (tmp->len == l)) {
		if (!memcmp(tmp->name, name, l))
		    return(tmp->name);
	    }
#else
	    if ((tmp->okey == skey) && (tmp->len == l) &&
		(!xmlStrncmp(tmp->name, name, l)))
		return(tmp->name);
#endif
	}
	key = okey % dict->size;
    }

    ret = xmlDictAddString(dict, name, l);
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
    entry->len = l;
    entry->next = NULL;
    entry->valid = 1;
    entry->okey = okey;


    if (insert != NULL)
	insert->next = entry;

    dict->nbElems++;

    if ((nbi > MAX_HASH_LEN) &&
        (dict->size <= ((MAX_DICT_HASH / 2) / MAX_HASH_LEN))) {
	if (xmlDictGrow(dict, MAX_HASH_LEN * 2 * dict->size) != 0)
	    return(NULL);
    }
    /* Note that entry may have been freed at this point by xmlDictGrow */

    return(ret);
}