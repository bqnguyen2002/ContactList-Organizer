#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "contact_list.h"
#include "utils.h"

char print_menu(void)
{
    char option[] = "";
    int ask_again = TRUE;
    do
    {
        printf("\n");
        printf("Please select one of the following: \n\n");
        printf(" c  Change output format\n");
        printf(" i  Search for individual\n");
        printf(" t  Print tab\n");
        printf(" s  Look up by state\n");
        printf(" q  Quit\n\n");
        printf("Option: ");
        scanf(" %s", option);
        // echo input
        printf("%s\n\n", option);
        switch (option[0])
        {
        case 'i':
        case 'I':
        case 'C':
        case 'c':
        case 'Q':
        case 'q':
        case 's':
        case 'S':
        case 't':
        case 'T':
            ask_again = FALSE;
            break;
        default:
            printf("Invalid option entered\n");
        }
    } while (strlen(option) > 1 || ask_again == TRUE);
    return option[0];
}

char print_format_menu(void)
{
    char option;
    printf("Please select one of the following: \n\n");
    printf(" c  Condensed output information\n");
    printf(" f  Full output information\n\n");
    printf("Option: ");
    scanf(" %c", &option);
    // echo input
    printf("%c\n", option);
    return option;
}

void process_file(char *filename)
{
    FILE *fd;
    fd = fopen(filename, "r");

    char first_name[15];
    char last_name[15];
    char co_name[35];
    char addr[35];
    char city[20];
    char county[25];
    char state[3];
    char zip[6];
    char phone1[15];
    char phone2[15];
    char email[35];
    char web[45];

    char buffer[1000];
    memset(buffer, 0, 1000);
    //  skip first line
    fgets(buffer, 1000, fd);

    CONTACT_T person;

    while (fscanf(fd, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n] ", first_name, last_name, co_name, addr, city, county, state, zip, phone1, phone2, email, web) != EOF)
    {
        strcpy(person.first_name, first_name);
        strcpy(person.last_name, last_name);
        strcpy(person.co_name, co_name);
        strcpy(person.addr, addr);
        strcpy(person.city, city);
        strcpy(person.county, county);
        strcpy(person.state, state);
        strcpy(person.zip, zip);
        strcpy(person.phone1, phone1);
        strcpy(person.phone2, phone2);
        strcpy(person.email, email);
        strcpy(person.web, web);

        CONTACT_T *contact = create_contact(&person);
        insert_contact(contact);
    }

    fclose(fd);
}

void find_individual(char mode)
{
    NAME_T firstName;
    NAME_T lastName;
    CONTACT_T *ptr;

    printf("Please enter last name: ");
    scanf(" %s", lastName);
    // echo input
    printf("%s\n", lastName);
    printf("Please enter first name: ");
    scanf(" %s", firstName);
    // echo input
    printf("%s\n\n", firstName);

    upper(lastName);
    upper(firstName);

    ptr = find_contact(lastName, firstName);
    if (ptr != NULL)
    {
        print_contact(ptr, mode);
    }
    else
    {
        printf("Contact not found\n");
    }
}

void print_tab(char mode)
{
    char tab_letter[1];
    CONTACT_T *ptr;

    printf("Please enter last name tab letter: ");
    scanf(" %s", tab_letter);
    // echo input
    printf("%s\n\n", tab_letter);

    upper(tab_letter);
    ptr = get_next_contact(tab_letter[0]);

    if (ptr == NULL)
    {
        printf("No contacts found\n");
    }

    while (ptr != NULL)
    {
        print_contact(ptr, mode);
        ptr = get_next_contact(tab_letter[0]);
    }
}

void process_state_contacts(char mode)
{
    char state[2] = "";

    printf("Please enter two-letter state abbreviation: ");
    scanf(" %s", state);
    // echo input
    printf("%s\n\n", state);
    upper(state);
    print_state_contacts(state, mode);
}

void main(int argc, char *argv[])
{
    char mode = 'c';
    char option;
    int ask_again = TRUE;

    // checks command line argument info to ensure contact file is specified; if not a message is
    // printed and exit is called with a EXIT_FAILURE status
    if (strcmp(argv[1], "addrcsv.txt") != 0)
    {
        printf("Error: wrong contact file...");
        exit(EXIT_FAILURE);
    }

    init_contact_list();
    process_file(argv[1]);
    print_contact_list(mode);

    do
    {
        option = print_menu();
        switch (option)
        {
        case 'C':
        case 'c':
            mode = print_format_menu();
            break;
        case 'I':
        case 'i':
            find_individual(mode);
            break;
        case 'T':
        case 't':
            print_tab(mode);
            break;
        case 'S':
        case 's':
            process_state_contacts(mode);
            break;
        case 'Q':
        case 'q':
            ask_again = FALSE;
        }

    } while (ask_again == TRUE);

    free_contact_list();
}
