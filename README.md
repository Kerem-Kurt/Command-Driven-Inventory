# Command Processing System Explanation

## Overview

The program is a text-based command processing system written in C that simulates buying and selling items, querying inventory, and tracking the location of people. It processes commands entered by the user and executes actions based on the given instructions.

## Key Points

- The program uses a structured approach to process commands and manage inventories and locations.
- The functionality is flexible, supporting multiple actions, queries, and conditional statements.
- It efficiently validates user input and provides feedback if the commands are not correctly formatted.
- The test cases demonstrate the system's ability to handle complex interactions and maintain accurate inventory records.

## Code Explanation

### Header Inclusions and Definitions

The program includes several standard headers:

- `stdio.h`: For input/output operations.
- `string.h`: For string manipulation.
- `stdlib.h`: For dynamic memory management.
- `ctype.h`: For character handling.

Macros are defined to set limits for word lengths, number of words, keywords, and keyword lengths:

- `MAX_WORD_LENGTH`: Maximum length of a word.
- `MAX_WORDS`: Maximum number of words.
- `NUM_KEYWORDS`: Number of keywords used in commands.
- `MAX_KEYWORD_LENGTH`: Maximum length of a keyword.

### Keyword Array

An array of 19 keywords is defined, such as "sell," "buy," "go," "to," "from," "and," etc. These keywords are essential for interpreting commands entered by the user.

### Data Structures

- **`Item`**: Represents an item with a `name` and `quantity`.
- **`Subject`**: Represents a person with a `name`, `location`, `previousLocation`, `inventoryCount`, and an array of `Item` structures.
- **`Location`**: Represents a location with a `name`.

### Global Variables

- `people`, `locationlist`, `itemlist`: Arrays to store people, locations, and items, respectively.
- `locationcnt`, `itemcnt`, `people_count`: Counters to track the number of locations, items, and people.

### Helper Functions

- **`containsNumber`** and **`isFullNumber`**: Check if a string contains or is entirely composed of numbers.
- **`isIntheList`**: Checks if a string is present in a given list.
- **`isInKeywords`**: Checks if a string is a keyword.
- **`ifFinder`**, **`atFinder`**, **`hasFinder`**: Find the indices of keywords like "if", "at", and "has" in the word array.
- **`comparator`**: Compares two integers.
- **`findPerson`** and **`findPersonsItem`**: Find a person or an item in a person's inventory.
- **`buy`** and **`sell`**: Execute buying and selling operations for people and items.

### Main Function

The main loop reads user input, tokenizes the input into words, and processes the commands.

- **Validity Check**: Validates the input command format and ensures that it follows the correct syntax and semantics.
- **Question Processing**: Handles queries about total items, locations, and inventory.
- **Condition Handling**: Evaluates conditional statements using "if", "at", and "has" for logical operations.
- **Sentence Execution**: Executes buy, sell, and go commands based on the parsed and validated input.

## Test Cases and Outputs

Here are examples of test cases from the "input_01.txt" with commands and their expected outputs:

### Some Test Cases from "input_01.txt"

```text
Input:
Galadriel and Elrond and Cirdan buy 100 Nenya and 100 Narya and 100 Vilya

Output:
OK
```

```text
Input:
Cirdan total ?

Output:
100 Nenya and 80 Vilya and 80 Narya
```

```text
Input:
Balrog total ?

Output:
10 Narya and 10 Vilya
```

```text
Input:
Balrog and Cirdan sell 10 Vilya to Legolas

Output:
OK
```

```text
Input:
Balrog and Cirdan sell 10 Vilya to Legolas

Output:
OK
```

```text
Input:
Balrog and Cirdan total Narya ?

Output:
90
```
