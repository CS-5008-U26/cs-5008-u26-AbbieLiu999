/*
 * citylist.c
 * CS-5008 Summer 2026
 * Dan Liu
 * 
 * This program asks the user to enter a number and read that number of cities from the
 * uscities.csv file. It then creates a variable-length array of city structs and prints 
 * the city name, state, population, latitude, and longitude for each city in the array.
 * The vector doubles the size when its full and is generic.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>


/* ========================================================================
                         vector struct and methods                            
   ======================================================================== */

/* 
 * Struct for a variable vector. 
 */
typedef struct vector_s {
    void **data;
    int size;
    int capacity;
} vector;

 /* 
  * Creates a new variable vector with the specified capacity. 
  */
vector *createVector(int capacity) {
    vector *newVector = malloc(sizeof(vector));
    if (!newVector) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newVector->data = malloc(capacity * sizeof(void*));
    if (!newVector->data) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newVector);
        return NULL;
    }
    newVector->size = 0;
    newVector->capacity = capacity;
    return newVector;
}

/* 
 * Adds a new element to the end of the vector. 
 */
int addLast(vector *v, void *element) {
    if (!v || !element) {
        return 0; // Return 0 if the vector or element is NULL
    }
    if (v->size >= v->capacity) {
        int newCapacity = v->capacity * 2;
        void **newData = malloc(newCapacity * sizeof(void *));
        if (!newData) {
            fprintf(stderr, "Memory allocation failed\n");
            return 0;
        }
        for (int i = 0; i < v->size; i++) {
            newData[i] = v->data[i];
        }
        free(v->data);
        v->data = newData;
        v->capacity = newCapacity;
    }
    (v->data)[v->size] = element; // Add the element to the vector
    v->size++; // Increment the size of the vector
    return 1; // Return 1 to indicate success
}

 /* 
  * Frees the memory allocated for the entire vector. 
  */
void freeVector(vector *v, void (*freeData)(void *)) {
    if (!v) {
        return; // Return if the vector is NULL
    }
    for (int i = 0; i < v->size; i++) {
        if (freeData && v->data[i]) {
            freeData(v->data[i]); // Free the memory allocated for each element
        }
    }
    free(v->data); // Free the memory allocated for the data array
    free(v); // Free the memory allocated for the vector itself
}

/* ========================================================================
                         city struct and methods                            
   ======================================================================== */

/* Struct for a city record. */
typedef struct cityStruct{
    char *cityNameAscii;
    char *stateId;
    int countyFips;
    double latitude;
    double longitude;
    int population;
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
city *stringToCity (char *textLine) {
    city *newCity = malloc(sizeof(city));
    char *p = textLine; 
    char *token = strtok(p, ",");
    int column = 1; // Start from the first column
    while (column <= 9 && token != NULL) { // We only need up to the 9th column
        char temp[10000]; // Allocate a buffer for the temporary string
        stripQuotes(token, temp); // Strip quotes from the token
        switch (column) {
            case 2:
                newCity->cityNameAscii = strdup(temp); // Copy the city name ascii and strip quotes
                break;
            case 3:
                newCity->stateId = strdup(temp); // Copy the state ID and strip quotes
                break;
            case 5:
                newCity->countyFips = atoi(temp); // Convert county FIPS code to an integer
                break;
            case 7:
                newCity->latitude = atof(temp); // Convert latitude to a double
                break;
            case 8:
                newCity->longitude = atof(temp); // Convert longitude to a double
                break;
            case 9:
                newCity->population = atoi(temp); // Convert population to an integer
                break;
        }
        token = strtok(NULL, ","); // Move to the next token
        column++; 
    }
    return newCity;
}

/*
 * Reads n cities from a CSV file and returns a vector of city records.
 */
vector *readCityList (char *filename, int n) {

    // Open the CSV file for reading
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return NULL;
    }
    
    // We just want to check if the variable vector is working correctly, so we
    // create a vector with initial capacity 1 and add n cities to it. The vector will
    // double its size when it is full.
    vector *cityList = createVector(1); 
    if (!cityList) {
        fclose(fp);
        return NULL; // Return NULL if vector creation failed
    }   

    char line[10000];

    // Read the header line and ignore it
    fgets(line, 10000, fp);

    // Read the next n lines of the file
    for (int i = 0; i < n; i++) {
        if (fgets(line, 10000, fp) == NULL) {
            fprintf(stderr, "Error reading line from file.\n");
            fclose(fp);
            return NULL;
        }
        city *newCity = stringToCity(line); // Convert the line to a City struct
        addLast(cityList, newCity); // Add the city to the vector
    }

    fclose(fp); // Close the file
    return cityList; // Return the vector of cities
}

/*
 * Frees the memory allocated for a City struct and its fields.
 */
void freeCity (void *data) {
    city *c = (city *)data;
    free(c->cityNameAscii);
    free(c->stateId);
    free(c); // Free the city struct itself
}

/* ========================================================================
                         BST struct and methods                            
   ======================================================================== */

/*
 * Struct for a binary search tree node.
 */
typedef struct bstNode_s {
    city *data;
    struct bstNode_s *left;
    struct bstNode_s *right;
} bstNode;

/*
 * Creates a new binary search tree node with the given city data.
 */
bstNode *createBSTNode(city *data) {
    bstNode *newNode = malloc(sizeof(bstNode));
    if (!newNode) {
        fprintf(stderr, "Error allocating memory for BST node.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/*
 * Inserts a city into the binary search tree based on latitude.
 */
bstNode *insertCity(bstNode *root, city *newCity) {
    if (root == NULL) {
        return createBSTNode(newCity); // Create a new node if the root is NULL
    }
    if (newCity->latitude < root->data->latitude) {
        root->left = insertCity(root->left, newCity); // Insert into the left subtree
    } else {
        root->right = insertCity(root->right, newCity); // Insert into the right subtree
    }
    return root; // Return the unchanged root pointer
}

/*
 * Inserts a city into the binary search tree based on FIPS code.
 * If a city with the same FIPS code, ignore it.
 */
bstNode *insertCityByFIPS(bstNode *root, city *newCity) {
    if (root == NULL) {
        return createBSTNode(newCity); // Create a new node if the root is NULL
    }
    if (newCity->countyFips < root->data->countyFips) {
        root->left = insertCityByFIPS(root->left, newCity); // Insert into the left subtree
    } else if (newCity->countyFips > root->data->countyFips) {
        root->right = insertCityByFIPS(root->right, newCity); // Insert into the right subtree
    } 
    return root; // Return the unchanged root pointer
}

/*
 * In-order traversal of the binary search tree to place city pointers into 
 * an array. Index tracks the current position in the array.
 */
void inOrder(bstNode *root, city **array, int *index) {
    if (root == NULL) {
        return; // Return if the root is NULL
    }
    inOrder(root->left, array, index); // Traverse the left subtree
    array[*index] = root->data; // Place the city pointer into the array
    (*index)++; // Increment the index
    inOrder(root->right, array, index); // Traverse the right subtree
}

/*
 * Performs a binary search on an array of city pointers based on FIPS code.
 */
int binarySearchFips(city **array, int size, int fips) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid]->countyFips == fips) {
            return mid; // Return the index if the FIPS code is found
        } else if (array[mid]->countyFips < fips) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }
    return -1; // Return -1 if the FIPS code is not found
}

/*
 * Frees all nodes in the BST. Note that the city data is not freed here, 
 * as it is managed separately.
 */
void freeBST(bstNode *root) {
    if (root == NULL) {
        return; // Return if the root is NULL
    }
    freeBST(root->left); // Free the left subtree
    freeBST(root->right); // Free the right subtree
    free(root); // Free the current node
}

/*
 * Main function to read the CSV file and calculate the required values.
 */
int main() {

    // ----------------------------------------------------------------------
    //                               Task 1
    // ----------------------------------------------------------------------

    // Ask the user for the number of cities to read
    int n;
    printf("How many cities: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    while (getchar() != '\n'); // Clear the input buffer   

    // Open the CSV file for reading and create a vector of city records
    vector *cityList = readCityList("../../Resources/uscities.csv", n);
    if (cityList == NULL) {
        fprintf(stderr, "Error reading city list.\n");
        return 1;
    }
    
    // Print the city data for each city in the vector
    for (int i = 0; i < cityList->size; i++) {
        city *c = (city *)cityList->data[i];
        printf("%s %s, population %d, at (%.4f, %.4f)\n",
            c->cityNameAscii,
            c->stateId,
            c->population,
            c->latitude,
            c->longitude);
    }

    // ---------------------------------------------------------------------
    //                               Task 2
    // ---------------------------------------------------------------------

    // Create a binary search tree of cities based on latitude
    bstNode *root = NULL;
    for (int i = 0; i < cityList->size; i++) {
        root = insertCity(root, cityList->data[i]); // Insert each city into the BST
    }

    // In-order traversal of the BST to place city pointers into an array 
    // in order of increasing latitude
    city **sortedCities = malloc(cityList->size * sizeof(city *));
    if (!sortedCities) {
        fprintf(stderr, "Memory allocation failed\n");
        freeVector(cityList, freeCity);
        freeBST(root);
        return 1;
    }
    int index = 0;  
    inOrder(root, sortedCities, &index); // Perform in-order traversal

    // Linear search for New York in the sorted array of cities
    int nyIndex = -1;
    for (int i = 0; i < cityList->size; i++) {
        if (strcmp(sortedCities[i]->cityNameAscii, "New York") == 0) {
            nyIndex = i;
            break;
        }
    }

    if (nyIndex != -1) {
        printf("By latitude, New York is index %d\n", nyIndex);
    } else {
        printf("New York not found in the list.\n");
    }

    // ---------------------------------------------------------------------
    //                               Task 3
    // ---------------------------------------------------------------------
    bstNode *current = NULL;
    for (int i = 0; i < cityList->size; i++) {
        current = insertCityByFIPS(current, cityList->data[i]); // Insert each city into the BST by FIPS
    }

    // In-order traversal of the BST to place city pointers into an array 
    // in order of increasing FIPS code
    city **fipsCities = malloc(cityList->size * sizeof(city *));
    if (!fipsCities) {
        fprintf(stderr, "Memory allocation failed\n");
        freeVector(cityList, freeCity);
        freeBST(current);
        return 1;
    }
    int fipsIndex = 0;  
    inOrder(current, fipsCities, &fipsIndex); // Perform in-order traversal

    // Binary search search for New York in the sorted array of cities
    int fipsNyIndex = binarySearchFips(fipsCities, fipsIndex, 36081); // FIPS code for New York is 36081

    if (fipsNyIndex != -1) {
        printf("By FIPS code, %s is index %d\n", fipsCities[fipsNyIndex]->cityNameAscii, fipsNyIndex);
    } else {
        printf("New York not found in the list.\n");
    }

    // Free all allocated memory 
    free(fipsCities); 
    free(sortedCities);
    freeBST(root);
    freeBST(current); 
    freeVector(cityList, freeCity); 
    return 0;
}

