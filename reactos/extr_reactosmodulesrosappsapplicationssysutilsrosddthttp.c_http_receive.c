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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  HINTERNET ;

/* Variables and functions */
 int HTTP_QUERY_CONTENT_LENGTH ; 
 int HTTP_QUERY_FLAG_NUMBER ; 
 scalar_t__ HttpQueryInfo (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ InternetReadFile (int /*<<< orphan*/ ,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 char* realloc (char*,scalar_t__) ; 

__attribute__((used)) static char *http_receive(HINTERNET h_req, u_long *d_size)
{
	u_long bytes  = sizeof(u_long);
	u_long qsize  = 0;
	u_long readed = 0;
	char  *data   = NULL;
	char   buff[4096];

	if (HttpQueryInfo(h_req, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &qsize, &bytes, NULL) != 0) {
		data = malloc(qsize + 1);
	}

	do
	{
		if (InternetReadFile(h_req, buff, sizeof(buff), &bytes) == 0) {
			break;
		}
		if ( (readed + bytes) > qsize) {
			data = realloc(data, readed + bytes + 1);
			if (data == NULL) break;
			qsize += bytes;
		}
		memcpy(data + readed, buff, bytes); readed += bytes;
	} while (bytes != 0);

	if ( (data != NULL) && (readed != qsize) ) {
		free(data); data = NULL;
	} else {
		if (d_size != NULL) *d_size = readed;
		data[readed] = 0;
	}	
	return data;
}