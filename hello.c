#define USE_TI89

#include <tigcclib.h>
#include "ti89-stub.c"

void _main(void);

short sr;
void _main(void)
{
	long int x;

	clrscr();
	set_debug_traps();
	printf_xy(0, 60, "_main = %lp\n", &_main);
//	for (x = 0 ; x++ ; x < 1000000) {}
//	breakpoint();
//	puts(".\n");

	while (1) {};
}

// Used to listen to the remote debugger
int getDebugChar(void)
{
	char c;
	int len;
	len = OSReadLinkBlock(&c, 1);

	if (len != 0)
		return c;
	else
		return 0;
}

/* Used by the GDB stub to set a vector handler */
void exceptionHandler(int vec_no, void *func)
{
	void *old, *new;
	long int x;

	old = GetIntVec((long) vec_no * 4);
	printf("Setting %x (%lp) ...\n", vec_no * 4, func);

//	if (vec_no * 4 > TRAP_15) {
//		printf(" - Ignoring, >#15\n");
//		return;
//	}

//	if ((vec_no * 4 > FIRST_AUTO_INT) && (vec_no * 4 < LAST_AUTO_INT)) {
//		printf(" - Ignoring AI\n");
//	}

	SetIntVec((long) vec_no * 4, (INT_HANDLER) func);
	new = GetIntVec((long) vec_no * 2);
	printf(" - %lp -> %lp\n", old, new);
//	for (x = 0; x < 100000; x++) {}
}
