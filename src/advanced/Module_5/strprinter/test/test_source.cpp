#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>
#include <iterator>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/printers.hpp"
#include "../src/string_printer.hpp"
#include "../src/diagonal_printer.hpp"
#include "../src/standard_printer.hpp"

const std::vector<std::string> strings_v{"test print", "second test", "testing the third", "mooore", "idk"};
gcheck::SequenceArgument<std::string> strings(strings_v);
gcheck::SequenceArgument<std::string> starting_lines({"", "first line", "mumbo jumbo"});
gcheck::SequenceArgument<std::string> ending_lines({"last line", "", ":D"});
const std::vector<std::string> names{"mumbo", "a name", "second name", "something", "John Cena"};
const std::vector<std::string> prints{"mumbo", "a name", "second name", "something", "John Cena"};

class ReversePrinter : public StringPrinter {
public:
    /* Construct a new object - test default parameter value*/
    ReversePrinter() : StringPrinter() { }
    /* Construct a new object - pass the std::ostream& to the base class */
    ReversePrinter(std::ostream &os) : StringPrinter(os) { }
    /* Copy this object */
    ReversePrinter* Clone() const {
        return new ReversePrinter(os_);
    }
    virtual StringPrinter& operator()(const std::string& str) {
        /* os is a protected member of the base class */
        std::copy(str.rbegin(), str.rend(), std::ostream_iterator<char>(os_));
        os_ << std::endl;
        return *this;
    }
private:
};
std::string TStandard(std::string str) {
    std::stringstream ss;
    StandardPrinter sp(ss);
    sp(str);
    return ss.str();
}
PREREQ_TEST(StandardPrinter, function_call_operator_and_constructor, 1, 0) {
    strings.Reset();
    {
        std::vector correct_not_reserved = {"test print\n","second test\n","testing the third\n","mooore\n","idk\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("test print"),std::string("second test"),std::string("testing the third"),std::string("mooore"),std::string("idk")});
        TestCase(strings.GetSize(),correct_not_reserved,TStandard,inputs_not_reserved0);
    };
}

std::string TDiagonal(std::string str, std::string first, std::string last) {
    std::stringstream ss;
    DiagonalPrinter sp(first, last, ss);
    sp(str);
    return ss.str();
}
std::string TDiagonal2(std::string str) {
    gcheck::StdoutCapturer tout;
    DiagonalPrinter sp;
    sp(str);
    return tout.str();
}
PREREQ_TEST(DiagonalPrinter, function_call_operator_and_constructor, 1, 0) {
    strings.Reset();
    starting_lines.Reset();
    ending_lines.Reset();
    {
        std::vector correct_not_reserved = {"t         \n e        \n  s       \n   t      \n          \n     p    \n      r   \n       i  \n        n \n         t\n","s          \n e         \n  c        \n   o       \n    n      \n     d     \n           \n       t   \n        e  \n         s \n          t\n","t                \n e               \n  s              \n   t             \n    i            \n     n           \n      g          \n                 \n        t        \n         h       \n          e      \n                 \n            t    \n             h   \n              i  \n               r \n                d\n","m     \n o    \n  o   \n   o  \n    r \n     e\n","i  \n d \n  k\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("test print"),std::string("second test"),std::string("testing the third"),std::string("mooore"),std::string("idk")});
        TestCase(strings.GetSize(),correct_not_reserved,TDiagonal2,inputs_not_reserved0);
    };
    strings.Reset();
    {
        std::vector correct_not_reserved = {"t         \n e        \n  s       \n   t      \n          \n     p    \n      r   \n       i  \n        n \n         t\nlast line\n","first line\ns          \n e         \n  c        \n   o       \n    n      \n     d     \n           \n       t   \n        e  \n         s \n          t\n","mumbo jumbo\nt                \n e               \n  s              \n   t             \n    i            \n     n           \n      g          \n                 \n        t        \n         h       \n          e      \n                 \n            t    \n             h   \n              i  \n               r \n                d\n:D\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("test print"),std::string("second test"),std::string("testing the third")});
        gcheck::SequenceArgument inputs_not_reserved1({std::string(""),std::string("first line"),std::string("mumbo jumbo")});
        gcheck::SequenceArgument inputs_not_reserved2({std::string("last line"),std::string(""),std::string(":D")});
        TestCase(starting_lines.GetSize(),correct_not_reserved,TDiagonal,inputs_not_reserved0,inputs_not_reserved1,inputs_not_reserved2);
    };
}

PREREQ_TEST(StringPrinter, test_members, 1, 0) {
    std::ostringstream oss;
    StringPrinter* p = new ReversePrinter;
    StringPrinter* p2 = new ReversePrinter(oss);
    
    gcheck::StdoutCapturer tout;
    
    (*p)("Testing the two printers");

    std::string function_call_operator_out = tout.str();
    
    (*p2)("Seems to work");
    
    std::string correct = "sretnirp owt eht gnitseT\n";
    EXPECT_EQ(correct, function_call_operator_out) << "default stream";
    correct = "krow ot smeeS\n";
    function_call_operator_out = oss.str();
    EXPECT_EQ(correct, function_call_operator_out) << "given a stream";
    
    delete p;
    delete p2;
}


std::string TAddIndexing(std::vector<std::string> names, std::vector<std::string> print) {
    Printers printers;
    std::stringstream ss;
    StringPrinter* p = new StandardPrinter(ss);
    StringPrinter* p2 = new ReversePrinter(ss);
    StringPrinter* p3 = new DiagonalPrinter("", "", ss);
    StringPrinter* p4 = new ReversePrinter(ss);
    printers.Add(names[1], p2);
    printers.Add(names[0], p);
    printers.Add(names[3], p4);
    printers.Add(names[2], p3);
    
    try {
        for(size_t i = 0; i < 4; ++i)
            printers[names[i]](print[i]);
            
    } catch(std::invalid_argument e) {
        return "Indexing operator threw an exception when it shouldn't have.";
    }
    return ss.str();
}

PREREQ_TEST(Printers, Add_and_indexing, 1, 1) {
    {
        std::vector correct_not_reserved = {"mumbo\neman a\ns          \n e         \n  c        \n   o       \n    n      \n     d     \n           \n       n   \n        a  \n         m \n          e\ngnihtemos\n","mumbo\neman a\ns          \n e         \n  c        \n   o       \n    n      \n     d     \n           \n       n   \n        a  \n         m \n          e\ngnihtemos\n","mumbo\neman a\ns          \n e         \n  c        \n   o       \n    n      \n     d     \n           \n       n   \n        a  \n         m \n          e\ngnihtemos\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")}),std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")}),std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")}),std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")}),std::vector<std::string>({std::string("mumbo"),std::string("a name"),std::string("second name"),std::string("something"),std::string("John Cena")})});
        TestCase(3,correct_not_reserved,TAddIndexing,inputs_not_reserved0,inputs_not_reserved1);
    };
}

TEST(Diagonal_Standard, chaining) {
    std::ostringstream ss;
    StringPrinter* p = new StandardPrinter(ss);
    StringPrinter* p2 = new DiagonalPrinter("","", ss);
    
    (*p)("Testing the standard printer")("With some chaining")("Whoo");

    std::string standard_chain_out = ss.str();
    
    std::string correct = "Testing the standard printer\n"
        "With some chaining\n"
        "Whoo\n";
        
    EXPECT_EQ(correct, standard_chain_out);   
    
    ss.str("");
    ss.clear();
    
    (*p2)("works?")("yes");
    
    std::string diagonal_chain_out = ss.str();
    
    correct = 
            "w     \n"
            " o    \n"
            "  r   \n"
            "   k  \n"
            "    s \n"
            "     ?\n"
            "y  \n"
            " e \n"
            "  s\n";
            
    EXPECT_EQ(correct, diagonal_chain_out);
    
    delete p;
    delete p2;
}








TEST_(Printers, test_copyassign, 2) {
    std::ostringstream ss;
    auto p = new StandardPrinter(ss);
    auto p2 = new ReversePrinter(ss);
    
    Printers& ps = *(new Printers);
    ps.Add("n1", p);
    ps.Add("r2", p2);

    Printers ps2(ps);
    Printers ps3;
    ps3 = ps;
    
    delete &ps;

    ps2["n1"]("Testing a copy constructed Printers");    
    ps2["n1"]("With some chaining")("Whoo");
    
    std::string copy_constructed_out = ss.str();
    
    std::string correct = 
        "Testing a copy constructed Printers\n"
        "With some chaining\n"
        "Whoo\n";
    EXPECT_EQ(correct, copy_constructed_out);  
    
    ss.str("");
    ss.clear();
    
    ps3["r2"]("Seems to work");
    ps3["r2"]("Yes, pretty well");
 
    std::string copy_assigned_out = ss.str();
    
    correct = "krow ot smeeS\n"
        "llew ytterp ,seY\n";
    EXPECT_EQ(correct, copy_assigned_out);
}

TEST(Printers, exceptions) {
    auto p = new StandardPrinter;
    auto p2 = new DiagonalPrinter;
    
    Printers ps;
    ps.Add("n1", p);
    ps.Add("r2", p2);
    
    std::string exception_what;
    bool exception_type_is_invalid_argument = false;
    bool exception_thrown = false;
    try {
        ps.Add("n3", nullptr);
    } catch(const std::invalid_argument& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = true;
        exception_thrown = true;
    } catch(const std::exception& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = false;
        exception_thrown = true;
    }
    if(exception_thrown) {
        EXPECT_EQ(std::string("Invalid printer"), exception_what) << "exception.what()";
        EXPECT_TRUE(exception_type_is_invalid_argument) << "Add nullptr: Exception type should be invalid_argument";
    } else {
        bool Add_with_nullptr_throws = false;
        EXPECT_TRUE(Add_with_nullptr_throws) << "Add should throw with a nullptr parameter";
    }

    exception_thrown = false;
    try {
        ps["pinkey"]("Hih");    
    } catch(const std::invalid_argument& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = true;
        exception_thrown = true;
    } catch(const std::exception& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = false;
        exception_thrown = true;
    }
    if(exception_thrown) {
        EXPECT_EQ(std::string("Unknown index"), exception_what) << "exception.what()";
        EXPECT_TRUE(exception_type_is_invalid_argument) << "Indexing: Exception type should be invalid_argument";
    } else {
        bool Add_with_nullptr_throws = false;
        EXPECT_TRUE(Add_with_nullptr_throws) << "Indexing should throw when the printer doesn't exist";
    }
    
    exception_thrown = false;
    try {
        ps.Add("n1", p);
    } catch(const std::invalid_argument& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = true;
        exception_thrown = true;
    } catch(const std::exception& err) {
        exception_what = err.what();
        exception_type_is_invalid_argument = false;
        exception_thrown = true;
    }
    if(exception_thrown) {
        EXPECT_EQ(std::string("Duplicate index"), exception_what) << "exception.what()";
        EXPECT_TRUE(exception_type_is_invalid_argument) << "Add duplicate name: Exception type should be invalid_argument";
    } else {
        bool Add_with_duplicate_name_throws = false;
        EXPECT_TRUE(Add_with_duplicate_name_throws) << "Add should throw with a duplicate name";
    }
}
