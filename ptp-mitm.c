#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#ifdef WIN32
#include <process.h>
#endif


// #define DISABLE_SLAVE_ONLY 		// Allow DVS to become leader
// #define ENABLE_PTPV2 			// Enable PTPv2 support

#ifdef WIN32
const char DvsPath[] = "C:\\Program Files\\Audinate\\Dante Virtual Soundcard\\ptp-original.exe";
const char DvsPathArg[] = "\"C:\\Program Files\\Audinate\\Dante Virtual Soundcard\\ptp-original.exe\"";
#else
const char DvsPath[] = "/Library/Application Support/Audinate/DanteVirtualSoundcard/ptp-original";
#define DvsPathArg DvsPath
#endif 

int main(int argc, char *argv[], char *envp[])
{
	char ** args;
	int i, argsc;

	printf("<3 DVS PTP HACK <3\n");

	argsc = argc+1;

#ifdef ENABLE_PTPV2
	// store m2 (ptpv2 interface) as used for ptpv1 (-m1=)
	char m2[256] = "-m2=";
	argsc += 2;
#endif // ENABLE_PTPV2

	// alloc new argument list (last pointer must always be NULL)
	args = calloc( argsc, sizeof(char*) );

	// set path of actual ptp service
	args[0] = (char*)DvsPathArg;

	for (i = 1, argsc = 1; i < argc; i++) {
#ifdef DISABLE_SLAVE_ONLY
		// skip -s (slave-only) option
		if (strcmp(argv[i], "-s") == 0)
			continue;
#endif //DISABLE_SLAVE_ONLY

#ifdef ENABLE_PTPV2
	 if (strncmp(argv[i],"-m1=",4) == 0){
		 strcpy(&m2[4], &argv[i][4]);
	 }
#endif //ENABLE_PTPV2

#ifdef WIN32
	// the log-file and conf-file paths will be padded with "
	// such that it will be considered one arguments
	// (preventing spaces to mark argument delimiters)
	if ((strncmp(argv[i],"-lf=",4) == 0) ||
	    (strncmp(argv[i],"-c=",3) == 0)){
		int l = strlen(argv[i]);
		args[argsc] = calloc(l+3, sizeof(char));
		args[argsc][0] = '"'; 			// prepend "
		memcpy(&args[argsc][1],argv[i],l);	// original argument
		args[argsc][l+1] = '"';			// append "
		args[argsc][l+2] = '\0';		// string termination
		argsc++;
		continue;
	}
#endif //WIN32

		args[argsc] = argv[i];
		argsc++;
	}

#ifdef ENABLE_PTPV2
	args[argsc++] = "-y2=-2";
	args[argsc++] = m2; // "-m2="
#endif // ENABLE_PTPV2

	// call actual ptp service
#ifdef WIN32
	spawnv(_P_WAIT, DvsPath, args);
#else	
	execve(args[0], args, envp);
#endif

	// should never reach here -> error case

    printf("Error %d ", errno);
    switch(errno){
    	case EPERM: 	printf("Operation not permitted"); break;
    	case ENOENT: 	printf("No such file or directory"); break;
	case EINVAL:	printf("Invalid argument. An invalid value was given for one of the arguments to a function."); break;
    	// etc
    }

	printf("\n");

	free( args );

	while (1){
		sleep(1000);
	}

	return 0;

}
