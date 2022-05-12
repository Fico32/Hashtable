#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C12.h"


struct hash make_table(int s)
{
	struct anode **ptr = malloc(s*sizeof(void *));
	for (int i = 0; i < s; ++i)
	{
		ptr[i] = NULL;
	}
	struct hash h = {s,ptr};
	return h;
}

char *search(struct hash T, int k)
{
	struct anode *lst = T.table[k%(T.size)];
	if(lst == NULL)
		return NULL;
	else
	{
		while(lst->key != k)
		{
			if(lst->next == NULL)
				return NULL;
			lst = lst->next;
		}
		return lst->value;
	}
}

void add(struct hash T, int k, char *v)
{
	struct anode *lst = T.table[k%(T.size)];
	struct anode *newlst = malloc(sizeof(struct anode));
	char *val = malloc(sizeof(char)*(strlen(v)+1));
	strcpy(val,v);
	newlst->key = k; 
	newlst->value = val;
	newlst->next = NULL;
	if(lst == NULL)
	{
		T.table[k%(T.size)] = newlst;
	}
	else
	{
		while(lst->next != NULL)
		{
			if(lst->key == k)
			{
				free(lst->value);
				lst->value = val;
				free(newlst);
				return;
			}
			lst = lst->next;
		}
		if(lst->key == k)
		{
			free(lst->value);
			lst->value = val;
			free(newlst);
		}
		else
			lst->next = newlst;
	}
}

void free_table(struct hash T)
{
	struct anode *lst;
	struct anode *temp;
	for(int i = 0; i < T.size; ++i)
	{
		lst = T.table[i];
		if(lst != NULL)
		{
			while(lst->next != NULL)
			{
				temp = lst;
				lst = lst->next;
				free(temp->value);
				free(temp);
			}
			free(lst->value);
			free(lst);
		}
	}
	free(T.table);
	T.table = NULL;
}

void delete(struct hash T, int k)
{
	struct anode *lst = T.table[k%(T.size)];
	struct anode *last = T.table[k%(T.size)];
	if(lst != NULL && lst->key == k)
	{
		T.table[k%(T.size)] = lst->next;
		free(lst->value);
		free(lst);
	}
	else if(lst != NULL)
	{
		while(lst->key != k)
		{
			if(lst->next == NULL)
				return;
			last = lst;
			lst = lst->next;
		}
		last->next = lst->next;
		free(lst->value);
		free(lst);
	}
}