#include "shell.h"

/**
 * node_next -Function that adds  node at the start of list
 * @head: Address of pointer first node
 * @str: string
 * @num: node index
 * Return:  The size of list
 */
list_t *node_next(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	shell_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = strd_up(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_end_node - Function that adds a node to end of list
 * @head: Address of pointer
 * @str: string
 * @num: node index
 *
 * Return:  The size of list
 */
list_t *add_end_node(list_t **head, const char *str, int num)
{
	list_t *node_new, *node;

	if (!head)
		return (NULL);

	node = *head;
	node_new = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	shell_memset((void *)new_node, 0, sizeof(list_t));
	node_new->num = num;
	if (str)
	{
		node_new->str = strd_up(str);
	if (!node_new->str)
		{
			free(node_new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = node_new;
	}
	else
		*head = node_new;
	return (node_new);
}

/**
 * myprint_listStr - prints only the str element of a list_t linked list
 * @h: pointer
 *
 * Return: The size of list
 */
size_t myprint_listStr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		my_print(h->str ? h->str : "(nil)");
		my_print("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_del_index - Function that deletes node at given index
 * @head: Address of pointer 
 * @index: index of node
 *
 * Return: If successful 1 or 0 if it fails.
 */
int node_del_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * node_list_free - Function that frees all nodes of a list
 * @head_ptr: Address of pointer
 */
void node_list_free(list_t **head_ptr)
{
	list_t *node, *node_next, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = node_next;
	}
	*head_ptr = NULL;
}
