#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlParserInputPtr ;
typedef  TYPE_2__* xmlParserCtxtPtr ;
typedef  char xmlChar ;
typedef  int /*<<< orphan*/  (* warningSAXFunc ) (TYPE_2__*,char*,char const*) ;
typedef  int /*<<< orphan*/ * errorSAXFunc ;
struct TYPE_7__ {TYPE_1__* sax; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* warning ) (TYPE_2__*,char*,char const*) ;int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int /*<<< orphan*/ * defaultEntityLoader (char const*,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 scalar_t__ load_trace ; 
 int nbpaths ; 
 scalar_t__* paths ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xmlFree (char*) ; 
 char* xmlStrcat (char*,char const*) ; 
 char* xmlStrdup (char const*) ; 

__attribute__((used)) static xmlParserInputPtr
xmllintExternalEntityLoader(const char *URL, const char *ID,
			     xmlParserCtxtPtr ctxt) {
    xmlParserInputPtr ret;
    warningSAXFunc warning = NULL;
    errorSAXFunc err = NULL;

    int i;
    const char *lastsegment = URL;
    const char *iter = URL;

    if ((nbpaths > 0) && (iter != NULL)) {
	while (*iter != 0) {
	    if (*iter == '/')
		lastsegment = iter + 1;
	    iter++;
	}
    }

    if ((ctxt != NULL) && (ctxt->sax != NULL)) {
	warning = ctxt->sax->warning;
	err = ctxt->sax->error;
	ctxt->sax->warning = NULL;
	ctxt->sax->error = NULL;
    }

    if (defaultEntityLoader != NULL) {
	ret = defaultEntityLoader(URL, ID, ctxt);
	if (ret != NULL) {
	    if (warning != NULL)
		ctxt->sax->warning = warning;
	    if (err != NULL)
		ctxt->sax->error = err;
	    if (load_trace) {
		fprintf \
			(stderr,
			 "Loaded URL=\"%s\" ID=\"%s\"\n",
			 URL ? URL : "(null)",
			 ID ? ID : "(null)");
	    }
	    return(ret);
	}
    }
    for (i = 0;i < nbpaths;i++) {
	xmlChar *newURL;

	newURL = xmlStrdup((const xmlChar *) paths[i]);
	newURL = xmlStrcat(newURL, (const xmlChar *) "/");
	newURL = xmlStrcat(newURL, (const xmlChar *) lastsegment);
	if (newURL != NULL) {
	    ret = defaultEntityLoader((const char *)newURL, ID, ctxt);
	    if (ret != NULL) {
		if (warning != NULL)
		    ctxt->sax->warning = warning;
		if (err != NULL)
		    ctxt->sax->error = err;
		if (load_trace) {
		    fprintf \
			(stderr,
			 "Loaded URL=\"%s\" ID=\"%s\"\n",
			 newURL,
			 ID ? ID : "(null)");
		}
		xmlFree(newURL);
		return(ret);
	    }
	    xmlFree(newURL);
	}
    }
    if (err != NULL)
        ctxt->sax->error = err;
    if (warning != NULL) {
	ctxt->sax->warning = warning;
	if (URL != NULL)
	    warning(ctxt, "failed to load external entity \"%s\"\n", URL);
	else if (ID != NULL)
	    warning(ctxt, "failed to load external entity \"%s\"\n", ID);
    }
    return(NULL);
}