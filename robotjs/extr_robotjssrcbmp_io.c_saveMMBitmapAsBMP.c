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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  MMBitmapRef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * createBitmapData (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 

int saveMMBitmapAsBMP(MMBitmapRef bitmap, const char *path)
{
	FILE *fp;
	size_t dataLen;
	uint8_t *data;

	if ((fp = fopen(path, "wb")) == NULL) return -1;

	if ((data = createBitmapData(bitmap, &dataLen)) == NULL) {
		fclose(fp);
		return -1;
	}

	if (fwrite(data, dataLen, 1, fp) == 0) {
		free(data);
		fclose(fp);
		return -1;
	}

	free(data);
	fclose(fp);
	return 0;
}