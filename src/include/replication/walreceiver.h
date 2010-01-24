/*-------------------------------------------------------------------------
 *
 * walreceiver.h
 *	  Exports from replication/walreceiverfuncs.c.
 *
 * Portions Copyright (c) 2010-2010, PostgreSQL Global Development Group
 *
 * $PostgreSQL$
 *
 *-------------------------------------------------------------------------
 */
#ifndef _WALRECEIVER_H
#define _WALRECEIVER_H

#include "access/xlogdefs.h"
#include "storage/spin.h"

/*
 * MAXCONNINFO: maximum size of a connection string.
 *
 * XXX: Should this move to pg_config_manual.h?
 */
#define MAXCONNINFO		1024

/*
 * Values for WalRcv->walRcvState.
 */
typedef enum
{
	WALRCV_NOT_STARTED,
	WALRCV_RUNNING,		/* walreceiver has been started */
	WALRCV_STOPPING,	/* requested to stop, but still running */
	WALRCV_STOPPED		/* stopped and mustn't start up again */
} WalRcvState;

/* Shared memory area for management of walreceiver process */
typedef struct
{
	/*
	 * connection string; is used for walreceiver to connect with
	 * the primary.
	 */
	char	conninfo[MAXCONNINFO];

	/*
	 * PID of currently active walreceiver process, and the current state.
	 */
	pid_t	pid;
	WalRcvState walRcvState;

	/*
	 * receivedUpto-1 is the last byte position that has been already
	 * received. When startup process starts the walreceiver, it sets this
	 * to the point where it wants the streaming to begin. After that,
	 * walreceiver updates this whenever it flushes the received WAL.
	 */
	XLogRecPtr	receivedUpto;

	slock_t	mutex;		/* locks shared variables shown above */
} WalRcvData;

extern WalRcvData *WalRcv;

/* libpqwalreceiver hooks */
typedef bool (*walrcv_connect_type) (char *conninfo, XLogRecPtr startpoint);
extern PGDLLIMPORT walrcv_connect_type walrcv_connect;

typedef bool (*walrcv_receive_type) (int timeout, XLogRecPtr *recptr, char **buffer, int *len);
extern PGDLLIMPORT walrcv_receive_type walrcv_receive;

typedef void (*walrcv_disconnect_type) (void);
extern PGDLLIMPORT walrcv_disconnect_type walrcv_disconnect;

extern void WalReceiverMain(void);
extern Size WalRcvShmemSize(void);
extern void WalRcvShmemInit(void);
extern bool WalRcvInProgress(void);
extern XLogRecPtr WaitNextXLogAvailable(XLogRecPtr recptr, bool *finished);
extern void RequestXLogStreaming(XLogRecPtr recptr, const char *conninfo);
extern XLogRecPtr GetWalRcvWriteRecPtr(void);

#endif   /* _WALRECEIVER_H */
