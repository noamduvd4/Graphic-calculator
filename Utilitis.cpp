#include "Utilitis.h"
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <map>
#include <set>
#include <iostream>
#include <vector>
void RemoveSpacesFromBeginAndEnd(std::string & name)
{   
    const auto strBegin = name.find_first_not_of(WHITE_SPACE);
    if (strBegin != std::string::npos)
    {
        const auto strEnd = name.find_last_not_of(WHITE_SPACE);
        const auto strRange = strEnd - strBegin + 1;
        name=name.substr(strBegin, strRange);
    }
}
std::vector<std::string> SplitToArry(const std::string & data, const char split_char)
{
    std::vector<std::string> words ;
    int  pos = 0;
    std::string copy_of_data=data;
    while ((pos = copy_of_data.find(split_char)) != -1) {
        words.push_back (copy_of_data.substr(0, pos));
        copy_of_data.erase(0, pos + 1);
    }
    words.push_back(copy_of_data);
    return(words);
}