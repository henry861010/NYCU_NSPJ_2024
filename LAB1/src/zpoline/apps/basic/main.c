#include <stdio.h>
#include <string.h>

typedef long (*syscall_fn_t)(long, long, long, long, long, long, long);

static syscall_fn_t next_sys_call = NULL;

static long hook_function(long a1, long a2, long a3, long a4, long a5, long a6, long a7){
	
/*
	//see what the system call eas called
	printf("output from hook_function: syscall number %ld\n", a1);
*/
	
	if(a1 == 59){
		char **command = (char **)a3;

	/*
		// see what the command line was called by ./mystery
		for(int i=0;command[i]!=NULL;i++){
			printf("%s ",command[i]);
		}
		printf("\n");
	*/

		
		if(strcmp("toilet", command[0]) == 0){
			char *newcommand[] = {
				command[0],
				command[1],
				command[2],
				command[3],
				command[4],
				command[5],
				"--gay",
				NULL 
			};
			return next_sys_call(a1, a2, (long)newcommand, a4, a5, a6, a7);
		}
		
	}

	return next_sys_call(a1, a2, a3, a4, a5, a6, a7);
}

int __hook_init(long placeholder __attribute__((unused)),
		void *sys_call_hook_ptr)
{

	next_sys_call = *((syscall_fn_t *) sys_call_hook_ptr);
	*((syscall_fn_t *) sys_call_hook_ptr) = hook_function;

	return 0;
}
