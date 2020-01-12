#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include <gcheck.h>
#include "../src/transcript.hpp"

TEST(TranscriptRegistry, Add) {
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

    /*BEGIN SOLUTION*/
    std::string s4 = "Transcript of student_367754";
    std::string id4 = "367754";
    std::list<std::pair<std::string, size_t>> grades4;
    grades4.emplace_back("Basic Course in Mathematics S1", 1);
    grades4.emplace_back("C++ programming", 2);
    grades4.emplace_back("Basic Course in C programming", 2);
    Transcript t4;
    t4.name = s4;
    t4.student_id = id4;
    t4.grades = grades4;
    /*END SOLUTION*/

    TranscriptRegistry reg;
    
    reg.Add(t3); 
    reg.Add(t2); 
    reg.Add(t);
    /*BEGIN SOLUTION*/
    reg.Add(t4);
    /*END SOLUTION*/

    const TranscriptRegistry& reg2 = reg; // to test that the GetTranscripts is const
    auto& transcripts = reg2.GetTranscripts();
    
    EXPECT_EQ(t3.name, transcripts.begin()->name);
    EXPECT_EQ(t3.student_id, transcripts.begin()->student_id);
    EXPECT_EQ(*t3.grades.begin(), *(transcripts.begin()->grades.begin()));
    EXPECT_EQ(*(std::next(t3.grades.begin(),1)), *(std::next(transcripts.begin()->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t3.grades.begin(),2)), *(std::next(transcripts.begin()->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t3.grades.begin(),3)), *(std::next(transcripts.begin()->grades.begin(), 3)));

    EXPECT_EQ(t2.name, (++transcripts.begin())->name);
    EXPECT_EQ(t2.student_id, (++transcripts.begin())->student_id);
    EXPECT_EQ(*t2.grades.begin(), *((std::next(transcripts.begin(), 1))->grades.begin()));
    EXPECT_EQ(*(std::next(t2.grades.begin(),1)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t2.grades.begin(),2)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t2.grades.begin(),3)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 3)));

    EXPECT_EQ(t.name, (std::next(transcripts.begin(), 2))->name);
    EXPECT_EQ(t.student_id, (std::next(transcripts.begin(), 2))->student_id);
    EXPECT_EQ(*t.grades.begin(), *((std::next(transcripts.begin(), 2))->grades.begin()));
    EXPECT_EQ(*(std::next(t.grades.begin(),1)), *(std::next(std::next(transcripts.begin(),2)->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t.grades.begin(),2)), *(std::next(std::next(transcripts.begin(),2)->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t.grades.begin(),3)), *(std::next(std::next(transcripts.begin(),2)->grades.begin(), 3)));
    
    /*BEGIN SOLUTION*/
    EXPECT_EQ(t4.name, (std::next(transcripts.begin(), 3))->name);
    EXPECT_EQ(t4.student_id, (std::next(transcripts.begin(), 3))->student_id);
    EXPECT_EQ(*t4.grades.begin(), *((std::next(transcripts.begin(), 3))->grades.begin()));
    EXPECT_EQ(*(std::next(t4.grades.begin(),1)), *(std::next(std::next(transcripts.begin(),3)->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t4.grades.begin(),2)), *(std::next(std::next(transcripts.begin(),3)->grades.begin(), 2)));
    /*END SOLUTION*/
}

TEST(TranscriptRegistry, RemoveById) {
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

    /*BEGIN SOLUTION*/
    std::string s4 = "Transcript of student_367754";
    std::string id4 = "367754";
    std::list<std::pair<std::string, size_t>> grades4;
    grades4.emplace_back("Basic Course in Mathematics S1", 1);
    grades4.emplace_back("C++ programming", 2);
    grades4.emplace_back("Basic Course in C programming", 2);
    Transcript t4;
    t4.name = s4;
    t4.student_id = id4;
    t4.grades = grades4;
    /*END SOLUTION*/

    TranscriptRegistry reg;
    
    reg.Add(t); 
    reg.Add(t2); 
    reg.Add(t3);
    /*BEGIN SOLUTION*/
    reg.Add(t4);
    /*END SOLUTION*/

    reg.RemoveById(t2.student_id);
    /*BEGIN SOLUTION*/
    reg.RemoveById(t4.student_id);
    /*END SOLUTION*/

    auto& transcripts = reg.GetTranscripts();
    
    EXPECT_EQ(t.name, transcripts.begin()->name);
    EXPECT_EQ(t.student_id, transcripts.begin()->student_id);
    EXPECT_EQ(*t.grades.begin(), *(transcripts.begin()->grades.begin()));
    EXPECT_EQ(*(std::next(t.grades.begin(),1)), *(std::next(transcripts.begin()->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t.grades.begin(),2)), *(std::next(transcripts.begin()->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t.grades.begin(),3)), *(std::next(transcripts.begin()->grades.begin(), 3)));

    EXPECT_EQ(t3.name, (++transcripts.begin())->name);
    EXPECT_EQ(t3.student_id, (++transcripts.begin())->student_id);
    EXPECT_EQ(*t3.grades.begin(), *((std::next(transcripts.begin(), 1))->grades.begin()));
    EXPECT_EQ(*(std::next(t3.grades.begin(),1)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t3.grades.begin(),2)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t3.grades.begin(),3)), *(std::next(std::next(transcripts.begin(),1)->grades.begin(), 3)));
}

TEST(TranscriptRegistry, FindTranscript) {
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

    /*BEGIN SOLUTION*/
    std::string s4 = "Transcript of student_367754";
    std::string id4 = "367754";
    std::list<std::pair<std::string, size_t>> grades4;
    grades4.emplace_back("Basic Course in Mathematics S1", 1);
    grades4.emplace_back("C++ programming", 2);
    grades4.emplace_back("Basic Course in C programming", 2);
    Transcript t4;
    t4.name = s4;
    t4.student_id = id4;
    t4.grades = grades4;
    /*END SOLUTION*/

    



    TranscriptRegistry reg;
    
    reg.Add(t); 
    reg.Add(t2); 
    reg.Add(t3);
    /*BEGIN SOLUTION*/
    reg.Add(t4);
    /*END SOLUTION*/

    const TranscriptRegistry& reg2 = reg;
    auto it = reg2.FindTranscript(t.student_id);
    /*BEGIN SOLUTION*/
    auto it2 = reg2.FindTranscript(t4.student_id);
    /*END SOLUTION*/

    EXPECT_EQ(t.name, it->name);
    EXPECT_EQ(t.student_id, it->student_id);
    EXPECT_EQ(*t.grades.begin(), *(it->grades.begin()));
    EXPECT_EQ(*(std::next(t.grades.begin(),1)), *(std::next(it->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t.grades.begin(),2)), *(std::next(it->grades.begin(), 2)));
    EXPECT_EQ(*(std::next(t.grades.begin(),3)), *(std::next(it->grades.begin(), 3)));

    /*BEGIN SOLUTION*/
    EXPECT_EQ(t4.name, it2->name);
    EXPECT_EQ(t4.student_id, it2->student_id);
    EXPECT_EQ(*t4.grades.begin(), *(it2->grades.begin()));
    EXPECT_EQ(*(std::next(t4.grades.begin(),1)), *(std::next(it2->grades.begin(), 1)));
    EXPECT_EQ(*(std::next(t4.grades.begin(),2)), *(std::next(it2->grades.begin(), 2)));
    /*END SOLUTION*/
}

TEST(TranscriptRegistry, FindCourseResults) {
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

    /*BEGIN SOLUTION*/
    std::string s4 = "Transcript of student_367754";
    std::string id4 = "367754";
    std::list<std::pair<std::string, size_t>> grades4;
    grades4.emplace_back("Basic Course in Mathematics S1", 1);
    grades4.emplace_back("C++ programming", 2);
    grades4.emplace_back("Basic Course in C programming", 2);
    Transcript t4;
    t4.name = s4;
    t4.student_id = id4;
    t4.grades = grades4;
    /*END SOLUTION*/

    TranscriptRegistry reg;
    
    reg.Add(t); 
    reg.Add(t2); 
    reg.Add(t3);
    /*BEGIN SOLUTION*/
    reg.Add(t4);
    /*END SOLUTION*/

    const TranscriptRegistry& reg2 = reg;
    auto list  = reg2.FindCourseResults("C++ programming");
    /*BEGIN SOLUTION*/
    auto list2 = reg2.FindCourseResults("Basic Course in C programming");
    /*END SOLUTION*/

    EXPECT_EQ("123456", (*list.begin()).first);
    EXPECT_EQ("347657", (*std::next(list.begin(), 1)).first);
    EXPECT_EQ("092854", (*std::next(list.begin(), 2)).first);
    /*BEGIN SOLUTION*/
    EXPECT_EQ("367754", (*std::next(list2.begin(), 2)).first);
    /*END SOLUTION*/

    EXPECT_EQ(2, (*list.begin()).second);
    EXPECT_EQ(5, (*std::next(list.begin(), 1)).second);
    EXPECT_EQ(4, (*std::next(list.begin(), 2)).second);
    /*BEGIN SOLUTION*/
    EXPECT_EQ(2, (*std::next(list2.begin(), 2)).second);
    /*END SOLUTION*/

}
