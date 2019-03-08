#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t child;
	int status;
	if (argc !=  2) {
		fprintf(stderr, "usage: tryit command\n");
	}
	if ((child = fork())) {
		/* parent */
		if (-1 == child) {
			perror("fork");
			exit(3);
		}
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
		execlp(argv[1], argv[1], NULL);
		perror(argv[1]);
		exit(3);
	}
	return 1; /* unreachable */
}
