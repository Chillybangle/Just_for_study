/*!
 * \file
 * \brief Header with descriptions of used in this project functions
 * 
 * This file contains definitions of all main functions which were used
 * in the "Sort the poem" project
 */
#include <stdio.h> // pragma
#include <stdlib.h>
#include <assert.h>
#include "str_func.h"

#ifndef ONEGUINE_FUNCTIONS
#define ONEGUINE_FUNCTIONS

/// a structure which contains a pointer to a string and its size
struct str_pointer
{
    char* p = NULL; //< string pointer
    size_t size = 0; //< size of string
};

/// using constants
const int max_size = 256; //< Max size of file name
const int OK = 993 + 7; //< Return value of sort if everything is all right
const int FAIL = -1; //< Return value of sort if something is wrong
const char name_of_sorted_file[] = "sorted.txt";

/*!
 * \brief The function which execute the rest important ones
 * 
 * \param[in] name name of the file we are interacting with
 */
int launching_function (char* name);

/*! \defgroup user_interaction User interaction 
 * 
 *  \brief This module contains functions to interact with user
 *         (to get name of file and inform about results of the
 *         program)
 * 
 * At present it contains such functions: get_file_name,
 * description, congratulations, failure
 * 
 * @{
 */

/*!
 * \brief Asks user to input the name of the file we are interacting with
 * 
 * \param[in] name pointer to an array which will contain name of the file
 */
void get_file_name(char* name);

/*!
 * \brief A description of the program
 */
void description ();

/*!
 * \brief A message about the correct execution of the program
 */
void congratulations ();

/*!
 * \brief A message about the incorrect execution of the program
 */
void failure ();
/*! @} */

/*! \defgroup file_interaction File interaction
 * 
 *  \brief The functions which process the poem file
 *
 * This functions copy the file into an array, create
 * array of pointers and output the sorted text
 * 
 * @{
 */

/*!
 * \brief Outputs the text to a file
 * 
 * \param[in] sorted_file the pointer to a file
 * \param[in] array_p the struct with pointers to strings of the text
 */
void file_write (FILE* sorted_file, struct str_pointer* array_p);

FILE* sorted_open ();

int original_file_write (FILE* sorted_file, char* array, size_t size_of_elem, size_t nmemb);

size_t fsize (char* name);
/*! @} */

void bubble_sort (void* base, size_t nmemb, size_t size, int (*compar)(const void* a, const void* b));

int Strcmp_compar (const void* struct1, const void* struct2);

int Strcmp_reversed_compar (const void* struct1, const void* struct2);

#endif
