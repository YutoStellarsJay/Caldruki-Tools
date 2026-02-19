#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*FILE *file = fopen("worddb", "wb+"); // Create The File
char *words[] = {"the", "of", "to", "and", "a", "in", "is", "it", "you", "that", "he", "was", "for", "on", "are", "with", "as", "I", "his", "they", "be", "at", "one", "have", "this", "from", "or", "had", "by", "not", "word", "but", "what", "some", "we", "can", "out", "other", "were", "all", "there", "when", "up", "use", "your", "how", "said", "an", "each", "she", "which", "do", "their", "time", "if", "will", "way", "about", "many", "then", "them", "write", "would", "like", "so", "these", "her", "long", "make", "thing", "see", "him", "two", "has", "look", "more", "day", "could", "go", "come", "did", "number", "sound", "no", "most", "people", "my", "over", "know", "water", "than", "call", "first", "who", "may", "down", "side", "been", "now", "find", "any", "new", "work", "part", "take", "get", "place", "made", "live", "where", "after", "back", "little", "only", "round", "man", "year", "came", "show", "every", "good", "me", "give", "our", "under", "name", "very", "through", "just", "form", "sentence", "great", "think", "say", "help", "low", "line", "differ", "turn", "cause", "much", "mean", "before", "move", "right", "boy", "old", "too", "same", "tell", "does", "set", "three", "want", "air", "well", "also", "play", "small", "end", "put", "home", "read", "hand", "port", "large", "spell", "add", "even", "land", "here", "must", "big", "high", "such", "follow", "act", "why", "ask", "men", "change", "went", "light", "kind", "off", "need", "alpaca", "diddly", "didder", "satan", "brotosynthesys", "beta", "gory", "poopoo", "bopoger", "cryan pooper", "fandruki"};
char temp = (char)197; // Word len
{
    long t = 197;
    fwrite(&t, sizeof(long), 1, file); // Size header
}
for (int i = 0; i < 197; i++) // Word Count
{
    temp = (char)strlen(words[i]);
    fwrite(&temp, 1, 1, file);                   // Write size
    fwrite(words[i], 1, strlen(words[i]), file); // Then word as seperator that works for reading
}
fclose(file);*/

int similarScore(char *value, char *data) // Similarity Score For Words
{
    long similar = 0;
    for (int i = 0; i < strlen(data); i++)
        for (int j = 0; j < strlen(data); j++)
        {
            if (value[j] == data[i])
                similar++;
        }
    return similar;
}

int main()
{
    //[8 Bytes Word Count]([1 Byte Word Size][? Bytes Word])..
    FILE *file = fopen("worddb", "rb+");
    if (ferror(file))
    {
        puts("File Needed");
        goto end;
    }
    long count;     // Words Count
    char temp;      // Word Size
    char **strings; // Words
    fread(&count, sizeof(long), 1, file);
    strings = malloc(count * sizeof(char *)); // Word amount of pointers for chars
    for (int i = 0; i < count; i++)
    {
        fread(&temp, 1, 1, file); // 1 character size seperator
        if (temp <= 0)
            goto end;
        strings[i] = malloc(temp + 1);    // Init to size of temp
        strings[i][temp] = '\0';          // Null end
        fread(strings[i], 1, temp, file); // Read into arr
    }
    while (1) // Input loop
    {
        printf("Put text: ");
        char input[31];
        input[30] = '\0';
        scanf("%30s", input);
        long mostIndex;
        long mostValue = -1;
        for (int i = 0; i < count; i++)
            if (similarScore(&input[0], strings[i]) > mostValue)
            {
                mostIndex = i;
                mostValue = similarScore(&input[0], strings[i]);
            }
        printf("%s🥰\nbackwards\n%s💀\n", input, strings[mostIndex]);
    }
end:;
    fclose(file);
}