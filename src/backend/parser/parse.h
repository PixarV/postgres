typedef union
{
	double				dval;
	int					ival;
	char				chr;
	char				*str;
	bool				boolean;
	bool*				pboolean;	/* for pg_shadow privileges */
	List				*list;
	Node				*node;
	Value				*value;

	Attr				*attr;

	TypeName			*typnam;
	DefElem				*defelt;
	ParamString			*param;
	SortGroupBy			*sortgroupby;
	JoinExpr			*joinexpr;
	IndexElem			*ielem;
	RangeVar			*range;
	RelExpr				*relexp;
	A_Indices			*aind;
	ResTarget			*target;
	ParamNo				*paramno;

	VersionStmt			*vstmt;
	DefineStmt			*dstmt;
	RuleStmt			*rstmt;
	InsertStmt			*astmt;
} YYSTYPE;
#define	ABSOLUTE	258
#define	ACTION	259
#define	ADD	260
#define	ALL	261
#define	ALTER	262
#define	AND	263
#define	ANY	264
#define	AS	265
#define	ASC	266
#define	BEGIN_TRANS	267
#define	BETWEEN	268
#define	BOTH	269
#define	BY	270
#define	CASCADE	271
#define	CASE	272
#define	CAST	273
#define	CHAR	274
#define	CHARACTER	275
#define	CHECK	276
#define	CLOSE	277
#define	COALESCE	278
#define	COLLATE	279
#define	COLUMN	280
#define	COMMIT	281
#define	CONSTRAINT	282
#define	CREATE	283
#define	CROSS	284
#define	CURRENT	285
#define	CURRENT_DATE	286
#define	CURRENT_TIME	287
#define	CURRENT_TIMESTAMP	288
#define	CURRENT_USER	289
#define	CURSOR	290
#define	DAY_P	291
#define	DECIMAL	292
#define	DECLARE	293
#define	DEFAULT	294
#define	DELETE	295
#define	DESC	296
#define	DISTINCT	297
#define	DOUBLE	298
#define	DROP	299
#define	ELSE	300
#define	END_TRANS	301
#define	EXCEPT	302
#define	EXECUTE	303
#define	EXISTS	304
#define	EXTRACT	305
#define	FALSE_P	306
#define	FETCH	307
#define	FLOAT	308
#define	FOR	309
#define	FOREIGN	310
#define	FROM	311
#define	FULL	312
#define	GRANT	313
#define	GROUP	314
#define	HAVING	315
#define	HOUR_P	316
#define	IN	317
#define	INNER_P	318
#define	INSENSITIVE	319
#define	INSERT	320
#define	INTERSECT	321
#define	INTERVAL	322
#define	INTO	323
#define	IS	324
#define	ISOLATION	325
#define	JOIN	326
#define	KEY	327
#define	LANGUAGE	328
#define	LEADING	329
#define	LEFT	330
#define	LEVEL	331
#define	LIKE	332
#define	LOCAL	333
#define	MATCH	334
#define	MINUTE_P	335
#define	MONTH_P	336
#define	NAMES	337
#define	NATIONAL	338
#define	NATURAL	339
#define	NCHAR	340
#define	NEXT	341
#define	NO	342
#define	NOT	343
#define	NULLIF	344
#define	NULL_P	345
#define	NUMERIC	346
#define	OF	347
#define	ON	348
#define	ONLY	349
#define	OPTION	350
#define	OR	351
#define	ORDER	352
#define	OUTER_P	353
#define	PARTIAL	354
#define	POSITION	355
#define	PRECISION	356
#define	PRIMARY	357
#define	PRIOR	358
#define	PRIVILEGES	359
#define	PROCEDURE	360
#define	PUBLIC	361
#define	READ	362
#define	REFERENCES	363
#define	RELATIVE	364
#define	REVOKE	365
#define	RIGHT	366
#define	ROLLBACK	367
#define	SCROLL	368
#define	SECOND_P	369
#define	SELECT	370
#define	SET	371
#define	SUBSTRING	372
#define	TABLE	373
#define	TEMP	374
#define	THEN	375
#define	TIME	376
#define	TIMESTAMP	377
#define	TIMEZONE_HOUR	378
#define	TIMEZONE_MINUTE	379
#define	TO	380
#define	TRAILING	381
#define	TRANSACTION	382
#define	TRIM	383
#define	TRUE_P	384
#define	UNION	385
#define	UNIQUE	386
#define	UPDATE	387
#define	USER	388
#define	USING	389
#define	VALUES	390
#define	VARCHAR	391
#define	VARYING	392
#define	VIEW	393
#define	WHEN	394
#define	WHERE	395
#define	WITH	396
#define	WORK	397
#define	YEAR_P	398
#define	ZONE	399
#define	TRIGGER	400
#define	TYPE_P	401
#define	ABORT_TRANS	402
#define	AFTER	403
#define	AGGREGATE	404
#define	ANALYZE	405
#define	BACKWARD	406
#define	BEFORE	407
#define	BINARY	408
#define	CACHE	409
#define	CLUSTER	410
#define	COPY	411
#define	CREATEDB	412
#define	CREATEUSER	413
#define	CYCLE	414
#define	DATABASE	415
#define	DELIMITERS	416
#define	DO	417
#define	EACH	418
#define	ENCODING	419
#define	EXPLAIN	420
#define	EXTEND	421
#define	FORWARD	422
#define	FUNCTION	423
#define	HANDLER	424
#define	INCREMENT	425
#define	INDEX	426
#define	INHERITS	427
#define	INSTEAD	428
#define	ISNULL	429
#define	LANCOMPILER	430
#define	LIMIT	431
#define	LISTEN	432
#define	LOAD	433
#define	LOCATION	434
#define	LOCK_P	435
#define	MAXVALUE	436
#define	MINVALUE	437
#define	MOVE	438
#define	NEW	439
#define	NOCREATEDB	440
#define	NOCREATEUSER	441
#define	NONE	442
#define	NOTHING	443
#define	NOTIFY	444
#define	NOTNULL	445
#define	OFFSET	446
#define	OIDS	447
#define	OPERATOR	448
#define	PASSWORD	449
#define	PROCEDURAL	450
#define	RENAME	451
#define	RESET	452
#define	RETURNS	453
#define	ROW	454
#define	RULE	455
#define	SEQUENCE	456
#define	SERIAL	457
#define	SETOF	458
#define	SHOW	459
#define	START	460
#define	STATEMENT	461
#define	STDIN	462
#define	STDOUT	463
#define	TRUSTED	464
#define	UNLISTEN	465
#define	UNTIL	466
#define	VACUUM	467
#define	VALID	468
#define	VERBOSE	469
#define	VERSION	470
#define	IDENT	471
#define	SCONST	472
#define	Op	473
#define	ICONST	474
#define	PARAM	475
#define	FCONST	476
#define	OP	477
#define	UMINUS	478
#define	TYPECAST	479


extern YYSTYPE yylval;
