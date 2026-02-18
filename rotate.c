#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char oneCharSide(char input)
{
    switch (input)
    {
    case '~':
    case '*':
    case '-':
        return '-'; // In the middle
    case '"':
    case '\'':
    case '^':
    case '`':
        return '`'; // Top
    case '_':
    case ',':
    case '.':
        return '_'; // Bottom
    case ':':
    case ';':
        return ':'; // Colon
    default:
        return '|';
    }
    return '|';
}

char oneCharAbove(char input)
{
    switch (input)
    {
    case ' ': // Whitespace
        return ' ';
    case '!':
    case '"':
    case '\'':
    case '(':
    case ')':
    case ',':
    case '.':
    case ':':
    case ';':
    case '[':
    case ']':
    case '`':
    case 'i':
    case 'I':
    case 'l':
    case '|':
        return '*'; // Thin letters
    default:
        return '-'; // All others are long
    }
}

char *backwards(char *input)
{
    char *temp;
    int slen = strlen(input);
    temp = malloc(slen + 1);
    temp[slen] = '\0';
    for (int i = 0; i < slen; i++)
        temp[i] = input[slen - i - 1];
    return temp;
}

typedef struct
{
    char cha;
    char *stri;
} result;

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        result Result;
        char isOneChar;
        char *operation;
        switch (argv[1][0])
        {
        case '1': // Top + Bottom
        case '2':
            Result.stri = malloc(strlen(argv[2]) + 1);
            Result.stri[strlen(argv[2])] = '\0';
            for (int i = 0; i < strlen(argv[2]); i++)
                Result.stri[i] = oneCharAbove((char)argv[2][i]);
            isOneChar = 0;
            operation = malloc(6);
            if (argv[1][0] == '1')
                strcpy(operation, "above");
            else
                strcpy(operation, "below");
            break;
        case '3': // Left
            Result.cha = oneCharSide(argv[2][0]);
            isOneChar = 1;
            operation = malloc(10);
            strcpy(operation, "left side");
            break;
        case '4': // Right
            Result.cha = oneCharSide(argv[2][strlen(argv[2]) - 1]);
            isOneChar = 1;
            operation = malloc(11);
            strcpy(operation, "right side");
            break;
        case '5': // Front
            Result.stri = malloc(strlen(argv[2]) + 1);
            Result.stri[strlen(argv[2])] = '\0';
            strcpy(Result.stri, argv[2]);
            isOneChar = 0;
            operation = malloc(9);
            strcpy(operation, "forwards");
            break;
        case '6': // Back
            ;     // Fix warning
            int slen = strlen(argv[2]);
            Result.stri = malloc(slen + 1);
            Result.stri[slen] = '\0';
            for (int i = 0; i < slen; i++)
                Result.stri[i] = argv[2][slen - i - 1];
            isOneChar = 0;
            operation = malloc(7);
            strcpy(operation, "behind");
            break;
        }
        if (isOneChar)
            printf("%s🥰\n%s\n%c💀", argv[2], operation, Result.cha);
        else
        {
            printf("%s🥰\n%s\n%s💀", argv[2], operation, Result.stri);
            free(Result.stri);
        }
        free(operation);
    }
    else if (argc <= 2)
        puts("Add the arguments side (1-6) then text \"\"");
    else
        puts("Too many arguments");
}