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
typedef  TYPE_1__* xmlURIPtr ;
typedef  scalar_t__ xmlChar ;
struct TYPE_6__ {char* scheme; char* fragment; char* path; char* authority; char* server; int port; char* user; char* query_raw; char* query; } ;

/* Variables and functions */
 scalar_t__ strlen (char*) ; 
 TYPE_1__* xmlCreateURI () ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 int /*<<< orphan*/  xmlFreeURI (TYPE_1__*) ; 
 scalar_t__ xmlMallocAtomic (int) ; 
 void* xmlMemStrdup (char*) ; 
 int /*<<< orphan*/  xmlNormalizeURIPath (char*) ; 
 int xmlParseURIReference (TYPE_1__*,char const*) ; 
 scalar_t__* xmlSaveUri (TYPE_1__*) ; 
 scalar_t__* xmlStrdup (scalar_t__ const*) ; 
 int /*<<< orphan*/  xmlURIErrMemory (char*) ; 

xmlChar *
xmlBuildURI(const xmlChar *URI, const xmlChar *base) {
    xmlChar *val = NULL;
    int ret, len, indx, cur, out;
    xmlURIPtr ref = NULL;
    xmlURIPtr bas = NULL;
    xmlURIPtr res = NULL;

    /*
     * 1) The URI reference is parsed into the potential four components and
     *    fragment identifier, as described in Section 4.3.
     *
     *    NOTE that a completely empty URI is treated by modern browsers
     *    as a reference to "." rather than as a synonym for the current
     *    URI.  Should we do that here?
     */
    if (URI == NULL)
	ret = -1;
    else {
	if (*URI) {
	    ref = xmlCreateURI();
	    if (ref == NULL)
		goto done;
	    ret = xmlParseURIReference(ref, (const char *) URI);
	}
	else
	    ret = 0;
    }
    if (ret != 0)
	goto done;
    if ((ref != NULL) && (ref->scheme != NULL)) {
	/*
	 * The URI is absolute don't modify.
	 */
	val = xmlStrdup(URI);
	goto done;
    }
    if (base == NULL)
	ret = -1;
    else {
	bas = xmlCreateURI();
	if (bas == NULL)
	    goto done;
	ret = xmlParseURIReference(bas, (const char *) base);
    }
    if (ret != 0) {
	if (ref)
	    val = xmlSaveUri(ref);
	goto done;
    }
    if (ref == NULL) {
	/*
	 * the base fragment must be ignored
	 */
	if (bas->fragment != NULL) {
	    xmlFree(bas->fragment);
	    bas->fragment = NULL;
	}
	val = xmlSaveUri(bas);
	goto done;
    }

    /*
     * 2) If the path component is empty and the scheme, authority, and
     *    query components are undefined, then it is a reference to the
     *    current document and we are done.  Otherwise, the reference URI's
     *    query and fragment components are defined as found (or not found)
     *    within the URI reference and not inherited from the base URI.
     *
     *    NOTE that in modern browsers, the parsing differs from the above
     *    in the following aspect:  the query component is allowed to be
     *    defined while still treating this as a reference to the current
     *    document.
     */
    res = xmlCreateURI();
    if (res == NULL)
	goto done;
    if ((ref->scheme == NULL) && (ref->path == NULL) &&
	((ref->authority == NULL) && (ref->server == NULL))) {
	if (bas->scheme != NULL)
	    res->scheme = xmlMemStrdup(bas->scheme);
	if (bas->authority != NULL)
	    res->authority = xmlMemStrdup(bas->authority);
	else if ((bas->server != NULL) || (bas->port == -1)) {
	    if (bas->server != NULL)
		res->server = xmlMemStrdup(bas->server);
	    if (bas->user != NULL)
		res->user = xmlMemStrdup(bas->user);
	    res->port = bas->port;
	}
	if (bas->path != NULL)
	    res->path = xmlMemStrdup(bas->path);
	if (ref->query_raw != NULL)
	    res->query_raw = xmlMemStrdup (ref->query_raw);
	else if (ref->query != NULL)
	    res->query = xmlMemStrdup(ref->query);
	else if (bas->query_raw != NULL)
	    res->query_raw = xmlMemStrdup(bas->query_raw);
	else if (bas->query != NULL)
	    res->query = xmlMemStrdup(bas->query);
	if (ref->fragment != NULL)
	    res->fragment = xmlMemStrdup(ref->fragment);
	goto step_7;
    }

    /*
     * 3) If the scheme component is defined, indicating that the reference
     *    starts with a scheme name, then the reference is interpreted as an
     *    absolute URI and we are done.  Otherwise, the reference URI's
     *    scheme is inherited from the base URI's scheme component.
     */
    if (ref->scheme != NULL) {
	val = xmlSaveUri(ref);
	goto done;
    }
    if (bas->scheme != NULL)
	res->scheme = xmlMemStrdup(bas->scheme);

    if (ref->query_raw != NULL)
	res->query_raw = xmlMemStrdup(ref->query_raw);
    else if (ref->query != NULL)
	res->query = xmlMemStrdup(ref->query);
    if (ref->fragment != NULL)
	res->fragment = xmlMemStrdup(ref->fragment);

    /*
     * 4) If the authority component is defined, then the reference is a
     *    network-path and we skip to step 7.  Otherwise, the reference
     *    URI's authority is inherited from the base URI's authority
     *    component, which will also be undefined if the URI scheme does not
     *    use an authority component.
     */
    if ((ref->authority != NULL) || (ref->server != NULL)) {
	if (ref->authority != NULL)
	    res->authority = xmlMemStrdup(ref->authority);
	else {
	    res->server = xmlMemStrdup(ref->server);
	    if (ref->user != NULL)
		res->user = xmlMemStrdup(ref->user);
            res->port = ref->port;
	}
	if (ref->path != NULL)
	    res->path = xmlMemStrdup(ref->path);
	goto step_7;
    }
    if (bas->authority != NULL)
	res->authority = xmlMemStrdup(bas->authority);
    else if ((bas->server != NULL) || (bas->port == -1)) {
	if (bas->server != NULL)
	    res->server = xmlMemStrdup(bas->server);
	if (bas->user != NULL)
	    res->user = xmlMemStrdup(bas->user);
	res->port = bas->port;
    }

    /*
     * 5) If the path component begins with a slash character ("/"), then
     *    the reference is an absolute-path and we skip to step 7.
     */
    if ((ref->path != NULL) && (ref->path[0] == '/')) {
	res->path = xmlMemStrdup(ref->path);
	goto step_7;
    }


    /*
     * 6) If this step is reached, then we are resolving a relative-path
     *    reference.  The relative path needs to be merged with the base
     *    URI's path.  Although there are many ways to do this, we will
     *    describe a simple method using a separate string buffer.
     *
     * Allocate a buffer large enough for the result string.
     */
    len = 2; /* extra / and 0 */
    if (ref->path != NULL)
	len += strlen(ref->path);
    if (bas->path != NULL)
	len += strlen(bas->path);
    res->path = (char *) xmlMallocAtomic(len);
    if (res->path == NULL) {
        xmlURIErrMemory("resolving URI against base\n");
	goto done;
    }
    res->path[0] = 0;

    /*
     * a) All but the last segment of the base URI's path component is
     *    copied to the buffer.  In other words, any characters after the
     *    last (right-most) slash character, if any, are excluded.
     */
    cur = 0;
    out = 0;
    if (bas->path != NULL) {
	while (bas->path[cur] != 0) {
	    while ((bas->path[cur] != 0) && (bas->path[cur] != '/'))
		cur++;
	    if (bas->path[cur] == 0)
		break;

	    cur++;
	    while (out < cur) {
		res->path[out] = bas->path[out];
		out++;
	    }
	}
    }
    res->path[out] = 0;

    /*
     * b) The reference's path component is appended to the buffer
     *    string.
     */
    if (ref->path != NULL && ref->path[0] != 0) {
	indx = 0;
	/*
	 * Ensure the path includes a '/'
	 */
	if ((out == 0) && (bas->server != NULL))
	    res->path[out++] = '/';
	while (ref->path[indx] != 0) {
	    res->path[out++] = ref->path[indx++];
	}
    }
    res->path[out] = 0;

    /*
     * Steps c) to h) are really path normalization steps
     */
    xmlNormalizeURIPath(res->path);

step_7:

    /*
     * 7) The resulting URI components, including any inherited from the
     *    base URI, are recombined to give the absolute form of the URI
     *    reference.
     */
    val = xmlSaveUri(res);

done:
    if (ref != NULL)
	xmlFreeURI(ref);
    if (bas != NULL)
	xmlFreeURI(bas);
    if (res != NULL)
	xmlFreeURI(res);
    return(val);
}