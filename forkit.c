#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
	pid_t child;
	int status;
	printf("Hello World!\n");
	if ((child = fork())) {
		/* parent */
		if (-1 == child) {
			perror("fork");
			exit(3);
		}
		printf("This is the parent, pid %d.\n", getpid());
		if (-1 == wait(&status)) {
			perror("wait");
			exit(3);
		}
		if (!WIFEXITED(status) || WEXITSTATUS(status)) {
			exit(EXIT_FAILURE);
		}
		else {
			exit(0);
		}
	}
	else {
		/* child */
		printf("This is the child, pid %d.\n", getpid());
		exit(0);
	}
	return 1; /* unreachable */
}
