#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact_list.h"
#include "contact.h"
#include "utils.h"

// array of linked lists
static CONTACT_T *contacts[26];

// static current pointer
static CONTACT_T *current;

void init_contact_list(void)
{
    for (int i = 0; i < 26; i++)
    {
        contacts[i] = NULL;
    }
}

void insert_contact(CONTACT_T *contact)
{
    int index = contact->last_name[0] - 'A';

    CONTACT_T *cur, *prev;

    // if the list is empty, then make contact the first node
    if (contacts[index] == NULL)
    {
        contacts[index] = contact;
        contacts[index]->next = NULL;
        return;
    }

    // if the new contact needs to be placed before the first node
    if (strcmp(contact->last_name, contacts[index]->last_name) < 0)
    {
        contact->next = contacts[index];
        contacts[index] = contact;
        return;
    }

    cur = contacts[index];
    prev = cur;
    // if the new contact needs to be placed in between two nodes
    while (cur != NULL)
    {
        if (strcmp(contact->last_name, cur->last_name) > 0)
        {
            prev = cur;
            cur = cur->next;
        }
        else
        {
            prev->next = contact;
            contact->next = cur;
            return;
        }
    }

    // if the new contact needs to be placed add the end of the list
    if (cur == NULL)
    {
        prev->next = contact;
        contact->next = cur;
        return;
    }
}

void print_contact_list(char mode)
{
    if (mode == 'c' || mode == 'C')
    {
        for (int i = 0; i < 26; i++)
        {
            CONTACT_T *cur = contacts[i];
            while (cur != NULL)
            {
                print_contact(cur, 'c');
                cur = cur->next;
            }
        }
    }

    if (mode == 'f' || mode == 'F')
    {
        for (int i = 0; i < 26; i++)
        {
            CONTACT_T *cur = contacts[i];
            while (cur != NULL)
            {
                print_contact(cur, 'f');
                cur = cur->next;
            }
        }
    }
    printf("\n");
}

CONTACT_T *find_contact(NAME_T last_name, NAME_T first_name)
{
    NAME_T listLast;
    NAME_T listFirst;
    int index = last_name[0] - 'A';
    CONTACT_T *cur = contacts[index];
    while (cur != NULL)
    {
        strcpy(listLast, cur->last_name);
        strcpy(listFirst, cur->first_name);
        upper(listLast);
        upper(listFirst);
        if ((strcmp(listLast, last_name) == 0) && (strcmp(listFirst, first_name) == 0))
        {
            return cur;
        }
        cur = cur->next;
    }
    return cur;
}

CONTACT_T *get_next_contact(char letter)
{
    int index = letter - 'A';
    if (current == NULL)
    {
        current = contacts[index];
        return current;
    }
    current = current->next;
    return current;
}

void print_state_contacts(char state[], char mode)
{
    int contacts_found = 0;
    for (int i = 0; i < 26; i++)
    {
        CONTACT_T *cur = contacts[i];
        while (cur != NULL)
        {
            if (strcmp(cur->state, state) == 0)
            {
                print_contact(cur, mode);
                contacts_found++;
            }
            cur = cur->next;
        }
    }
    if (contacts_found == 0)
    {
        printf("No contacts found\n");
    }
}

void free_contact_list(void)
{
    for (int i = 0; i < 26; i++)
    {
        CONTACT_T *cur = contacts[i];
        CONTACT_T *temp;
        while (cur != NULL)
        {
            temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
}
