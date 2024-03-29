#include <client.h>

static List *clients = NULL;
static struct client *active_client;

int client_id_callback(void *data, void *needle);

int clients_init(void)
{
	clients = list_new(sizeof(struct client), NULL);

	if (clients == NULL) {
		perror("");		
		return -1;
	}

	return 0;
}

int is_client_timerset(void)
{
	Iter *iter = list_getiter(clients);
	struct client *temp;

	while((temp = iter_next(iter))) {
		if (temp->timer) {
			return 1;
		}
	}

	return 0;
}

int client_getall(struct client ***client_array)
{
	int i = 0;
	struct client **array;

	array = malloc(sizeof(struct client *) * clients->size);

	Iter *iter = list_getiter(clients);
	struct client *temp;

	while((temp = iter_next(iter))) {
		array[i++] = temp;
	}

	*client_array = array;

	if (array == NULL || client_array == NULL)
		return 0;

	return i;
}

void client_add(struct client *temp)
{
	list_push(clients, temp);
}

int client_remove(int id)
{
	struct client temp = {.id = id};

	return list_remove(clients, &temp, client_id_callback);
}

struct client *client_get(int id)
{
	struct client temp = {.id = id};

	return list_search(clients, &temp, client_id_callback);
}

int client_id_callback(void *data, void *needle)
{
	return !(((struct client *)needle)->id == ((struct client *)data)->id);
}

int client_is_dead(fd_set *rset, fd_set *allset)
{
	int nbytes;
	char buf[1024];

	Iter *iter = list_getiter(clients);
	struct client *temp;

	while((temp = iter_next(iter))) {
		if (FD_ISSET(temp->fd, rset)) {

			if ((nbytes = read(temp->fd, buf, sizeof(buf))) == 0) {
				fprintf(stderr, "Client %d Terminated\n", temp->id);
				close(temp->fd);
				FD_CLR(temp->fd, allset);
				client_remove(temp->id);
				return 0;
			}
		}
	}

	return -1;
}

void client_dump(struct client *temp)
{
	printf("Id        : %d\n", temp->id);
	printf("Hostname  : %s\n", temp->hostname);
	printf("Username  : %s\n", temp->username);
	printf("Uptime    : %s\n", temp->uptime);
	printf("State     : %s\n", (temp->is_online) ? "online" : "offline");
	printf("IP        : %s\n", temp->ip);
	printf("Pid       : %d\n\n", temp->pid);
}


char *client_ipstr(struct client *temp)
{
	char *buf = malloc(sizeof(char) * BUFSIZ);
	struct sockaddr_in *sockaddr = &(temp->addr);

	if (inet_ntop(sockaddr->sin_family, &sockaddr->sin_addr, buf, BUFSIZ) == NULL) {
		free(buf);

		return NULL;
	}

	return buf;
}

void client_active_set(struct client *client)
{
	active_client = client;
}

struct client *client_active_get(void)
{
	return active_client;
}

void client_active_unset(void)
{
	active_client = NULL;
}
