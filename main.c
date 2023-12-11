#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct DiscordUser {
	char name[40];
	long id;
};

void add_user(struct DiscordUser** users, size_t* len, char* name, long id) {
	struct DiscordUser new_user;
	strcpy(new_user.name, name);
	new_user.id = id;
	*users = (struct DiscordUser*) realloc(*users, 1 + *len);
	(*users)[*len] = new_user;
	*len += 1;
}

int main() {
	struct DiscordUser* users = (struct DiscordUser*)malloc(2 * sizeof(struct DiscordUser));
	
	size_t len = 0;
	add_user(&users, &len, "Aliquis", 163437468522250240);
	add_user(&users, &len, "Vexcess", 480905025112244234);
	add_user(&users, &len, "WKoA", 724416180097384498);
	
	for (int i = 0; i < len; i++) {
		printf("%s (%ld)\n", users[i].name, users[i].id);
	}
	
	free(users);
	
	return 0;
}
