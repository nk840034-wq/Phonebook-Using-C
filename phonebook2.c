
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook.h"

contact *head = NULL;

void readLine(char *s, int size)
{
    fgets(s, size, stdin);
    s[strcspn(s, "\n")] = '\0';
}

Contact *findContact(char name[])
{
    Contact *p = head;

    while (p != NULL)
    {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void addContact(void)
{
    Contact *p = calloc(1, sizeof(Contact));
    if (!p) return;

    printf("Name: ");
    readLine(p->name, sizeof(p->name));

    $$$$44G ,mjnyhfffmvmv                           
        printf("Empty or duplicate name!\n");
        free(p);
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Phone %d (Enter to skip): ", i + 1);
        readLine(p->phone[i], sizeof(p->phone[i]));
    }

    printf("Email: ");
    readLine(p->email, sizeof(p->email));

    printf("Address: ");
    readLine(p->address, sizeof(p->address));

    printf("Company: ");
    readLine(p->company, sizeof(p->company));

    printf("Notes: ");
    readLine(p->notes, sizeof(p->notes));

    p->next = head;
    head = p;

    saveContacts();
    printf("Contact added!\n");
}

void displayContacts(void)
{
    Contact *p = head;

    if (!p)
    {
        printf("No contacts found.\n");
        return;
    }

    while (p)
    {
        printf("\nName: %s\n", p->name);
        printf("Phones: %s | %s | %s\n",
               p->phone[0], p->phone[1], p->phone[2]);
        printf("Email: %s\n", p->email);
        printf("Address: %s\n", p->address);
        printf("Company: %s\n", p->company);
        printf("Notes: %s\n", p->notes);
        p = p->next;
    }
}

void searchContact(void)
{
    char name[50];

    printf("Enter name: ");
    readLine(name, sizeof(name));

    Contact *p = findContact(name);

    if (p)
    {
        printf("Found: %s\n", p->name);
        printf("Phones: %s | %s | %s\n",
               p->phone[0], p->phone[1], p->phone[2]);
        printf("Email: %s\n", p->email);
        printf("Address: %s\n", p->address);
        printf("Company: %s\n", p->company);
        printf("Notes: %s\n", p->notes);
    }
    else
        printf("Contact not found.\n");
}

void editContact(void)
{
    char name[50];

    printf("Enter name to edit: ");
    readLine(name, sizeof(name));

    Contact *p = findContact(name);

    if (!p)
    {
        printf("Contact not found.\n");
        return;
    }

    printf("New email (Enter to keep): ");
    char temp[100];
    readLine(temp, sizeof(temp));
    if (temp[0]) strcpy(p->email, temp);

    printf("New address (Enter to keep): ");
    readLine(temp, sizeof(temp));
    if (temp[0]) strcpy(p->address, temp);

    printf("New company (Enter to keep): ");
    readLine(temp, sizeof(temp));
    if (temp[0]) strcpy(p->company, temp);

    printf("New notes (Enter to keep): ");
    readLine(temp, sizeof(temp));
    if (temp[0]) strcpy(p->notes, temp);

    saveContacts();
    printf("Contact updated.\n");
}

void deleteContact(void)
{
    char name[50];

    printf("Enter name to delete: ");
    readLine(name, sizeof(name));

    Contact *p = head, *prev = NULL;

    while (p && strcmp(p->name, name) != 0)
    {
        prev = p;
        p = p->next;
    }

    if (!p)
    {
        printf("Contact not found.\n");
        return;
    }


    free(p);
    saveContacts();
    printf("Contact deleted.\n");
}

void saveContacts(void)
{
    FILE *fp = fopen("contacts.dat", "wb");
    if (!fp) return;

    for (Contact *p = head; p; p = p->next)
    {
        fwrite(p->name, sizeof(p->name), 1, fp);
        fwrite(p->phone, sizeof(p->phone), 1, fp);
        fwrite(p->email, sizeof(p->email), 1, fp);
        fwrite(p->address, sizeof(p->address), 1, fp);
        fwrite(p->company, sizeof(p->company), 1, fp);
        fwrite(p->notes, sizeof(p->notes), 1, fp);
    }

    fclose(fp);
}

void loadContacts(void)
{
    FILE *fp = fopen("contacts.dat", "rb");
    if (!fp) return;

    Contact data = {0};

    while (fread(data.name, sizeof(data.name), 1, fp) == 1)
    {
        if (fread(data.phone, sizeof(data.phone), 1, fp) != 1 ||
            fread(data.email, sizeof(data.email), 1, fp) != 1 ||
            fread(data.address, sizeof(data.address), 1, fp) != 1 ||
            fread(data.company, sizeof(data.company), 1, fp) != 1 ||
            fread(data.notes, sizeof(data.notes), 1, fp) != 1)
            break;

        Contact *p = malloc(sizeof(Contact));
        if (!p) break;

        *p = data;
        p->next = head;
        head = p;
    }

    fclose(fp);
}




