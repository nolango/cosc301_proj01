#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */
struct node {
	int  value;
	struct node *next;
	// note: why not "struct node* next;"
};


/* your function declarations associated with the list */
void list_print(struct node*);
int list_delete(const int, struct node**);
void sorted_insert(int, struct node**);

#endif // __LIST_H__
