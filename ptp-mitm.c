#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <errno.h>

const char DvsPath[] = "/Library/Application Support/Audinate/DanteVirtualSoundcard/ptp-original";

int main(int argc, char *argv[], char *envp[]) 
{ 
	char ** args;
	int i, argsc;
	
	printf("DVS PTP HACK\n");
	
	// alloc new argument list (last pointer must always be NULL)
	args = calloc( argc+1, sizeof(char*) );
	
	// set path of actual ptp service
	args[0] = (char*)DvsPath;
	
	for (i = 1, argsc = 1; i < argc; i++) {
		// unless it is the -s (slave-only) option pass through argument
		if (strcmp(argv[i], "-s") != 0){
			args[argsc] = argv[i];
			argsc++;	
		}
	}
	
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