#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct DiscordUser {
	char name[40];
	long id;
};

int main() {
	struct DiscordUser* users = (struct DiscordUser*)malloc(2 * sizeof(struct DiscordUser));

	strcpy(users[0].name, "Aliquis");
	users[0].id = 163437468522250240;	

	strcpy(users[1].name, "Vexcess");
	users[1].id = 480905025112244234;
			
	for (int i = 0; i < 2; i++) {
		printf("%s (%ld)\n", users[i].name, users[i].id);
	}
		
	return 0;
}
