#ifndef __CLIENT_H_
#define __CLIENT_H_ 

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <list.h>
#include <iter.h>


typedef struct {
	int id;
	char *fullname;
	char *dob;
	char *phone;
	int address_id;
	char *deleted_at;
	
} User;

struct client {
	int id;
	int fd;
	pid_t pid;
	char *hostname;
	char *username;
	char *ip;
	char *state;
	char *uptime;
	User *user;
	struct sockaddr_in addr;
	struct timeval last_active_at;
};

int clients_init(void);
void client_add(struct client *temp);
int client_remove(int id);
int client_is_dead(fd_set *rset, fd_set *allset);
struct client *client_get(int id);
int client_getall(struct client ***clients);
void client_dump(struct client *temp);
char *client_ipstr(struct client *temp);

void client_active_set(struct client *client);
struct client *client_active_get(void);
void client_active_unset(void);




#endif