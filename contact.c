
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

CONTACT_T *create_contact(CONTACT_T *contact)
{
    CONTACT_T *node = (CONTACT_T *)malloc(sizeof(*node));
    strcpy(node->addr, contact->addr);
    strcpy(node->city, contact->city);
    strcpy(node->co_name, contact->co_name);
    strcpy(node->county, contact->county);
    strcpy(node->email, contact->email);
    strcpy(node->first_name, contact->first_name);
    strcpy(node->last_name, contact->last_name);
    strcpy(node->phone1, contact->phone1);
    strcpy(node->phone2, contact->phone2);
    strcpy(node->state, contact->state);
    strcpy(node->zip, contact->zip);
    strcpy(node->web, contact->web);
    return node;
}

void print_contact(CONTACT_T *contact, char mode)
{
    if (mode == 'c' || mode == 'C')
    {
        printf("%-15s   %-15s   %s   %s\n", contact->last_name, contact->first_name, contact->phone1, contact->email);
    }
    if (mode == 'f' || mode == 'F')
    {
        printf("Name:    %s %s\n", contact->first_name, contact->last_name);
        printf("Address: %s, %s, %s %s  (%s County)\n", contact->addr, contact->city, contact->state, contact->zip, contact->county);
        printf("Phone:   %s (primary)  %s\n", contact->phone1, contact->phone2);
        printf("email:   %s\n", contact->email);
        printf("web:     %s\n\n", contact->web);
    }
}