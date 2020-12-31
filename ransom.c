#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_OF_WORD 6

char* readline();
char** split_string(char*);


typedef struct magazine_node magazine_node;
typedef struct linked_list linked_list;


struct magazine_node {
	char word[SIZE_OF_WORD];
	int used; // tell me if the word were used or not ,present simple passive.//
	magazine_node *next;
};

struct linked_list {
	  magazine_node *head ;
	  magazine_node *tail;

};

magazine_node* create_node(char* magazine){
	magazine_node* node = malloc(sizeof(magazine_node));
	if (node == NULL) return NULL;
	strcpy(node->word,magazine);
	node->used = 1;
	node->next = NULL;
	return node;
}

void insert_node(struct linked_list *link_list
				,char* magazine){
	struct magazine_node* node =  create_node(magazine);
	if(!((*link_list).head)){
		(*link_list).head = node;
	}
	else {
		(*link_list).tail->next= node;
	}

	(*link_list).tail = node;
}

void free_list(struct magazine_node* node){
	while(node){
	magazine_node* temp = node;
	node = node->next;
	free(temp);
	}
}





void checkMagazine(int magazine_count,
					char** magazine,
					int note_count,
					char** note) {
	linked_list* magazine_list = malloc(sizeof(linked_list));
	struct magazine_node *node,*current_head;

	int counter = 0;
	for (int i = 0; i < magazine_count; i++){
	node = create_node(magazine[i]);
	insert_node( magazine_list , magazine[i]);
	}
	for (int i = 0; i < note_count; i++){
		for( current_head = magazine_list->head;
				current_head; current_head = current_head->next){
			if(((strcasecmp(current_head->word,note[i])) == 0) && (current_head->used)){
			current_head->used = 0;
			counter++;
			break;
			}
		}
	}
	free_list(node);
	if(counter == note_count){
		printf("Yes");
	}
	else{
		printf("No");
	}
}

// Complete the checkMagazine function below.
int main()
{

    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
