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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AuthEvent ; 
 int /*<<< orphan*/  CF ; 
 int /*<<< orphan*/  CFM ; 
 int /*<<< orphan*/  Encrypt ; 
 int /*<<< orphan*/  EncryptMetadata ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  Length ; 
 int /*<<< orphan*/  O ; 
 int /*<<< orphan*/  OE ; 
 int /*<<< orphan*/  P ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Perms ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  StdCF ; 
 int /*<<< orphan*/  StmF ; 
 int /*<<< orphan*/  StrF ; 
 int /*<<< orphan*/  U ; 
 int /*<<< orphan*/  UE ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  pdf_crypt_encrypt_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_crypt_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* pdf_crypt_owner_encryption (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* pdf_crypt_owner_password (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_crypt_permissions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_crypt_permissions_encryption (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_crypt_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* pdf_crypt_user_encryption (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* pdf_crypt_user_password (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_crypt_version (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_put_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_dict_put_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_dict_put_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * pdf_trailer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
create_encryption_dictionary(fz_context *ctx, pdf_document *doc, pdf_crypt *crypt)
{
	unsigned char *o, *u;
	pdf_obj *encrypt;
	int r;

	r = pdf_crypt_revision(ctx, crypt);

	encrypt = pdf_dict_put_dict(ctx, pdf_trailer(ctx, doc), PDF_NAME(Encrypt), 10);

	pdf_dict_put_name(ctx, encrypt, PDF_NAME(Filter), "Standard");
	pdf_dict_put_int(ctx, encrypt, PDF_NAME(R), r);
	pdf_dict_put_int(ctx, encrypt, PDF_NAME(V), pdf_crypt_version(ctx, crypt));
	pdf_dict_put_int(ctx, encrypt, PDF_NAME(Length), pdf_crypt_length(ctx, crypt));
	pdf_dict_put_int(ctx, encrypt, PDF_NAME(P), pdf_crypt_permissions(ctx, crypt));
	pdf_dict_put_bool(ctx, encrypt, PDF_NAME(EncryptMetadata), pdf_crypt_encrypt_metadata(ctx, crypt));

	o = pdf_crypt_owner_password(ctx, crypt);
	u = pdf_crypt_user_password(ctx, crypt);

	if (r < 4)
	{
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(O), (char *) o, 32);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(U), (char *) u, 32);
	}
	else if (r == 4)
	{
		pdf_obj *cf;

		pdf_dict_put_name(ctx, encrypt, PDF_NAME(StmF), "StdCF");
		pdf_dict_put_name(ctx, encrypt, PDF_NAME(StrF), "StdCF");

		cf = pdf_dict_put_dict(ctx, encrypt, PDF_NAME(CF), 1);
		cf = pdf_dict_put_dict(ctx, cf, PDF_NAME(StdCF), 3);
		pdf_dict_put_name(ctx, cf, PDF_NAME(AuthEvent), "DocOpen");
		pdf_dict_put_name(ctx, cf, PDF_NAME(CFM), "AESV2");
		pdf_dict_put_int(ctx, cf, PDF_NAME(Length), 16);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(O), (char *) o, 32);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(U), (char *) u, 32);
	}
	else if (r == 6)
	{
		unsigned char *oe = pdf_crypt_owner_encryption(ctx, crypt);
		unsigned char *ue = pdf_crypt_user_encryption(ctx, crypt);
		pdf_obj *cf;

		pdf_dict_put_name(ctx, encrypt, PDF_NAME(StmF), "StdCF");
		pdf_dict_put_name(ctx, encrypt, PDF_NAME(StrF), "StdCF");

		cf = pdf_dict_put_dict(ctx, encrypt, PDF_NAME(CF), 1);
		cf = pdf_dict_put_dict(ctx, cf, PDF_NAME(StdCF), 3);
		pdf_dict_put_name(ctx, cf, PDF_NAME(AuthEvent), "DocOpen");
		pdf_dict_put_name(ctx, cf, PDF_NAME(CFM), "AESV3");
		pdf_dict_put_int(ctx, cf, PDF_NAME(Length), 32);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(O), (char *) o, 48);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(U), (char *) u, 48);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(OE), (char *) oe, 32);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(UE), (char *) ue, 32);
		pdf_dict_put_string(ctx, encrypt, PDF_NAME(Perms), (char *) pdf_crypt_permissions_encryption(ctx, crypt), 16);
	}
}