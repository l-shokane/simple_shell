#include "shell.h"

/**
 * length_list - Function that determines length of linked list
 * @h: A pointer to first node
 * Return: Length of list
 */
size_t length_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * strings_lists -  Function that returns an array of strings of the list
 * @head: A pointer to first node
 * Return:  An array of strings
 */
char **strings_lists(list_t *head)
{
	list_t *node = head;
	size_t i = length_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_str(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * my_printList -  Function that prints all elements of a list_t linked list
 * @h: pointer
 * Return:  The size of list
 */
size_t my_printList(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		my_print(convrt_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		my_print(h->str ? h->str : "(nil)");
		my_print("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_creates - Function returns node
 * @node:  A pointer to list head
 * @prefix: string 
 * @c: next character 
 *
 * Return: If successful match node OR NULL if not
 */
list_t *node_create(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begins_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_index_node - Function that gets the index of a node
 * @head:  A pointer to list head
 * @node:  A pointer to the node
 *
 * Return: if successful index of node OR -1 if not
 */
ssize_t get_index_node(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
