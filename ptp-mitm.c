#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// #define DISABLE_SLAVE_ONLY
#define ENABLE_PTPV2

const char DvsPath[] = "/Library/Application Support/Audinate/DanteVirtualSoundcard/ptp-original";

int main(int argc, char *argv[], char *envp[])
{
	char ** args;
	int i, argsc;

	printf("DVS PTP HACK\n");

	argsc = argc+1;

#ifdef ENABLE_PTPV2
	// store m2 (ptpv2 interface) as used for ptpv1 (-m=)
	char m2[256] = "-m2=";
	argsc += 2;
#endif // ENABLE_PTPV2

	// alloc new argument list (last pointer must always be NULL)
	args = calloc( argsc, sizeof(char*) );

	// set path of actual ptp service
	args[0] = (char*)DvsPath;

	for (i = 1, argsc = 1; i < argc; i++) {

#ifdef DISABLE_SLAVE_ONLY
		// skip -s (slave-only) option
		if (strcmp(argv[i], "-s") == 0)
			continue;
#endif //DISABLE_SLAVE_ONLY

#ifdef ENABLE_PTPV2
	 if (strncmp(argv[i],"-m=",3) == 0){
		 strcpy(&m2[4], &argv[i][3]);
	 }
#endif //ENABLE_PTPV2

		args[argsc] = argv[i];
		argsc++;
	}

#ifdef ENABLE_PTPV2
	args[argsc++] = "-y2=-2";
	args[argsc++] = m2; // "-m2="
#endif // ENABLE_PTPV2

	// call actual ptp service
	execve(args[0], args, envp);

	// should never reach here -> error case

    printf("Error %d ", errno);
    switch(errno){
    	case EPERM: 	printf("Operation not permitted"); break;
    	case ENOENT: 	printf("No such file or directory"); break;
    	// etc
    }

	printf("\n");

	free( args );

	return 0;

}
