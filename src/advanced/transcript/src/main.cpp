#include "transcript.hpp"
#include <iostream>
#include <algorithm>

int main() {
    std::string s = "Transcript of student_123456";
    std::string id = "123456";
    std::list<std::pair<std::string, size_t>> grades;
    grades.emplace_back("C++ programming", 2);
    grades.emplace_back("Basic Course in C programming", 4);
    grades.emplace_back("Computer Graphics", 5);
    grades.emplace_back("Programming 1", 3);
    Transcript t;
    t.name = s;
    t.student_id = id;
    t.grades = grades;

    std::string s2 = "Transcript of student_347657";
    std::string id2 = "347657";
    std::list<std::pair<std::string, size_t>> grades2;
    grades2.emplace_back("C++ programming", 5);
    grades2.emplace_back("Basic Course in C programming", 2);
    grades2.emplace_back("Basic Course in Mathematics S1", 3);
    grades2.emplace_back("Circuit Analysis 1", 4);
    Transcript t2;
    t2.name = s2;
    t2.student_id = id2;
    t2.grades = grades2;

    std::string s3 = "Transcript of student_092854";
    std::string id3 = "092854";
    std::list<std::pair<std::string, size_t>> grades3;
    grades3.emplace_back("Embedded Systems Development", 5);
    grades3.emplace_back("Switched-Mode Power Supplies", 3);
    grades3.emplace_back("Design of Electrical Machines", 4);
    grades3.emplace_back("Converter Techniques", 4);
    grades3.emplace_back("C++ programming", 4);
    Transcript t3;
    t3.name = s3;
    t3.student_id = id3;
    t3.grades = grades3;

    TranscriptRegistry reg;
    
    std::cout << std::endl << "**** TESTING ADD ****" << std::endl;
    reg.Add(t); 
    reg.Add(t2); 
    reg.Add(t3);

    for (auto& tr : reg.GetTranscripts() ) {
        std::cout << "Name: " << tr.name << std::endl;
        std::cout << "Student id: " << tr.student_id << std::endl;
        std::cout << "Grades:" << std::endl;
        std::for_each(tr.grades.begin(), tr.grades.end(), [](std::pair<std::string, size_t> e) { std::cout << e.first << " : " << e.second << std::endl; });
    }

    std::cout << std::endl << "**** TESTING REMOVE ****" << std::endl;
    reg.RemoveById("123456");

    for (auto& tr : reg.GetTranscripts()) {
        std::cout << "Name: " << tr.name << std::endl;
        std::cout << "Student id: " << tr.student_id << std::endl;
        std::cout << "Grades:" << std::endl;
        std::for_each(tr.grades.begin(), tr.grades.end(), [](std::pair<std::string, size_t> e) { std::cout << e.first << " : " << e.second << std::endl; });
    }

    std::cout << std::endl << "**** TESTING FIND ****" << std::endl;
    auto it = reg.FindTranscript("092854");
        std::cout << "Name: " << it->name << std::endl;
        std::cout << "Student id: " << it->student_id << std::endl;
        std::cout << "Grades:" << std::endl;
        std::for_each(it->grades.begin(), it->grades.end(), [](std::pair<std::string, size_t> e) { std::cout << e.first << " : " << e.second << std::endl; });
    auto it2 = reg.FindTranscript("123456");
    if(it2 == reg.GetTranscripts().end())
    std::cout << "Not found!" << std::endl;

    std::cout << std::endl << "**** TESTING FIND COURSE RESULTS ****" << std::endl;
    auto res = reg.FindCourseResults("C++ programming");
    for(auto& r : res) {
        std::cout << r.first << " : " << r.second << std::endl;
    }
}
