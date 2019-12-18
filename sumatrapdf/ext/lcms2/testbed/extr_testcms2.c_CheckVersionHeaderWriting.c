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
typedef  int /*<<< orphan*/  test_versions ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,float,scalar_t__) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProfilePlaceholder (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float) ; 
 double fabs (scalar_t__) ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static
cmsInt32Number CheckVersionHeaderWriting(void)
{
    cmsHPROFILE h;
    int index;
    float test_versions[] = {
      2.3f,
      4.08f,
      4.09f,
      4.3f
    };

    for (index = 0; index < sizeof(test_versions)/sizeof(test_versions[0]); index++) {

      h = cmsCreateProfilePlaceholder(DbgThread());
      if (h == NULL) return 0;

      cmsSetProfileVersion(DbgThread(), h, test_versions[index]);

      cmsSaveProfileToFile(DbgThread(), h, "versions.icc");
      cmsCloseProfile(DbgThread(), h);

      h = cmsOpenProfileFromFile(DbgThread(), "versions.icc", "r");

      // Only the first 3 digits are significant
      if (fabs(cmsGetProfileVersion(DbgThread(), h) - test_versions[index]) > 0.005) {
        Fail("Version failed to round-trip: wrote %.2f, read %.2f",
             test_versions[index], cmsGetProfileVersion(DbgThread(), h));
        return 0;
      }

      cmsCloseProfile(DbgThread(), h);
      remove("versions.icc");
    }
    return 1;
}