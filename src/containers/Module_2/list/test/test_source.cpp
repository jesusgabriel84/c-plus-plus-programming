#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/list.hpp"

gcheck::RandomSizeContainer<std::string, std::list> rnd(2, 10, std::initializer_list<std::string>
    {"", " ", "some text", "some more", "asd", "what else?", "even more text", "im out of ideas"});


std::vector<std::string> TGetLines(const std::list<std::string>& lines) {
    
    std::string input;
    
    for(auto line : lines)
        input += line + '\n';
    
    std::list<std::string> list;
    std::istringstream f(input);

    GetLines(f, list);
    
    return std::vector<std::string>(list.begin(), list.end());
}

TEST(List, GetLines) {
    {
        std::vector correct_not_reserved = {std::vector<std::string>({ "even more text"," ","asd","asd",""}),std::vector<std::string>({ "asd","some text","even more text","what else?","even more text","what else?"}),std::vector<std::string>({ "some more","some more","what else?","im out of ideas","asd"," ","im out of ideas"," ",""}),std::vector<std::string>({ "im out of ideas","asd","",""}),std::vector<std::string>({ "some more","im out of ideas","asd"," "}),std::vector<std::string>({ "","even more text","some text","im out of ideas","even more text","im out of ideas","some more","","asd"}),std::vector<std::string>({ "im out of ideas","some more","some text"," ","asd","","im out of ideas","asd"}),std::vector<std::string>({ " "," "}),std::vector<std::string>({ "im out of ideas","what else?","even more text"," "}),std::vector<std::string>({ "asd","asd","some more","what else?"})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ "even more text"," ","asd","asd",""}),std::list<std::string>({ "asd","some text","even more text","what else?","even more text","what else?"}),std::list<std::string>({ "some more","some more","what else?","im out of ideas","asd"," ","im out of ideas"," ",""}),std::list<std::string>({ "im out of ideas","asd","",""}),std::list<std::string>({ "some more","im out of ideas","asd"," "}),std::list<std::string>({ "","even more text","some text","im out of ideas","even more text","im out of ideas","some more","","asd"}),std::list<std::string>({ "im out of ideas","some more","some text"," ","asd","","im out of ideas","asd"}),std::list<std::string>({ " "," "}),std::list<std::string>({ "im out of ideas","what else?","even more text"," "}),std::list<std::string>({ "asd","asd","some more","what else?"})});
        TestCase(10,correct_not_reserved,TGetLines,inputs_not_reserved0);
    };
}


std::string TPrint(const std::list<std::string>& lines) {
    gcheck::StdoutCapturer tout;
    
    Print(lines);
    
    return tout.str();
}

TEST(List, Print) {
    {
        std::vector correct_not_reserved = {" \nwhat else?\nsome text\nsome text\n","some text\nsome more\n \n\nwhat else?\nsome more\n","\nwhat else?\nsome more\nwhat else?\nsome text\nsome text\nwhat else?\nsome text\n","what else?\nasd\neven more text\nim out of ideas\n","what else?\nsome more\nasd\n"," \nsome text\nwhat else?\neven more text\n \nsome text\nim out of ideas\n","im out of ideas\neven more text\n\nwhat else?\nsome text\nwhat else?\nsome more\neven more text\nsome text\nasd\n","even more text\nasd\nsome more\n","some text\n \nsome text\nasd\neven more text\nsome text\n \nsome more\n","asd\nsome more\nim out of ideas\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ " ","what else?","some text","some text"}),std::list<std::string>({ "some text","some more"," ","","what else?","some more"}),std::list<std::string>({ "","what else?","some more","what else?","some text","some text","what else?","some text"}),std::list<std::string>({ "what else?","asd","even more text","im out of ideas"}),std::list<std::string>({ "what else?","some more","asd"}),std::list<std::string>({ " ","some text","what else?","even more text"," ","some text","im out of ideas"}),std::list<std::string>({ "im out of ideas","even more text","","what else?","some text","what else?","some more","even more text","some text","asd"}),std::list<std::string>({ "even more text","asd","some more"}),std::list<std::string>({ "some text"," ","some text","asd","even more text","some text"," ","some more"}),std::list<std::string>({ "asd","some more","im out of ideas"})});
        TestCase(10,correct_not_reserved,TPrint,inputs_not_reserved0);
    };
}


std::vector<std::string> TSortAndUnique(std::list<std::string> lines) {
    SortAndUnique(lines);
    
    return std::vector<std::string>(lines.begin(), lines.end());
}

TEST(List, SortAndUnique) {
    {
        std::vector correct_not_reserved = {std::vector<std::string>({ " ","asd","even more text","im out of ideas"}),std::vector<std::string>({ ""," ","asd","some more","some text","what else?"}),std::vector<std::string>({ "","asd","even more text","im out of ideas","some more","some text","what else?"}),std::vector<std::string>({ "some text"}),std::vector<std::string>({ "asd","even more text","what else?"}),std::vector<std::string>({ ""," ","asd","im out of ideas","some more","some text","what else?"}),std::vector<std::string>({ "","asd","im out of ideas","some text","what else?"}),std::vector<std::string>({ ""," ","asd","im out of ideas","some more","some text","what else?"}),std::vector<std::string>({ "","im out of ideas","what else?"}),std::vector<std::string>({ "","asd","even more text","some more","some text"})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list<std::string>({ "im out of ideas","asd","im out of ideas","im out of ideas","asd"," ","even more text"}),std::list<std::string>({ "some text","what else?"," ","asd","some more","some text",""}),std::list<std::string>({ "im out of ideas","","even more text","im out of ideas","some text","some more","some text","what else?","asd"}),std::list<std::string>({ "some text","some text"}),std::list<std::string>({ "even more text","even more text","asd","what else?"}),std::list<std::string>({ "asd","what else?","im out of ideas","some text"," ","some more","some more",""}),std::list<std::string>({ "im out of ideas","asd","asd","some text","","some text","what else?","asd","what else?",""}),std::list<std::string>({ " ","im out of ideas","some text","asd"," ","some more","","what else?"}),std::list<std::string>({ "what else?","im out of ideas","what else?","im out of ideas",""}),std::list<std::string>({ "even more text","asd","some text","some more","some more","some more","even more text","","asd"})});
        TestCase(10,correct_not_reserved,TSortAndUnique,inputs_not_reserved0);
    };
}
