#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 1000
#define MAX_WORDS 1000
#define NUM_KEYWORDS 19
#define MAX_KEYWORD_LENGTH 7
 
// Define an array of strings to store the keywords
char keywords[NUM_KEYWORDS][MAX_WORD_LENGTH + 1] = {
    "sell", "buy", "go", "to", "from", "and", "at", "has", "if", "less",
    "more", "than", "exit", "where", "total", "who", "NOBODY", "NOTHING", "NOWHERE"};

// Defining the desired structure to store people with, name, location and items
typedef struct
{
    char name[100];
    int quantity;
} Item;

typedef struct
{
    char name[100];
    char location[100];
    char previusLocation[100];
    int inventoryCount;
    Item inventory[100];

} Subject;
typedef struct
{
    char name[100];
} Location;

Subject people[100];
char locationlist[1000][1000]; // List of all locations
int locationcnt = 0;
char itemlist[1000][1000]; // List of all items
int itemcnt = 0;
int people_count = 0;

/// @brief Check if a char[] is integer (only consisting of integers)
/// @param str
/// @return 1 or 0
int containsNumber(const char *str)
{
    while (*str)
    {
        if (isdigit(*str))
        {
            return 1; // Number found
        }
        str++;
    }
    return 0; // No number found
}

/// @brief Check if a char[] is integer (only consisting of integers)
/// @param str
/// @return 1 or 0
int isFullNumber(const char *str)
{
    while (*str)
    {
        if (isdigit(*str) != 1)
        {
            return 0;
        }
        str++;
    }
    return 1;
}

/// @brief Check if "strtosearch" is in "tmplist"
/// @param tmplist
/// @param strtosearch
/// @param tmpcount
/// @return 1 or 0
int isIntheList(char tmplist[MAX_WORDS][MAX_WORD_LENGTH], char strtosearch[100], int tmpcount)
{
    for (int i = 0; i < tmpcount; i++)
    {
        if (strcmp(tmplist[i], strtosearch) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/// @brief Check if a "strtosearch" is in keywords given
/// @param strtosearch
/// @return
int isInKeywords(char strtosearch[100])
{
    for (int i = 0; i < NUM_KEYWORDS; i++)
    {
        if (strcmp(keywords[i], strtosearch) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/// @brief Check the first if
/// @param words words to search
/// @param word_count count until
/// @param starting_index count from
/// @return the index of "if"
int ifFinder(char words[MAX_WORDS][MAX_WORD_LENGTH], int word_count, int starting_index)
{
    for (int i = starting_index; i < word_count; i++)
    {
        if (strcmp(words[i], "if") == 0)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Check the first "at"
/// @param words words to search
/// @param word_count count until
/// @param starting_index count from
/// @return the index of "at"
int atFinder(char words[MAX_WORDS][MAX_WORD_LENGTH], int word_count, int starting_index)
{
    for (int i = starting_index; i < word_count; i++)
    {
        if (strcmp(words[i], "at") == 0)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Check the first "has"
/// @param words words to search
/// @param word_count count until
/// @param starting_index count from
/// @return the index of "has"
int hasFinder(char words[MAX_WORDS][MAX_WORD_LENGTH], int word_count, int starting_index)
{
    for (int i = starting_index; i < word_count; i++)
    {
        if (strcmp(words[i], "has") == 0)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Compare
/// @param a
/// @param b
/// @return a>b 1 | a=b 0 | a<b -1|
int comparator(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/// @brief find the person
/// @param s
/// @return the index
int findPerson(char *s)
{
    for (int i = 0; i < people_count; i++)
    {
        if (strcmp(people[i].name, s) == 0)
        {
            return i;
        }
    }
    return -1;
}

/// @brief find the item of a person
/// @param p person's index
/// @param s
/// @return the index
int findPersonsItem(int p, char *s)
{
    for (int i = 0; i < people[p].inventoryCount; i++)
    {
        if (strcmp(people[p].inventory[i].name, s) == 0)
        {
            return i;
        }
    }
    return -1;
}

/// @brief Buy
/// @param personname
/// @param itemname
/// @param quantity
void buy(char *personname, char *itemname, int quantity)
{
    int tmppersonid = findPerson(personname);
    int tmpitemid = findPersonsItem(tmppersonid, itemname);
    if (tmpitemid != -1)
        people[tmppersonid].inventory[tmpitemid].quantity += quantity;
    else
    {
        int tmpinvcnt = people[tmppersonid].inventoryCount;
        people[tmppersonid].inventoryCount++;
        strcpy(people[tmppersonid].inventory[tmpinvcnt].name, itemname);
        people[tmppersonid].inventory[tmpinvcnt].quantity = quantity;
    }
}

/// @brief Sell
/// @param personname
/// @param itemname
/// @param quantity
void sell(char *personname, char *itemname, int quantity)
{
    int tmppersonid = findPerson(personname);
    int tmpitemid = findPersonsItem(tmppersonid, itemname);
    if (tmpitemid != -1)
    {
        people[tmppersonid].inventory[tmpitemid].quantity -= quantity;
    }
    else
    {
        int tmpinvcnt = people[tmppersonid].inventoryCount;
        people[tmppersonid].inventoryCount++;
        strcpy(people[tmppersonid].inventory[tmpinvcnt].name, itemname);
        people[tmppersonid].inventory[tmpinvcnt].quantity -= quantity;
    }
}

int main()
{

    char words[MAX_WORDS][MAX_WORD_LENGTH]; // Array to store words
    int word_count = 0;                     // Number of words entered
    char input[MAX_WORD_LENGTH];

    while (1)
    {
        int ifFound = 0;
        printf(">> ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin); // Read a line of input

        // Remove newline character if present
        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        // Get the input and add them to "words"
        word_count = 0;
        memset(words, 0, sizeof(words));

        char *token = strtok(input, " "); // Split by spaces

        while (token != NULL)
        {
            if (word_count < MAX_WORDS)
            {
                strcpy(words[word_count], token); // Copy the word into the words array
                word_count++;
            }
            else
            {
                break;
            }
            token = strtok(NULL, " "); // Get the next token
        }


        ////// VALIDITY PART ///////

        // Find "if"
        int ifIndexValidity = ifFinder(words, word_count, 0);

        // Validity variable to check validity of the sentence
        int validity = 1;
        int currentindex = 0;
        int destindex = 0;
        int tmpres = 1;

        // If the last word of the sentence or last word before if is "and"
        if (strcmp(words[word_count - 1], "and") == 0)
        {
            validity = 0;
        }
        if (strcmp(words[ifIndexValidity - 1], "and") == 0)
        {
            validity = 0;
        }

        // If no "if" found, dont check if validity
        if (ifIndexValidity == -1)
        {
            ifIndexValidity = word_count;
        }

        // Check validity until the if is found
        for (int i = 0; i < ifIndexValidity; i++)
        {
            // No last item | no "?"
            if (i == ifIndexValidity - 1 && tmpres == 1 && strcmp(words[ifIndexValidity - 1], "?") != 0)
            {
                validity = 0;
            }

            // If "go,buy,sell" found
            if (strcmp(words[i], "go") == 0 || strcmp(words[i], "buy") == 0 || strcmp(words[i], "sell") == 0)
            {
                tmpres = 0;
                destindex = i;

                // Loop until the index of them
                for (int j = currentindex; j < destindex; j++)
                {
                    // words before them is not in location/item list | not a keyword | don't contain number
                    if (isIntheList(locationlist, words[j], locationcnt) || isIntheList(itemlist, words[j], itemcnt) || isInKeywords(words[j]) || containsNumber(words[j]))
                    {
                        validity = 0;
                    }

                    else
                    {
                        // if not at the end | the next one is not "and"
                        if (j != destindex - 1 && strcmp(words[j + 1], "and") != 0)
                        {
                            validity = 0;
                        }

                        else
                        {
                            j++;
                        }
                    }
                }

                currentindex = destindex;

                /// BUY
                if (strcmp(words[i], "buy") == 0)
                {
                   
                    currentindex = i + 1;  // put the index just after it
                    int numberseen = 0;  // var to check if we checked an integer after the buy, before
                    int tmpvalid = 1;  
                    while (1)
                    {

                        if (!isFullNumber(words[currentindex]))
                        {
                            if (numberseen == 0) // If the first number we see is not a fullnumber -> No valid
                            {
                                validity = 0;
                                break;
                            }
                            else
                            {
                                tmpvalid = 0; // we dont know another sentence continues, keep temporary validity
                            }
                        }
                        else
                        {
                            numberseen = 1; // first number we see
                        }

                        currentindex++;
                        // Must be item
                        if (isIntheList(locationlist, words[currentindex], locationcnt) || isInKeywords(words[currentindex]) || containsNumber(words[currentindex]) || findPerson(words[currentindex]) != -1)
                        {
                            validity = 0;
                            break;
                        }
                        currentindex++;

                        // looping untill "if"
                        if (currentindex == ifIndexValidity)
                        {
                            break;
                        }

                        // if current word is "and"
                        else if (strcmp(words[currentindex], "and") == 0)
                        {
                            if (isFullNumber(words[currentindex + 1])) // next one integer 
                            {
                                currentindex++;
                                continue;
                            }
                            else
                            {
                                int tmpindex = currentindex;

                                // Loop to check if we have and or from after buy
                                while (1)
                                {

                                    if (tmpindex >= ifIndexValidity)
                                    {
                                        break;
                                    }

                                    if (strcmp(words[tmpindex], "and") == 0)
                                    {
                                        if (isFullNumber(words[tmpindex + 1])) // If we have int after "and" 
                                        {
                                            tmpindex++;
                                        }
                                        tmpindex += 2;
                                    }

                                    else if (strcmp(words[tmpindex], "from") == 0) 
                                    {
                                        validity = 0; // If we have "from" after "buy" but no int after the "and" & before the "from"
                                        break;
                                    }

                                    else if (isInKeywords(words[tmpindex])) 
                                    {
                                        break;
                                    }
                                }
                                currentindex++;
                                tmpres = 1;
                                break;
                            }
                        }

                        // if we have only "from"
                        else if (strcmp(words[currentindex], "from") == 0)
                        {

                            if (tmpvalid == 0)
                            {
                                validity = 0; // the one we stored from before 
                                break;
                            }
                            currentindex++;
                            if (isIntheList(itemlist, words[currentindex], itemcnt) || isInKeywords(words[currentindex]) || containsNumber(words[currentindex]) || isIntheList(locationlist, words[currentindex], locationcnt))
                            {
                                validity = 0; // If incompatible word
                            }
                            else
                            {
                                currentindex++;
                                if (currentindex < ifIndexValidity) // we still before if
                                {
                                    if (strcmp(words[currentindex], "and") == 0)
                                    {
                                        i = currentindex;
                                        currentindex++;
                                        tmpres = 1;
                                        break;
                                    }
                                    else
                                    {
                                        validity = 0;
                                    }
                                }
                                else
                                {
                                    i = currentindex;
                                    break;
                                }
                            }
                        }
                    }
                }

                /// SELL
                else if (strcmp(words[i], "sell") == 0)
                {
                    /// !!!! EXACT PROCESS OF BUY !!!! 
                    currentindex = i + 1;
                    int numberseen = 0;
                    int tmpvalid = 1;
                    while (1)
                    {
                        if (!isFullNumber(words[currentindex]))
                        {
                            if (numberseen == 0)
                            {
                                validity = 0; // if no int just after "sel"
                                break;
                            }
                            else
                            {
                                tmpvalid = 0;
                            }
                        }
                        else
                        {
                            numberseen = 1; // we saw the first int
                        }

                        currentindex++;
                        if (isIntheList(locationlist, words[currentindex], locationcnt) || isInKeywords(words[currentindex]) || containsNumber(words[currentindex]) || findPerson(words[currentindex]) != -1)
                        {
                            validity = 0; // incompatible word choice in Object part
                            break;
                        }
                        currentindex++;

                        // If we are at "if"
                        if (currentindex == ifIndexValidity)
                        {
                            break;
                        }

                        // we are at "and"
                        else if (strcmp(words[currentindex], "and") == 0)
                        {
                            if (isFullNumber(words[currentindex + 1])) // if next is int
                            {
                                currentindex++;
                                continue;
                            }
                            else
                            {
                                int tmpindex = currentindex;

                                // Loop to see if we have "and, to" 
                                while (1)
                                {

                                    if (tmpindex >= ifIndexValidity)
                                    {
                                        break;
                                    }
                                    if (strcmp(words[tmpindex], "and") == 0) // "and" after "sell"
                                    {
                                        if (isFullNumber(words[tmpindex + 1]))
                                        {
                                            tmpindex++;
                                        }
                                        tmpindex += 2;
                                    }

                                    else if (strcmp(words[tmpindex], "to") == 0)
                                    {
                                        validity = 0; // If we have "from" after "sell" but no int after the "and" & before the "sell"
                                        break;
                                    }
                                    else if (isInKeywords(words[tmpindex]))
                                    {
                                        break;
                                    }
                                }
                                currentindex++;
                                tmpres = 1;
                                break;
                            }
                        }

                        // wea are at "to"
                        else if (strcmp(words[currentindex], "to") == 0)
                        {

                            if (tmpvalid == 0)
                            {

                                validity = 0;
                                break;
                            }
                            currentindex++;
                            if (isIntheList(itemlist, words[currentindex], itemcnt) || isInKeywords(words[currentindex]) || containsNumber(words[currentindex]) || isIntheList(locationlist, words[currentindex], locationcnt))
                            {
                                validity = 0; // invalid choice of subject
                            }
                            else
                            {
                                currentindex++;
                                if (currentindex < ifIndexValidity)
                                {
                                    // Assume it jumps to the next sentence, because there can't be two receivers,
                                    // Checking it at the next sentence's loop
                                    if (strcmp(words[currentindex], "and") == 0)
                                    {
                                        i = currentindex;
                                        currentindex++;
                                        tmpres = 1;
                                        break;
                                    }
                                    else
                                    {
                                        validity = 0;
                                    }
                                }
                                else
                                {
                                    i = currentindex;
                                    break;
                                }
                            }
                        }
                    }
                }

                // we are at "go to"
                else if (strcmp(words[i], "go") == 0)
                {
                    if (strcmp(words[i + 1], "to") == 0)
                    {
                        currentindex = i + 2; // start of location part
                        if (isIntheList(itemlist, words[currentindex], itemcnt) || isInKeywords(words[currentindex]) || containsNumber(words[currentindex]) || findPerson(words[currentindex]) != -1)
                        {
                            validity = 0; // problematic location (item, keyword, number, subject)
                        }
                        else
                        {
                            // Next one after to is automatically location if in correct format
                            currentindex++;
                            if (currentindex < ifIndexValidity)
                            {
                                // If we dont have and after it for the next sentence, INVALID
                                if (strcmp(words[currentindex], "and") != 0)
                                {
                                    validity = 0;
                                }
                                // Continue next sentence
                                else
                                {
                                    i = currentindex;
                                    currentindex++;
                                    tmpres = 1;
                                    continue;
                                }
                            }
                        }
                    }
                    // no "to"
                    else
                    {
                        validity = 0;
                    }
                }
            }
        }
        // IF INVALID NO OPERATION DONE !!!!!!!!!!!!!!!
        if (validity == 0)
        {
            printf("INVALID\n");
            continue;
        }
        ////// END VALIDITY PART //////


    
        ///// QUESTION PART /////

        int isQuestion = 0;

        //only condition = last item "?"
        if (strcmp(words[word_count - 1], "?") == 0)
        {
            isQuestion = 1;

            ///// total item part
            if (strcmp(words[word_count - 3], "total") == 0)
            {
                int result = 0;
                int tmpcount = 0;
                char tmpnames[100][100];
                char tmpitem[100];
                strcpy(tmpitem, words[word_count - 2]);
                strcpy(itemlist[itemcnt], tmpitem);
                itemcnt++;

                // get subjects between "and"'s
                for (int i = 0; i < word_count; i++)
                {
                    if (strcmp(words[i], "and") != 0)
                    {
                        strcpy(tmpnames[tmpcount], words[i]);
                        tmpcount++;
                        if (strcmp(words[i + 1], "and") != 0) // if no "and" left
                        {
                            break;
                        }
                    }
                }

                // calculate the total of the subject's given
                for (int i = 0; i < tmpcount; i++)
                {
                    int personid = findPerson(tmpnames[i]);
                    int itemid = findPersonsItem(personid, tmpitem);
                    if (itemid != -1)
                    {
                        result += people[personid].inventory[itemid].quantity;
                    }
                }
                printf("%d\n", result);
            }

            ////// where part
            if (strcmp(words[word_count - 2], "where") == 0)
            {
                int personid = findPerson(words[0]);

                printf("%s\n", people[personid].location);
            }

            ///// who at part
            if (strcmp(words[0], "who") == 0 && strcmp(words[1], "at") == 0)
            {
                int tmpflag = 0;
                int resflag = 0;
                char tmploc[100];
                strcpy(tmploc, words[2]);
                strcpy(locationlist[locationcnt], tmploc);
                locationcnt++;

                // Loop all people 
                for (int i = 0; i < people_count; i++)
                {

                    // If location is same, print 
                    if (strcmp(people[i].location, tmploc) == 0)
                    {
                        resflag = 1; // someone found
                        if (tmpflag == 0)
                        {
                            printf("%s", people[i].name);
                            tmpflag = 1;
                        }
                        else
                        {
                            printf(" and %s", people[i].name);
                        }
                    }
                }

                // If no one found
                if (resflag == 0)
                {
                    printf("NOBODY\n");
                }
                else
                {
                    printf("\n");
                }
            }

            ///// total part
            if (strcmp(words[word_count - 2], "total") == 0)
            {
                int personid = findPerson(words[0]);
                int tmpflag = 0;
                int flagfornothing = 1;

                // loop all items of a person
                for (int i = 0; i < people[personid].inventoryCount; i++)
                {
                    // If an item has value > 0  -> print
                    if (people[personid].inventory[i].quantity != 0)
                    {
                        flagfornothing = 0;
                        if (tmpflag == 0)
                        {
                            printf("%d %s", people[personid].inventory[i].quantity, people[personid].inventory[i].name);
                            tmpflag = 1; // formatting output reasons
                        }
                        else
                        {
                            printf(" and %d %s", people[personid].inventory[i].quantity, people[personid].inventory[i].name);
                        }
                    }
                }
                // if no item
                if (flagfornothing)
                {
                    printf("NOTHING\n");
                }
                else
                {
                    printf("\n");
                }
            }
            continue;
        }
        /////END OF QUESTION PART/////


        
        ///// CONDITION PART /////

        int isCondTrue = 1;
        int beforeCondTrue = 1;

        // find the location of "if"
        int ifIndex = -1;

        int conditionStartIndex = 0;

        ifIndex = ifFinder(words, word_count, 0);
        if (ifIndex > -1)
        {
            ifFound = 1;
        }

        // "if" found, condition starts just after it
        if (ifFound)
        {
            conditionStartIndex = ifIndex + 1;
        }

        // Validity of the if part
        int dumendenValidity = 1;

        while (ifFound)
        {

            isCondTrue = beforeCondTrue;

            /// FIND COND. TYPE
            int conditionIndex = -1;
            int hasIndex = -1;
            int atIndex = -1;
            int conditionType = -1; // 0: at  --  1: has

            hasIndex = hasFinder(words, word_count, conditionStartIndex); // find "has" location
            atIndex = atFinder(words, word_count, conditionStartIndex);   // find "at" location

            
            if (hasIndex == -1) // no has
            {
                if (atIndex > -1) // yes at
                {
                    conditionType = 0;
                    conditionIndex = atIndex;
                }
                // no has & no at --> nothing
            }
            
            else if (atIndex == -1) // yes has & no at
            {
                conditionType = 1;
                conditionIndex = hasIndex;
            }
            
            else // yes has yes at
            {
                // HAS before AT
                if (hasIndex < atIndex) 
                {
                    conditionType = 1;
                    conditionIndex = hasIndex;
                }

                // AT before HAS
                else
                {
                    conditionType = 0;
                    conditionIndex = atIndex;
                }
            }
            ///


            // find SUBJECTS

            char subjects[100][100];
            int subjectsIndexes[100];
            int subjectIndexCounter = 0;

            // check between IF and CONDITION
            for (int i = conditionStartIndex; i < conditionIndex; i++)
            {
                if (strcmp(words[i], "and") != 0)
                {
                    strcpy(subjects[subjectIndexCounter], words[i]);
                    subjectsIndexes[subjectIndexCounter] = findPerson(words[i]);
                    subjectIndexCounter++;
                }
            }

            char dumendentemp[100];
            // Reset the subject list if left from before
            for (int i = subjectIndexCounter; i < word_count; i++)
            {
                strcpy(subjects[i], "");
            }

            // Check if one of the subjects has invalid format
            for (int i = 0; i < subjectIndexCounter; i++)
            {
                strcpy(dumendentemp, subjects[i]);
                if (isIntheList(locationlist, dumendentemp, locationcnt) || isIntheList(itemlist, dumendentemp, itemcnt) || isInKeywords(dumendentemp) || containsNumber(dumendentemp))
                {
                    dumendenValidity = 0;
                    break;
                }
            }

            // AT
            if (conditionType == 0)
            {
                char tempLocation[100];
                int tempSubjectIndex;
                // Get all the subjects to check
                for (int i = 0; i < subjectIndexCounter; i++)
                {
                    strcpy(tempLocation, words[atIndex + 1]);
                    strcpy(locationlist[locationcnt], tempLocation);
                    locationcnt++;
                    tempSubjectIndex = subjectsIndexes[i];
                    if (strcmp(tempLocation, people[tempSubjectIndex].location) != 0)
                    {
                        isCondTrue = 0;
                    }
                    // If on subject has invalid format
                    if (findPerson(tempLocation) != -1 || isIntheList(itemlist, dumendentemp, itemcnt) || isInKeywords(dumendentemp) || containsNumber(dumendentemp))
                    {
                        dumendenValidity = 0;
                    }
                }

                // If and 2 after the "at" next sentence starts
                if (strcmp(words[atIndex + 2], "and") == 0)
                {
                    beforeCondTrue = isCondTrue;
                    conditionStartIndex = atIndex + 3;
                    continue;
                }
            }

            // HAS
            else
            {
                // Starting of objects just after has
                int objcetStartIndex = hasIndex + 1;
                int objectEndIndex = 0;
                int objectsCounter = 0;
                int hasType = 0; // -1 less than || 0 has || 1 more than
                int quantityList[100];
                char objectList[100][100];

                // IF "less than" or "more than", add +2 to starting of the objects
                // Check the type 
                if (strcmp(words[conditionIndex + 1], "less") == 0 && strcmp(words[conditionIndex + 2], "than") == 0)
                {
                    hasType = -1;
                    objcetStartIndex++;
                    objcetStartIndex++;
                }
                else if (strcmp(words[conditionIndex + 1], "more") == 0 && strcmp(words[conditionIndex + 2], "than") == 0)
                {
                    hasType = 1;
                    objcetStartIndex++;
                    objcetStartIndex++;
                }

                // Find end index
                for (int i = objcetStartIndex; i < word_count; i++)
                {
                    // If no int just after "has" invalid in all cases
                    if (atoi(words[objcetStartIndex]) == 0)
                    {
                        validity = 0;
                        printf("INVALID\n");
                    }
                    
                    // jump 2
                    if (atoi(words[i]) != 0)
                    {
                        i++;
                        i++;
                        objectEndIndex = i;
                    }
                    else
                    {
                        objectEndIndex = i - 1;
                        break;
                    }
                }

                // Create quantity and object list
                for (int i = objcetStartIndex; i < objectEndIndex; i++)
                {
                    if (atoi(words[i]) != 0)
                    {
                        quantityList[objectsCounter] = atoi(words[i]);
                        strcpy(objectList[objectsCounter], words[i + 1]);
                        strcpy(itemlist[itemcnt], words[i + 1]);
                        itemcnt++;
                    }
                    i++;
                    i++;
                    objectsCounter++;
                }

                // Check all objects for incompatible format
                for (int i = 0; i < objectsCounter; i++)
                {
                    strcpy(dumendentemp, objectList[i]);
                    if (isIntheList(locationlist, dumendentemp, locationcnt) || findPerson(dumendentemp) != -1 || isInKeywords(dumendentemp) || containsNumber(dumendentemp))
                    {
                        dumendenValidity = 0;
                        break;
                    }
                }

                int tempSubjectID = -1;
                int subjectsQuantity = 0;
                int subjectsInventoryIndex = 0;
                int tempItemId = -1;

                int tempObjectQuantity = 0;
                char tempObject[100];

                int comparison;

                int fullBreak = 0;

                // For loop for all subjects
                for (int i = 0; i < subjectIndexCounter; i++)
                {
                    if (fullBreak)
                    {
                        break;
                    }

                    tempSubjectID = subjectsIndexes[i];
                    for (int j = 0; j < objectsCounter; j++)
                    {
                        // get the object and the quantity for each subject
                        strcpy(tempObject, objectList[j]);
                        tempItemId = findPersonsItem(subjectsIndexes[i], tempObject);
                        if (tempItemId == -1)
                        {
                            subjectsQuantity = 0;
                        }
                        else
                        {
                            subjectsQuantity = people[tempSubjectID].inventory[tempItemId].quantity;
                        }
                        comparison = comparator(subjectsQuantity, quantityList[j]);

                        // Compare according to the types of the has
                        if (hasType == -1)
                        {
                            if (comparison != -1)
                            {

                                beforeCondTrue = 0;
                                fullBreak = 1;
                                break;
                            }
                        }
                        else if (hasType == 0)
                        {
                            if (comparison != 0)
                            {
                                beforeCondTrue = 0;
                                fullBreak = 1;
                                break;
                            }
                        }
                        else
                        {
                            if (comparison != 1)
                            {

                                beforeCondTrue = 0;
                                fullBreak = 1;
                                break;
                            }
                        }
                    }
                }
            }

            if (beforeCondTrue == 0)
            {
                isCondTrue = 0;
            }
            else
            {
                isCondTrue = isCondTrue;
            }
            break;
        }

        
        ///// END OF CONDITION /////

        /// SENTENCE PART

        int currentWordIndex = 0;
        if (dumendenValidity == 0)
        {
            printf("INVALID\n");
            continue;
        }

        // If we can come from "if" and "valid sentences"
        while (isCondTrue && dumendenValidity)
        {
            if (ifIndex == -1)
            {
                if (currentWordIndex >= word_count)
                {
                    break;
                }
            }
            else
            {
                if (currentWordIndex >= ifIndex)
                {
                    break;
                }
            }

            int restartLoop = 0;


            /////// SENTENCES PART ///////
            /// detecting subjects///
            char peopleForAction[100][100];
            int peopleForActionCount = 0;

            // get the subjects
            for (int i = currentWordIndex; i < word_count; i++)
            {
                if (strcmp(words[i], "and") != 0)
                {
                    // adding newly added people to the people
                    if (findPerson(words[i]) == -1)
                    {
                        strcpy(people[people_count].name, words[i]);
                        strcpy(people[people_count].location, "NOWHERE");
                        people_count++;
                    }

                    strcpy(peopleForAction[peopleForActionCount], words[i]);
                    peopleForActionCount++;
                    if (strcmp(words[i + 1], "and") != 0)
                    {
                        currentWordIndex = i + 1;
                        break;
                    }
                }
            }

            /// BUY
            if (strcmp(words[currentWordIndex], "buy") == 0)
            {
                int cancelTrade = 0;
                char itemsToBuy[100][100];
                int quantitiesToBuy[100];
                int itemCount = 0;
                currentWordIndex++;
                // check itemts to buy
                for (int i = currentWordIndex; i < word_count; i++)
                {
                    if (strcmp(words[i], "and") != 0)
                    {
                        if (atoi(words[i]) == 0) // if not int
                        {
                            currentWordIndex = i;
                            restartLoop = 1;
                            break;
                        }
                        quantitiesToBuy[itemCount] = atoi(words[i]);
                        i++;
                        strcpy(itemsToBuy[itemCount], words[i]); // add items to buy desired ones
                        itemCount++;
                        if (i == word_count - 1 || strcmp(words[i + 1], "and") != 0) // if not at end or no "and"
                        {
                            currentWordIndex = i + 1;
                            break;
                        }
                    }
                }

                // Do the buying operation while adding items to the list
                for (int i = 0; i < peopleForActionCount; i++)
                {
                    for (int j = 0; j < itemCount; j++)
                    {
                        strcpy(itemlist[itemcnt], itemsToBuy[j]);
                        itemcnt++;
                        buy(peopleForAction[i], itemsToBuy[j], quantitiesToBuy[j]);
                    }
                }
                if (restartLoop)
                {
                    continue;
                }

                /// From part
                if (strcmp(words[currentWordIndex], "from") == 0)
                {
                    currentWordIndex++;
                    char tmpseller[100];
                    strcpy(tmpseller, words[currentWordIndex]);
                    // if no seller found
                    if (findPerson(tmpseller) == -1)
                    {
                        strcpy(people[people_count].name, tmpseller);
                        strcpy(people[people_count].location, "NOWHERE"); // add people with loc
                        people_count++;
                    }
                    int flagForError = 0;

                    for (int i = 0; i < peopleForActionCount; i++)
                    {
                        // if buyer seller same
                        if (strcmp(peopleForAction[i], words[currentWordIndex]) == 0)
                        {
                            flagForError = 1; // if buyer seller same
                            break;
                        }
                    }
                    if (strcmp(words[currentWordIndex + 1], "and") == 0)
                    {
                        //////Multiple buyers
                        currentWordIndex += 2;
                        restartLoop = 1;
                    }
                    if (flagForError == 1)
                    {
                        validity = 0;
                        printf("INVALID\n");
                        ///////Subject serving as both the seller and the buyer
                    }
                    else
                    {
                        // count all items and do selling from the seller
                        for (int j = 0; j < itemCount; j++)
                        {
                            sell(tmpseller, itemsToBuy[j], quantitiesToBuy[j] * peopleForActionCount);
                        }
                        for (int j = 0; j < people[findPerson(tmpseller)].inventoryCount; j++)
                        {
                            if (people[findPerson(tmpseller)].inventory[j].quantity < 0) // if quantity not enough cancel trade
                            {
                                cancelTrade = 1;
                            }
                        }
                    }

                    // CANCEL TRADE -> reverse all operation
                    if (cancelTrade)
                    {   
                        //do buyin for all sells
                        for (int j = 0; j < itemCount; j++)
                        {
                            buy(tmpseller, itemsToBuy[j], quantitiesToBuy[j] * peopleForActionCount);
                        }
                        //do selling for all buys
                        for (int i = 0; i < peopleForActionCount; i++)
                        {
                            for (int j = 0; j < itemCount; j++)
                            {
                                sell(peopleForAction[i], itemsToBuy[j], quantitiesToBuy[j]);
                            }
                        }
                    }
                    // seller buyer same
                    if (flagForError == 1)
                    {
                        for (int i = 0; i < peopleForActionCount; i++)
                        {
                            for (int j = 0; j < itemCount; j++)
                            {
                                sell(peopleForAction[i], itemsToBuy[j], quantitiesToBuy[j]);
                            }
                        }
                    }
                    if (restartLoop)
                    {
                        continue;
                    }
                    currentWordIndex++;
                }
            }
            /////END OF BUY PART


            /////Sell and sell to part////
            else if (strcmp(words[currentWordIndex], "sell") == 0)
            {
                int cancelTrade = 0;
                char itemsToSell[100][100];
                int quantitiesToSell[100];
                int itemCount = 0;
                currentWordIndex++;

                // count all items to sell
                for (int i = currentWordIndex; i < word_count; i++)
                {
                    if (strcmp(words[i], "and") != 0) // if not and
                    {
                        if (atoi(words[i]) == 0)  
                        {
                            currentWordIndex = i;
                            restartLoop = 1;
                            break;
                        }
                        quantitiesToSell[itemCount] = atoi(words[i]);
                        i++;
                        strcpy(itemsToSell[itemCount], words[i]);
                        itemCount++;
                        // if we have and multiple sellers
                        if (i == word_count - 1 || strcmp(words[i + 1], "and") != 0)
                        {
                            currentWordIndex = i + 1;
                            break;
                        }
                    }
                }
                // get the number of people
                for (int i = 0; i < peopleForActionCount; i++)
                {
                    // do selling for all items
                    for (int j = 0; j < itemCount; j++)
                    {
                        strcpy(itemlist[itemcnt], itemsToSell[j]); // add items to item list 
                        itemcnt++;
                        sell(peopleForAction[i], itemsToSell[j], quantitiesToSell[j]); 
                    }
                }
                // check if sellers have enough to sells so dont go below 0
                for (int i = 0; i < peopleForActionCount; i++)
                {
                    for (int j = 0; j < people[findPerson(peopleForAction[i])].inventoryCount; j++)
                    {
                        if (people[findPerson(peopleForAction[i])].inventory[j].quantity < 0)
                        {
                            cancelTrade = 1;
                        }
                    }
                }
                // do reverse of all the operations
                if (cancelTrade)
                {
                    for (int i = 0; i < peopleForActionCount; i++)
                    {
                        for (int j = 0; j < itemCount; j++)
                        {
                            buy(peopleForAction[i], itemsToSell[j], quantitiesToSell[j]); 
                        }
                    }
                }
                if (restartLoop)
                {
                    continue;
                }
                // if we have "to"
                if (strcmp(words[currentWordIndex], "to") == 0)
                {
                    currentWordIndex++;
                    char tmpbuyer[100];
                    strcpy(tmpbuyer, words[currentWordIndex]); // get the buyer
                    if (findPerson(tmpbuyer) == -1) // no buyer for the sellers to sell
                    {
                        strcpy(people[people_count].name, tmpbuyer); // add the person
                        strcpy(people[people_count].location, "NOWHERE");
                        people_count++;
                    }
                    int flagForError = 0;
                    // for all people want to sell
                    for (int i = 0; i < peopleForActionCount; i++)
                    {
                        // buyer seller same get error code
                        if (strcmp(peopleForAction[i], words[currentWordIndex]) == 0)
                        {
                            flagForError = 1;
                            break;
                        }
                    }
                    // if we have add, restart to add the next seller to the list 
                    if (strcmp(words[currentWordIndex + 1], "and") == 0)
                    {
                        restartLoop = 1;
                        currentWordIndex += 2;
                    }
                    if (flagForError == 1)
                    {
                        validity = 0;
                        printf("INVALID\n");
                        // cancelling if anything is wrong in the trade
                        if (!cancelTrade)
                        {
                            for (int i = 0; i < peopleForActionCount; i++)
                            {
                                for (int j = 0; j < itemCount; j++)
                                {
                                    buy(peopleForAction[i], itemsToSell[j], quantitiesToSell[j]); // buy for all the sell operations (reversing)
                                }
                            }
                        }
                    }
                    // no error, do all operations
                    else
                    {
                        // do the operations
                        for (int j = 0; j < itemCount; j++)
                        {
                            buy(tmpbuyer, itemsToSell[j], quantitiesToSell[j] * peopleForActionCount);
                        }
                        if (cancelTrade)
                        {
                            for (int j = 0; j < itemCount; j++)
                            {
                                sell(tmpbuyer, itemsToSell[j], quantitiesToSell[j] * peopleForActionCount);
                            }
                        }
                    }
                    // if any need to restart, do restart
                    if (restartLoop)
                    {
                        continue;
                    }
                    currentWordIndex++;
                }
            }
            ////END OF SELL PART////


            /////GO TO PART/////
            else if (strcmp(words[currentWordIndex], "go") == 0 && strcmp(words[currentWordIndex + 1], "to") == 0)
            {
                currentWordIndex += 2;
                char whereto[100];
                for (int i = 0; i < peopleForActionCount; i++)
                {
                    // hold the previous location in case of unsuccesful operation
                    strcpy(people[findPerson(peopleForAction[i])].previusLocation, people[findPerson(peopleForAction[i])].location);
                    strcpy(people[findPerson(peopleForAction[i])].location, words[currentWordIndex]);
                    strcpy(locationlist[locationcnt], words[currentWordIndex]);
                    locationcnt++;
                }
                currentWordIndex++;
            }

            /////END OF GO TO PART//////
            //////END OF SENTENCES PART//////
        }
        // IF THE SENTENCE IS NO QUESTION AND VALID
        if (isQuestion == 0 && validity)
        {
            printf("OK\n");
        }
    }
    return 0;
}
