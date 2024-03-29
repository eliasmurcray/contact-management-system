#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char name[40];
	long id;
} DiscordUser;

void add_user(DiscordUser **users, size_t *len, const char *name, const long id) {
	DiscordUser new_user;
	strncpy(new_user.name, name, 39);
	new_user.name[39] = '\0';
	new_user.id = id;
	*users = (DiscordUser*) realloc(*users, *len + 1);
	(*users)[*len] = new_user;
	*len += 1;
}

void delete_user(DiscordUser **users, size_t *len, long id) {
	bool swap = false;
	for (size_t i = 0; i < *len - 1; i++) {
		if ((*users)[i].id == id) {
			swap = true;	
		}
		if (swap) {
			(*users)[i] = (*users)[i + 1]; 
		}
	}
	*users = (DiscordUser*) realloc(*users, *len - 1);
	*len -= 1;
}

void print_users(DiscordUser *users, size_t len) {
	for (size_t i = 0; i < len; i++) {
		printf("%s (%ld)\n", users[i].name, users[i].id);	
	}
}

void print_user(DiscordUser *user_ptr) {
	if (user_ptr == NULL) {
		printf("User not found\n");
	} else {
		DiscordUser user = *user_ptr;
		printf("DiscordUser{name=\"%s\",id=%ld}\n", user.name, user.id);
	}
}

DiscordUser *find_user(DiscordUser *users, size_t len, long id) {
	for (size_t i = 0; i < len; i++) {
		if (users[i].id == id) {
			return &users[i];
		}
	}
	return NULL;
}

long prompt_id() {
	long id;
	while (1) {
		printf("Enter Discord ID: ");
		if (scanf("%ld", &id) != 1) {
			printf("Error, invalid input. Please enter a long.\n");
			int c;
            		while ((c = getchar()) != '\n' && c != EOF);
		} else {
			break;
		}
	}
	return id;
}

int main() {
	DiscordUser *users = (DiscordUser*) malloc(0);
	
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
				printf("Enter name: ");
				scanf("%s", name);
				if (strlen(name) == 0) {
					printf("Name is too short\n");
					break;
				}
				long id = prompt_id();
				printf("Adding user...\n");
				add_user(&users, &len, name, id);
				printf("Added user successfully.\n");
				break;
			}
			case 2: {
				long id = prompt_id();
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
				long id = prompt_id();
				DiscordUser *user_ptr = find_user(users, len, id);
				printf("Result: ");
				print_user(user_ptr);
				break;
			}
			case 5: {
				printf("Exiting program...\n");
				free(users);
				break;
			}
			default:
				printf("Invalid choice, please try again.\n");
		}
	}
	
	return 0;
}
