#define USE_POSIX_TIME
#define NO_EMPTY_STMTS
#define SYSV_DIRENT

#ifndef			BYTE_ORDER
#ifdef			MIPSEB
#define			BYTE_ORDER		BIG_ENDIAN
#endif
#endif

#ifdef sinix
#define HAS_TEST_AND_SET

#include <abi_mutex.h>
typedef abilock_t slock_t;

#endif
