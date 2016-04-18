//By Ronny Aprilio
//using Code::Blocks 13.12 Ubuntu version

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <boost/locale.hpp>

int main()
{
    using namespace boost::locale::boundary;
boost::locale::generator gen;
std::string text="To be or not to be, that is the question.";
// Create mapping of text for token iterator using global locale.
ssegment_index map(word,text.begin(),text.end(),gen("en_US.UTF-8"));
// Print all "words" -- chunks of word boundary
for(ssegment_index::iterator it=map.begin(),e=map.end();it!=e;++it)
    std::cout <<"\""<< * it << "\", ";
std::cout << std::endl;
    return 0;
}
