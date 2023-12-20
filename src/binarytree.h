#ifndef BINARYTREE_H
#define BINARYTREE_H

struct binarytree
{
	uint16_t key;
	char *value;
	struct binarytree *left;
	struct binarytree *right;
};

struct binarytree *btinit();
void btfree(struct binarytree *b);
void btput(struct binarytree *b, uint16_t key, char *value);
char *btget(struct binarytree *b, uint16_t key);

#endif
