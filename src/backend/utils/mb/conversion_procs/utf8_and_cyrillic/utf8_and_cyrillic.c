/*-------------------------------------------------------------------------
 *
 *	  UTF8 and Cyrillic
 *
 * Portions Copyright (c) 1996-2005, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * IDENTIFICATION
 *	  $PostgreSQL$
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"
#include "fmgr.h"
#include "mb/pg_wchar.h"
#include "../../Unicode/utf8_to_koi8r.map"
#include "../../Unicode/koi8r_to_utf8.map"
#include "../../Unicode/utf8_to_win1251.map"
#include "../../Unicode/win1251_to_utf8.map"
#include "../../Unicode/utf8_to_win866.map"
#include "../../Unicode/win866_to_utf8.map"

PG_FUNCTION_INFO_V1(utf8_to_koi8r);
PG_FUNCTION_INFO_V1(koi8r_to_utf8);
PG_FUNCTION_INFO_V1(utf8_to_win1251);
PG_FUNCTION_INFO_V1(win1251_to_utf8);
PG_FUNCTION_INFO_V1(utf8_to_win866);
PG_FUNCTION_INFO_V1(win866_to_utf8);

extern Datum utf8_to_koi8r(PG_FUNCTION_ARGS);
extern Datum koi8r_to_utf8(PG_FUNCTION_ARGS);
extern Datum utf8_to_win1251(PG_FUNCTION_ARGS);
extern Datum win1251_to_utf8(PG_FUNCTION_ARGS);
extern Datum utf8_to_win866(PG_FUNCTION_ARGS);
extern Datum win866_to_utf8(PG_FUNCTION_ARGS);

/* ----------
 * conv_proc(
 *		INTEGER,	-- source encoding id
 *		INTEGER,	-- destination encoding id
 *		CSTRING,	-- source string (null terminated C string)
 *		CSTRING,	-- destination string (null terminated C string)
 *		INTEGER		-- source string length
 * ) returns VOID;
 * ----------
 */

Datum
utf8_to_koi8r(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_UTF8);
	Assert(PG_GETARG_INT32(1) == PG_KOI8R);
	Assert(len >= 0);

	UtfToLocal(src, dest, ULmap_KOI8R,
			   sizeof(ULmap_KOI8R) / sizeof(pg_utf_to_local), len);

	PG_RETURN_VOID();
}

Datum
koi8r_to_utf8(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_KOI8R);
	Assert(PG_GETARG_INT32(1) == PG_UTF8);
	Assert(len >= 0);

	LocalToUtf(src, dest, LUmapKOI8R,
			sizeof(LUmapKOI8R) / sizeof(pg_local_to_utf), PG_KOI8R, len);

	PG_RETURN_VOID();
}

Datum
utf8_to_win1251(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_UTF8);
	Assert(PG_GETARG_INT32(1) == PG_WIN1251);
	Assert(len >= 0);

	UtfToLocal(src, dest, ULmap_WIN1251,
			   sizeof(ULmap_WIN1251) / sizeof(pg_utf_to_local), len);

	PG_RETURN_VOID();
}

Datum
win1251_to_utf8(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_WIN1251);
	Assert(PG_GETARG_INT32(1) == PG_UTF8);
	Assert(len >= 0);

	LocalToUtf(src, dest, LUmapWIN1251,
		sizeof(LUmapWIN1251) / sizeof(pg_local_to_utf), PG_WIN1251, len);

	PG_RETURN_VOID();
}

Datum
utf8_to_win866(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_UTF8);
	Assert(PG_GETARG_INT32(1) == PG_WIN866);
	Assert(len >= 0);

	UtfToLocal(src, dest, ULmap_WIN866,
			   sizeof(ULmap_WIN866) / sizeof(pg_utf_to_local), len);

	PG_RETURN_VOID();
}

Datum
win866_to_utf8(PG_FUNCTION_ARGS)
{
	unsigned char *src = PG_GETARG_CSTRING(2);
	unsigned char *dest = PG_GETARG_CSTRING(3);
	int			len = PG_GETARG_INT32(4);

	Assert(PG_GETARG_INT32(0) == PG_WIN866);
	Assert(PG_GETARG_INT32(1) == PG_UTF8);
	Assert(len >= 0);

	LocalToUtf(src, dest, LUmapWIN866,
			   sizeof(LUmapWIN866) / sizeof(pg_local_to_utf), PG_WIN866, len);

	PG_RETURN_VOID();
}
