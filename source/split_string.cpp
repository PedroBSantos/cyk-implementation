#include "../include/split_string.h"

std::vector<std::string> split(const char* str, char delimiter)
{
    std::vector<std::string> strings;
    if (strlen(str) == 0)
    {
        return strings;
    }
    char* splits = new char[strlen(str)];
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < (signed int)strlen(str); i++)
    {
        if (str[i] != delimiter)
        {
            splits[count1] = str[i];
            count1++;
        }
        else
        {
            splits[count1] = '\0';
            std::string aux(splits);
            strings.push_back(aux);
            count2++;
            count1 = 0;
            splits = new char[strlen(str)];
        }
        if (i == (signed int)strlen(str) - 1)
        {
            splits[count1] = '\0';
            std::string aux(splits);
            strings.push_back(aux);
            count2++;
        }
    }
    return strings;
}
