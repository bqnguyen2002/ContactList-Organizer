
#include "contact.h"
#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H
void insert_contact (CONTACT_T *contact);
void init_contact_list(void);
void print_contact_list(char mode);
CONTACT_T *get_next_contact(char letter);
CONTACT_T *find_contact(NAME_T last_name, NAME_T first_name);
void print_state_contacts(char state[], char mode);
void free_contact_list(void);
#endif