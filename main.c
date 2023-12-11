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

void delete_user(struct DiscordUser** users, size_t* len, long id) {
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
	for (size_t i = 0; i < len; i++) {
		printf("%s (%ld)\n", users[i].name, users[i].id);	
	}
}

void print_user(struct DiscordUser* user_ptr) {
	if (user_ptr == NULL) {
		printf("User not found\n");
	} else {
		struct DiscordUser user = *user_ptr;
		printf("DiscordUser{name=\"%s\",id=%ld}\n", user.name, user.id);
	}
}

struct DiscordUser* find_user(struct DiscordUser* users, size_t len, long id) {
	for (size_t i = 0; i < len; i++) {
		if (users[i].id == id) {
			return &users[i];
		}
	}
	return NULL;
}

int main() {
	struct DiscordUser* users = (struct DiscordUser*) malloc(0);
	
	size_t len = 0;
	add_user(&users, &len, "Aliquis", 163437468522250240);
	add_user(&users, &len, "Vexcess", 480905025112244234);
	add_user(&users, &len, "WKoA", 724416180097384498);
	
	int choice = 0;
	while (choice != 5) {
		printf("-------------------\n\n1: Add User\n2: Delete User\n3: Print Users\n4. Search Users\n5. Exit\n\nChoose option: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1: {
				char name[40];
				long id;
				printf("Enter name: ");
				scanf("%39s", name);
				if (strlen(name) == 0) {
					printf("Name is too short\n");
					break;
				}
				printf("Enter Discord ID: ");
				scanf("%ld", &id);
				printf("Adding user...\n");
				add_user(&users, &len, name, id);
				printf("Added user successfully.\n");
				break;
			}
			case 2: {
				long id;
				printf("Enter Discord ID: ");
				scanf("%ld", &id);
				printf("Deleting user...\n");
				delete_user(&users, &len, id);
				printf("Deleted user successfully.\n");
				break;
			}
			case 3: {
				printf("\nUSERS\n\n");
				print_users(users, len);
				break;
			}
			case 4: {
				long id;
				printf("Enter Discord ID: ");
				scanf("%ld", &id);
				struct DiscordUser* user_ptr = find_user(users, len, id);
				printf("Result: ");
				print_user(user_ptr);
				break;
			}
			case 5: {
				printf("Exiting program...\n");
				break;
			}
			default:
				printf("Invalid choice, please try again.\n");
		}
	}
	free(users);
	
	return 0;
}
