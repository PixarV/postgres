#include "btree_gist.h"
#include "btree_utils_var.h"
#include "utils/builtins.h"

/*
** Text ops
*/
PG_FUNCTION_INFO_V1(gbt_text_compress);
PG_FUNCTION_INFO_V1(gbt_bpchar_compress);
PG_FUNCTION_INFO_V1(gbt_text_union);
PG_FUNCTION_INFO_V1(gbt_text_picksplit);
PG_FUNCTION_INFO_V1(gbt_text_consistent);
PG_FUNCTION_INFO_V1(gbt_bpchar_consistent);
PG_FUNCTION_INFO_V1(gbt_text_penalty);
PG_FUNCTION_INFO_V1(gbt_text_same);

Datum		gbt_text_compress(PG_FUNCTION_ARGS);
Datum		gbt_bpchar_compress(PG_FUNCTION_ARGS);
Datum		gbt_text_union(PG_FUNCTION_ARGS);
Datum		gbt_text_picksplit(PG_FUNCTION_ARGS);
Datum		gbt_text_consistent(PG_FUNCTION_ARGS);
Datum		gbt_bpchar_consistent(PG_FUNCTION_ARGS);
Datum		gbt_text_penalty(PG_FUNCTION_ARGS);
Datum		gbt_text_same(PG_FUNCTION_ARGS);


/* define for comparison */

static bool
gbt_textgt(const void *a, const void *b)
{
	return (DatumGetBool(DirectFunctionCall2(text_gt, PointerGetDatum(a), PointerGetDatum(b))));
}

static bool
gbt_textge(const void *a, const void *b)
{
	return (DatumGetBool(DirectFunctionCall2(text_ge, PointerGetDatum(a), PointerGetDatum(b))));
}

static bool
gbt_texteq(const void *a, const void *b)
{
	return (DatumGetBool(DirectFunctionCall2(texteq, PointerGetDatum(a), PointerGetDatum(b))));
}

static bool
gbt_textle(const void *a, const void *b)
{
	return (DatumGetBool(DirectFunctionCall2(text_le, PointerGetDatum(a), PointerGetDatum(b))));
}

static bool
gbt_textlt(const void *a, const void *b)
{
	return (DatumGetBool(DirectFunctionCall2(text_lt, PointerGetDatum(a), PointerGetDatum(b))));
}

static int32
gbt_textcmp(const bytea *a, const bytea *b)
{
	return strcmp(VARDATA(a), VARDATA(b));
}


/*
 * Converts data of leaf using strxfrm ( locale support )
*/

static bytea *
gbt_text_xfrm(bytea *leaf)
{
	bytea	   *out = leaf;
	int32		ilen = VARSIZE(leaf) - VARHDRSZ;
	int32		olen;
	char	   *sin;
	char	   *sou;

	sin = palloc(ilen + 1);
	memcpy(sin, (void *) VARDATA(leaf), ilen);
	sin[ilen] = '\0';

	olen = strxfrm(NULL, &sin[0], 0) + 1;
	sou = palloc(olen);
	olen = strxfrm(sou, &sin[0], olen);
	olen += VARHDRSZ;
	out = palloc(olen + 1);
	out->vl_len = olen + 1;
	memcpy((void *) VARDATA(out), sou, olen - VARHDRSZ);
	((char *) out)[olen] = '\0';

	pfree(sou);
	pfree(sin);

	return out;
}


static GBT_VARKEY *
gbt_text_l2n(GBT_VARKEY * leaf)
{

	GBT_VARKEY *out = leaf;
	GBT_VARKEY_R r = gbt_var_key_readable(leaf);
	bytea	   *o;

	o = gbt_text_xfrm(r.lower);
	r.lower = r.upper = o;
	out = gbt_var_key_copy(&r, TRUE);
	pfree(o);

	return out;

}





static const gbtree_vinfo tinfo =
{
	gbt_t_text,
	TRUE,
	TRUE,
	gbt_textgt,
	gbt_textge,
	gbt_texteq,
	gbt_textle,
	gbt_textlt,
	gbt_textcmp,
	gbt_text_l2n
};



/**************************************************
 * Text ops
 **************************************************/


Datum
gbt_text_compress(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);

	PG_RETURN_POINTER(gbt_var_compress(entry, &tinfo));
}

Datum
gbt_bpchar_compress(PG_FUNCTION_ARGS)
{

	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *retval;

	if (entry->leafkey)
	{

		Datum		d = DirectFunctionCall1(rtrim1, entry->key);
		GISTENTRY  *trim = palloc(sizeof(GISTENTRY));

		gistentryinit(*trim, d,
					  entry->rel, entry->page,
					  entry->offset, VARSIZE(DatumGetPointer(d)), TRUE);
		retval = gbt_var_compress(trim, &tinfo);

		pfree(trim);
		pfree(DatumGetPointer(d));
	}
	else
		retval = entry;

	PG_RETURN_POINTER(retval);
}



Datum
gbt_text_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GBT_VARKEY *ktst = (GBT_VARKEY *) DatumGetPointer(entry->key);
	GBT_VARKEY *key = (GBT_VARKEY *) DatumGetPointer(PG_DETOAST_DATUM(entry->key));
	void	   *qtst = (void *) DatumGetPointer(PG_GETARG_DATUM(1));
	void	   *query = (void *) DatumGetTextP(PG_GETARG_DATUM(1));
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		retval = FALSE;
	GBT_VARKEY_R r = gbt_var_key_readable(key);

	if (GIST_LEAF(entry))
		retval = gbt_var_consistent(&r, query, &strategy, TRUE, &tinfo);
	else
	{
		bytea	   *q = gbt_text_xfrm((bytea *) query);

		retval = gbt_var_consistent(&r, (void *) q, &strategy, FALSE, &tinfo);
		if (q != query)
			pfree(q);
	}

	if (ktst != key)
		pfree(key);
	if (qtst != query)
		pfree(query);

	PG_RETURN_BOOL(retval);
}


Datum
gbt_bpchar_consistent(PG_FUNCTION_ARGS)
{
	GISTENTRY  *entry = (GISTENTRY *) PG_GETARG_POINTER(0);
	GBT_VARKEY *ktst = (GBT_VARKEY *) DatumGetPointer(entry->key);
	GBT_VARKEY *key = (GBT_VARKEY *) DatumGetPointer(PG_DETOAST_DATUM(entry->key));
	void	   *qtst = (void *) DatumGetPointer(PG_GETARG_DATUM(1));
	void	   *query = (void *) DatumGetPointer(PG_DETOAST_DATUM(PG_GETARG_DATUM(1)));
	void	   *trim = (void *) DatumGetPointer(DirectFunctionCall1(rtrim1, PointerGetDatum(query)));
	StrategyNumber strategy = (StrategyNumber) PG_GETARG_UINT16(2);
	bool		retval = FALSE;
	GBT_VARKEY_R r = gbt_var_key_readable(key);

	if (GIST_LEAF(entry))
		retval = gbt_var_consistent(&r, trim, &strategy, TRUE, &tinfo);
	else
	{
		bytea	   *q = gbt_text_xfrm((bytea *) trim);

		retval = gbt_var_consistent(&r, (void *) q, &strategy, FALSE, &tinfo);
		if (q != trim)
			pfree(q);
	}

	pfree(trim);

	if (ktst != key)
		pfree(key);
	if (qtst != query)
		pfree(query);
	PG_RETURN_BOOL(retval);
}




Datum
gbt_text_union(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	int32	   *size = (int *) PG_GETARG_POINTER(1);

	PG_RETURN_POINTER(gbt_var_union(entryvec, size, &tinfo));
}


Datum
gbt_text_picksplit(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	GIST_SPLITVEC *v = (GIST_SPLITVEC *) PG_GETARG_POINTER(1);

	gbt_var_picksplit(entryvec, v, &tinfo);
	PG_RETURN_POINTER(v);
}

Datum
gbt_text_same(PG_FUNCTION_ARGS)
{
	Datum		d1 = PG_GETARG_DATUM(0);
	Datum		d2 = PG_GETARG_DATUM(1);
	bool	   *result = (bool *) PG_GETARG_POINTER(2);

	PG_RETURN_POINTER(gbt_var_same(result, d1, d2, &tinfo));
}


Datum
gbt_text_penalty(PG_FUNCTION_ARGS)
{
	float	   *result = (float *) PG_GETARG_POINTER(2);
	GISTENTRY  *o = (GISTENTRY *) PG_GETARG_POINTER(0);
	GISTENTRY  *n = (GISTENTRY *) PG_GETARG_POINTER(1);

	PG_RETURN_POINTER(gbt_var_penalty(result, o, n, &tinfo));
}
