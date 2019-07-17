#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"

const char *MALLOC_ERROR_MESSAGE = "malloc returned a NULL pointer.";
const char *INPUT_ERROR = "Wrong input: NULL pointer.";

/**
 * the MyString struct
 * */
typedef struct MyString
{
    unsigned int strLength;
    char *str;
} MyString;


/**
 * allocates a new String containing the str1 char*
 * @param str1 a char*
 * @return a new MyString * struct contaning str1
 */

MyStringP createStringFromChars(const char *str1)
{
    if (str1 == NULL)
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }
    MyStringP structptr = (MyStringP) malloc(sizeof(MyStringP));
    if (structptr == NULL)
    {
        fprintf(stderr, MALLOC_ERROR_MESSAGE);
    }
    structptr->str = (char *) str1;
    structptr->strLength = lengthString(structptr);
    return structptr;
}


/**
 * allocates a new String which is a copy of str1
 * @param str1 a String
 * @return a copy of str1
 */
MyStringP createStringFromString(const MyStringP str1)
{
    if (str1 == NULL)
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }
    MyStringP structptr = (MyStringP) malloc(sizeof(MyStringP));
    if (structptr == NULL)
    {
        fprintf(stderr, MALLOC_ERROR_MESSAGE);
    }
    structptr->str = str1->str;
    structptr->strLength = str1->strLength;
    return structptr;
}


/**
 * frees the allocated memory given to the struct
 * @param str1 the string to free
 */
void freeString(MyStringP str1)
{
    free(str1);
}


/**
 * returns the lenght of the given String
 * @param str1 - the string
 * @return lenght of str1
 */
unsigned int lengthString(const MyStringP str1)
{
    // said in the forum that we can return 0 for an error case,
    // because we can only return an unsigned int.
    if (str1 == NULL)
    {
        fprintf(stderr, INPUT_ERROR);
        return 0;
    }
    unsigned int i = 0;
    while (str1->str[i] != '\0')
    {
        i++;
    }
    str1->strLength = i;
    return i;
}


/**
 * returns the value of the given String
 * @param str1 - the string
 * @return the content of str1
 */
const char *cString(const MyStringP str1)
{
    if (str1 == NULL)
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }
    return str1->str;
}


/**
 * Function that returns the strLength of the bigger structure between two parameter
 * @param str1 the first string to compare
 * @param str2 the second string to compare
 * @return the strLength of the bigger structure between two parameter.
 */
unsigned int biggerStructure(const MyStringP str1, const MyStringP str2)
{
    if (str1->strLength >= str2->strLength)
    {
        return str1->strLength;
    }
    else
    {
        return str2->strLength;
    }
}


/**
 * compares the 2 Strings by this logic:
 * compares the 2 strings by the first unmatched char.
 *
 * @param str1 the first string to compare
 * @param str2 the second string to compare
 * @return
 * 1 if the ASCII value of first unmatched character is greater in str1 then str2.
 * 0 if both strings are identical (equal)
 * -1 if the ASCII value of first unmatched character is less in str1 then str2.
 */
int cmpString(const MyStringP str1, const MyStringP str2)
{
    if ((str1 == NULL) || (str2 == NULL))
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }
    unsigned int longerStructure = biggerStructure(str1, str2);
    unsigned int i = 0;
    while (longerStructure > i)
    {
        if (str1->str[i] == str2->str[i])
        {
            i++;
            if ((i == str1->strLength) && (i == str2->strLength))
            {
                return 0;
            }
        }
        else if (str1->str[i] > str2->str[i])
        {
            return 1;
        }
        else if (str1->str[i] < str2->str[i])
        {
            return -1;
        }
    }
    return 0;
}


/**
 * concatenate the 2 Strings in to one String
 * @param str1 the first string in the result, the method will change the value of str1
 * @param str2 the second string in the result
 * @return the result of the concatenate
 */
MyStringP concatString(MyStringP str1, const MyStringP str2)
{
    if ((str1 == NULL) || (str2 == NULL))
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }

    str1 = (MyStringP) realloc(str1, sizeof(str1->strLength + str2->strLength));
    char *newStr = malloc(str1->strLength + str2->strLength);
    for (unsigned int i = 0; i < str1->strLength; ++i)
    {
        newStr[i] = str1->str[i];
    }
    for (unsigned int i = 0; i < str2->strLength; ++i)
    {
        newStr[str1->strLength + i] = str2->str[i];
    }
    newStr[str1->strLength + str2->strLength] = '\0';  // NULL char.
    str1->str = newStr;
    str1->strLength = str1->strLength + str2->strLength;
    return str1;
}


/**
 * deletes a certain char from the String
 * @param str1 the string, changes his value according to the result
 * @param letter the letter to delete from the String
 * @return the result.
 */
MyStringP deleteCharString(MyStringP str1, const char letter)
{
    if (str1 == NULL)
    {
        fprintf(stderr, INPUT_ERROR);
        exit(1);
    }
    unsigned int i, j, deletedChars = 0;
    char *newStr = (char *) malloc(str1->strLength);
    for (i = 0, j = 0; i < str1->strLength; i++)
    {
        if (str1->str[i] != letter)
        {
            newStr[j] = str1->str[i];
            j++;
        }
        else
        {
            deletedChars++;
        }
    }
    newStr[j] = '\0'; // NULL char.
    str1->str = newStr;
    str1->strLength -= deletedChars;
    return str1;
}


/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearance
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const MyStringP str1, const MyStringP str2, int isCyclic)
{
    if ((str1 == NULL) || (str2 == NULL))
    {
        return 0;
    }
    unsigned int counter = 0;
    for (unsigned int i = 0; i < (str1->strLength); ++i)
    {
        unsigned int j = 0;
        int k = i;
        if (!isCyclic)            // Case where isCyclic = 0.
        {
            while ((str2->str[j] != '\0') && (str2->str[j] == str1->str[k]))
            {
                k++;
                j++;
            }
            if (j == str2->strLength)
            {
                counter++;
            }
        }
        else                // Case where isCyclic != 0.
        {
            while ((str2->str[j] != '\0') && (str2->str[j] == str1->str[k]))
            {
                k++;
                j++;

                // Check if we need to go back to the beginning of the str of str1.
                if (str1->str[k] == '\0')
                {
                    k -= str1->strLength;
                }
            }
            if (j == str2->strLength)
            {
                counter++;
            }
        }

    }
    return counter;
}
