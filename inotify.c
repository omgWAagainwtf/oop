 uint32_t mask; #include <sys/inotify.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int main(int argc, char **argv) {
	int fd;
	int num;
	char* p;
	struct inotify_event* event;
	char buf[BUF_LEN];
	int ret;
	
	fd = inotify_init();
	if (fd < 0) {
		perror("error");
		exit (-1);
	}
	ret=inotify_add_watch(fd, argv[1], IN_ALL_EVENTS);
	if (ret < 0) {
		perror("error");
		exit (-1);
	}
	while(1) {
		num = read(fd, buf, BUF_LEN);
		if (num < 0) {
			perror("Error");
			exit(-1);
		}
		for (p = buf; p < buf + num; ) {
			event = (struct inotify_event *) p;
			printf("mask = %d\n", event->mask);
			if (event->mask & IN_ACCESS) 	puts("in access");
			if (event->mask & IN_CREATE)	puts("IN_CREATE ");
			if (event->mask & IN_DELETE)	puts("IN_DELETE ");
			p+=sizeof(struct inotify_event) + event->len;
		}
	}
}
