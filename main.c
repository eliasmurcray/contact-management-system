#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct DiscordUser {
	char name[40];
	long id;
};

void add_user(struct DiscordUser** users, size_t* len, const char* name, const long id) {
	struct DiscordUser new_user;
	strcpy(new_user.name, name);
	new_user.id = id;
	*users = (struct DiscordUser*) realloc(*users, *len + 1);
	(*users)[*len] = new_user;
	*len += 1;
}

void remove_user(struct DiscordUser** users, size_t* len, long id) {
	bool swap = false;
	for (size_t i = 0; i < *len - 1; i++) {
		if ((*users)[i].id == id) {
			swap = true;	
		}
		if (swap) {
			(*users)[i] = (*users)[i + 1]; 
		}
	}
	*users = (struct DiscordUser*) realloc(*users, *len - 1);
	*len -= 1;
}

void print_users(struct DiscordUser* users, size_t len) {
	for (size_t i = 0; i < len; i++){
		printf("%s (%ld)\n", users[i].name, users[i].id);	
	}
}

int main() {
	struct DiscordUser* users = (struct DiscordUser*) malloc(0);
	
	size_t len = 0;
	add_user(&users, &len, "Aliquis", 163437468522250240);
	add_user(&users, &len, "Vexcess", 480905025112244234);
	add_user(&users, &len, "WKoA", 724416180097384498);
	
	remove_user(&users, &len, 724416180097384498);
	
	print_users(users, len);

	free(users);
	
	return 0;
}
