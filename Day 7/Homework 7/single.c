/*
 * single.c
 *
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * This program reads in uscities.csv file and creates a singly-linked list of city
 * recoreds. Each city will be one node in the linked list and the list will be a 
 * singly-linked generic list.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ========================================================================
                         sNode struct and methods                            
   ======================================================================== */

/* 
 * Struct for a single node in the linked list. 
 */
typedef struct singleNode {
    void *data; 
    struct singleNode *next;
} sNode;

 /* 
  * Creates a new node. 
  */
sNode* createNode(void *data) {
    sNode *newNode = malloc(sizeof(sNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/* 
 *Adds a node to the front of the list. 
 */
sNode* addFront(sNode *list, sNode *newNode) {
    newNode->next = list;
    return newNode; // Return the new head of the list
}

/* 
 * Adds a node to the end of the list. 
 */
sNode* addEnd(sNode *list, sNode *newNode) {
    if (!list) {
        return newNode; // If the list is empty, the new node becomes the head
    }
    sNode *currentNode = list;
    while (currentNode->next) {
        currentNode = currentNode->next; // Traverse to the end of the list
    }
    currentNode->next = newNode; // Link the new node at the end
    return list; // Return the head of the list
}

/* 
 * Gets a pointer to the n-th sNode in the list. 
 */
sNode* getNode(sNode *list, int n) {
    if (n < 0) {
        return NULL; // Return NULL if n is negative
    }
    sNode *currentNode = list;
    int i = n;
    while (i > 0 && currentNode) {
        currentNode = currentNode->next; // Move to the next node
        i--;
    }
    return currentNode; // Return a pointer to the n-th node
}

/*
 * Detach a given node from the list. 
 */
sNode* detachNode(sNode *list, sNode *nodeToDetach) {
    
    // If the list is empty or the node to detach is NULL, return the original list
    if (!list || !nodeToDetach) {
        return list; 
    }

    // If the node to detach is the head of the list
    if (list == nodeToDetach) {
        return list->next; 
    }

    // Traverse the list to find the node to detach
    sNode *currentNode = list;
    while (currentNode->next && currentNode->next != nodeToDetach) {
        currentNode = currentNode->next; // Move to the next node
    }

    if (currentNode->next == nodeToDetach) {
        currentNode->next = currentNode->next->next; // Bypass the node to detach
    }

    return list; // Return the head of the list
}

/* 
 * Deletes a given sNode from the list. 
 */
sNode* deleteNode(sNode *list, sNode *nodeToDelete, void (*freeData)(void *)) {
    list = detachNode(list, nodeToDelete); // Detach the node from the list
    if (freeData && nodeToDelete->data) {
        freeData(nodeToDelete->data); // Free the memory allocated for the node's data
    }
    free(nodeToDelete); // Free the memory allocated for the node
    return list; // Return the head of the list  
}

/*
 * Gets the length of the list. 
 */
 int getLength(sNode *list) {
    int length = 0;
    sNode *currentNode = list;
    while (currentNode) {
        length++; // Increment the length for each node
        currentNode = currentNode->next; // Move to the next node
    }
    return length; // Return the total length of the list
 }

 /* 
  * Frees the memory allocated for the entire list. 
  */
void freeList(sNode *list, void (*freeData)(void *)) {
    sNode *currentNode = list;
    while (currentNode) {
        sNode *nextNode = currentNode->next; // Store the next node
        if (freeData && currentNode->data) {
            freeData(currentNode->data); // Free the memory allocated for the node's data
        }
        free(currentNode); // Free the memory allocated for the node
        currentNode = nextNode; // Move to the next node
    }
}


/* ========================================================================
                         city struct and methods                            
   ======================================================================== */

/* Struct for a city record. */
typedef struct cityStruct{
    char *cityName;
    char *cityNameAscii;
    char *stateId;
    char *stateName;
    char *countyFips;
    char *countyName;
    double latitude;
    double longitude;
    long population;
    } city;

/*
 * Removes all double-quote characters from the input string
 * and copies the result into the output string.
 */
void stripQuotes(char *in, char *out) {
    while (*in) {
        if (*in != '"') {
            *out = *in;
            out++;
        }
        in++;
    }
    *out = '\0'; // Null-terminate the output string
}

/*
 * Converts a line of text from the CSV file into a City struct.
 */
city* stringToCity (char *textLine) {
    city *newCity = malloc(sizeof(city));
    char *p = textLine; 
    char *token = strtok(p, ",");
    int column = 1; // Start from the first column
    while (column <= 9 && token != NULL) { // We only need up to the 9th column
        char temp[10000]; // Allocate a buffer for the temporary string
        stripQuotes(token, temp); // Strip quotes from the token
        switch (column) {
            case 1:
                newCity->cityName = strdup(temp); // Copy the city name and strip quotes
                break;
            case 2:
                newCity->cityNameAscii = strdup(temp); // Copy the city name ascii and strip quotes
                break;
            case 3:
                newCity->stateId = strdup(temp); // Copy the state ID and strip quotes
                break;
            case 4:
                newCity->stateName = strdup(temp); // Copy the state name and strip quotes
                break;
            case 5:
                newCity->countyFips = strdup(temp); // Copy the county FIPS code and strip quotes
                break;
            case 6:
                newCity->countyName = strdup(temp); // Copy the county name and strip quotes
                break;
            case 7:
                newCity->latitude = atof(temp); // Convert latitude to a double
                break;
            case 8:
                newCity->longitude = atof(temp); // Convert longitude to a double
                break;
            case 9:
                newCity->population = atol(temp); // Convert population to a long integer
                break;
        }
        token = strtok(NULL, ","); // Move to the next token
        column++; 
    }
    return newCity;
}

/*
 * Reads a list of cities from a CSV file and returns a single-linked list of city records.
 */
sNode* readCityList (char *filename) {
    // Open the CSV file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }

    char line[10000];
    sNode *head = NULL;
    sNode *current = NULL;

    // Read the header line and ignore it
    fgets(line, 10000, fp);

    // Read the next 20 lines of the file
    for (int i = 0; i < 20; i++) {
        if (fgets(line, 10000, fp) == NULL) {
            fprintf(stderr, "Error reading line from file.\n");
            fclose(fp);
            return NULL;
        }
        city *newCity = stringToCity(line); // Convert the line to a City struct
        sNode *newNode = createNode(newCity); // Create a new node for the city
        if (!newNode) {
            fclose(fp);
            return NULL; // Return NULL if node creation failed
        }
        if (!head) { // If the list is empty, set the new node as the head
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    fclose(fp); // Close the file
    return head; // Return the head of the list
}

/*
 * Frees the memory allocated for a City struct and its fields.
 */
void freeCity (void *data) {
    city *c = (city *)data;
    free(c->cityName);
    free(c->cityNameAscii);
    free(c->stateId);
    free(c->stateName);
    free(c->countyFips);
    free(c->countyName);
    free(c); // Free the city struct itself
}

/*
 * Main function to read the CSV file and calculate the required values.
 */
int main() {
    // Open the CSV file for reading and create a singly-linked list of city records
    sNode *cityList = readCityList("../../Resources/uscities.csv");
    if (cityList == NULL) {
        fprintf(stderr, "Error reading city list.\n");
        return 1;
    }
    
    char buffer[100];
    char command[100];
    int cityNumber;

    // Loop to process user commands
    while (1) {
        printf("size, delete, reverse, get, or print: ");
        if (!fgets(command, sizeof(command), stdin)) {
            fprintf(stderr, "Error reading input.\n");
            break;
        }
        command[strcspn(command, "\n")] = 0; // Remove the newline character from the input

        // If the user enters "size", print thr size of the list
        if (strcmp(command, "size") == 0) {
            printf("Size is %d\n", getLength(cityList));
            continue;
        }

        // If the user enters "delete", ask for a city number and delete the corresponding
        // city node from the list
        if (strcmp(command, "delete") == 0) {
            printf("Enter a number: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }
            buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character from the input
            cityNumber = atoi(buffer);
            if (cityNumber < 1 || cityNumber > getLength(cityList)) {
                fprintf(stderr, "Invalid city number. Please enter a number between 1 and %d.\n", getLength(cityList));
                continue;
            }
            sNode *nodeToDelete = getNode(cityList, cityNumber - 1);
            cityList = deleteNode(cityList, nodeToDelete, freeCity); // Delete the node and free its data
            continue;
        }

        // If the user enters "reverse", reverse the order of the nodes in the list
        if (strcmp(command, "reverse") == 0) {
            sNode *prev = NULL;
            sNode *current = cityList;
            sNode *next = NULL;
            while (current) {
                next = current->next; // Store the next node
                current->next = prev; // Reverse the link
                prev = current; // Move prev to current
                current = next; // Move to the next node
            }
            cityList = prev; // Update the head of the list
            continue;
        }

        // If the user enters "get", ask for a city number and move the corresponding
        // city node to the front of the list
        if (strcmp(command, "get") == 0) {
            printf("Enter a number: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }
            buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character from the input
            cityNumber = atoi(buffer);
            if (cityNumber < 1 || cityNumber > getLength(cityList)) {
                fprintf(stderr, "Invalid city number. Please enter a number between 1 and %d.\n", getLength(cityList));
                continue;
            }
            if (cityNumber == 1) {
                continue; // If the node is already at the front, do nothing
            }
            sNode *nodeToMove = getNode(cityList, cityNumber - 1);
            cityList = detachNode(cityList, nodeToMove); // Detach the node from its current position
            cityList = addFront(cityList, nodeToMove); // Add the node to the front of the list
            continue;
        }

        // If the user enters "print", ask for a number and print the city data for the first 
        // n nodes in the list
        if (strcmp(command, "print") == 0) {
            printf("Enter a number: ");
            if (!fgets(buffer, sizeof(buffer), stdin)) {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }
            buffer[strcspn(buffer, "\n")] = 0; // Remove the newline character from the input
            cityNumber = atoi(buffer);
            if (cityNumber < 1 || cityNumber > getLength(cityList)) {
                fprintf(stderr, "Invalid city number. Please enter a number between 1 and %d.\n", getLength(cityList));
                continue;
            }
            sNode *current = cityList;
            for (int i = 0; i < cityNumber && current; i++) {
                printf("%s %s, population %ld\n",
                    ((city *)current->data)->cityName,
                    ((city *)current->data)->stateId,
                    ((city *)current->data)->population);
                current = current->next; // Move to the next node
            }
            continue;
        }
        break; // Exit the loop if the command is not recognized
    } 
    freeList(cityList, freeCity); // Free the memory allocated for the city list
    return 0;
}

