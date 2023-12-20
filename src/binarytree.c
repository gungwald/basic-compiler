#include <string.h>

#include "binarytree.h"
#include "fail.h"


//struct binarytree
//{
	//uint16_t key;
	//char *value;
	//struct binarytree *left;
	//struct binarytree *right;
//};

struct binarytree *btinit()
{
	b = (struct binarytree *) malloc(sizeof(struct binarytree));
	if (b == NULL)
		fail("btinit");
	b->value = NULL;
	b->left = NULL;
	b->right = NULL;
	return b;
}

void btfree(struct binarytree *b)
{
	/* TODO: Implement btfree */
}

void btput(struct binarytree *b, uint16_t key, char *value)
{
	if (b->value == NULL) {
		b->key = key;
		b->value = value;
		return;
	}

}

char *btget(struct binarytree *b, uint16_t key)
{
}

