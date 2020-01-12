#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <gcheck.h>
#include "../src/aviary.hpp"
#include "../src/bird.hpp"
#include "../src/owl.hpp"
#include "../src/duck.hpp"

enum Type : int {
    DUCK,
    OWL,
    ERROR
};

std::string to_string(Type t) {
    switch (t) {
    case DUCK: return "Duck";
    case OWL: return "Owl";
    default: return "ERROR";
    }
}

gcheck::Random<std::string> names({"Esko", "Orly", "Alfred", "Seppo", "Albert"});
gcheck::Random types(std::vector<Type>{DUCK,OWL});

std::string TConstructDuck(const std::string& name) {
    return Duck(name).GetName();
}
std::string TConstructOwl(const std::string& name) {
    return Duck(name).GetName();
}

PREREQ_TEST(Bird, constructor, 1, 0) {
    {
        std::vector correct_not_reserved = {"Seppo","Esko","Esko","Alfred","Esko"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("Seppo"),std::string("Esko"),std::string("Esko"),std::string("Alfred"),std::string("Esko")});
        TestCase(5,correct_not_reserved,TConstructDuck,inputs_not_reserved0);
    };
    {
        std::vector correct_not_reserved = {"Albert","Esko","Orly","Seppo","Orly"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("Albert"),std::string("Esko"),std::string("Orly"),std::string("Seppo"),std::string("Orly")});
        TestCase(5,correct_not_reserved,TConstructOwl,inputs_not_reserved0);
    };
}

std::string TSpeakDuck(const std::string& name) {
    std::stringstream ss; 
    Duck(name).Speak(ss);
    return ss.str();
}
std::string TSpeakOwl(const std::string& name) {
    std::stringstream ss; 
    Owl(name).Speak(ss);
    return ss.str();
}

PREREQ_TEST(Birds, Speak, 2, 0) {
    {
        std::vector correct_not_reserved = {"Albert: QUACK\n","Seppo: QUACK\n","Orly: QUACK\n","Esko: QUACK\n","Alfred: QUACK\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("Albert"),std::string("Seppo"),std::string("Orly"),std::string("Esko"),std::string("Alfred")});
        TestCase(5,correct_not_reserved,TSpeakDuck,inputs_not_reserved0);
    };
    {
        std::vector correct_not_reserved = {"Alfred: WHUU\n","Alfred: WHUU\n","Alfred: WHUU\n","Esko: WHUU\n","Esko: WHUU\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("Alfred"),std::string("Alfred"),std::string("Alfred"),std::string("Esko"),std::string("Esko")});
        TestCase(5,correct_not_reserved,TSpeakOwl,inputs_not_reserved0);
    };
}


PREREQ_TEST(Aviary, Add_indexing_operator, 3, 0) {
    Aviary aviary;
    std::vector<Bird*> added;
    for(int i = 0; i < 10; i++) {
        Bird* b = types.Next() == DUCK ? (Bird*)new Duck(names.Next()) : (Bird*)new Owl(names.Next());
        aviary.Add(b);
        added.push_back(b);
    }
    
    ASSERT_TRUE(10 == aviary.Size());
    for(int i = 0; i < 10; i++) {
        Bird* bird_that_was_added = added[i];
        EXPECT_EQ(bird_that_was_added, aviary[i]);
    }
}

TEST_(Aviary, SpeakAll, 2) {
    Aviary a;
    a.Add(new Duck("Esko")); 
    a.Add(new Owl("Orly"));
    a.Add(new Duck("Alfred"));

    std::stringstream out;
    
    a.SpeakAll(out);
    std::string SpeakAll_out = out.str();
    
    std::string correct =
         "Esko: QUACK\n"
         "Orly: WHUU\n"
         "Alfred: QUACK\n";
    
    EXPECT_EQ(correct, SpeakAll_out);
    
    out.str("");
    a.Add(new Owl("Seppo"));
    a.Add(new Duck("Albert"));
    
    a.SpeakAll(out);
    SpeakAll_out = out.str();

    correct =
         "Esko: QUACK\n"
         "Orly: WHUU\n"
         "Alfred: QUACK\n"
         "Seppo: WHUU\n"
         "Albert: QUACK\n";
    
    EXPECT_EQ(correct, SpeakAll_out);
}

TEST_(Aviary, Fly, 2) {
    Aviary a;
    a.Add(new Duck("Esko")); 
    a.Add(new Owl("Orly"));
    a.Add(new Duck("Alfred"));

    std::stringstream out;
    
    for(size_t i = 0; i < a.Size(); i++)
        a[i]->Fly(out);

    std::string SpeakAll_out = out.str();

    std::string correct = 
        "Esko flies!\n"
        "Orly flies!\n"
        "Alfred flies!\n";
    
    EXPECT_EQ(correct, SpeakAll_out);
    
    out.str("");
    a.Add(new Owl("Seppo"));
    a.Add(new Duck("Albert"));
    
    for(size_t i = 0; i < a.Size(); i++)
        a[i]->Fly(out);

    SpeakAll_out = out.str();

    correct = 
        "Esko flies!\n"
        "Orly flies!\n"
        "Alfred flies!\n"
        "Seppo flies!\n"
        "Albert flies!\n";
    
    EXPECT_EQ(correct, SpeakAll_out);
}

namespace {
    template<class>
    struct sfinae_bool {};
    template<class T>
    struct sfinae_true : sfinae_bool<T>, std::true_type{};
    template<class T>
    struct sfinae_false : sfinae_bool<T>, std::false_type{};
}

namespace detail {
    template<class T>
    static auto is_const(int) -> sfinae_true<decltype(std::declval<const T&>().SpeakAll(std::cout))>;
    template<class T>
    static auto is_const(long) -> sfinae_false<T>;
    
    template<class T>
    static auto has_copy_constructor(int) -> sfinae_true<decltype(T(std::declval<T>()))>;
    template<class T>
    static auto has_copy_constructor(long) -> sfinae_false<T>;
    
    template<class T>
    static auto has_copy_assignment(int) -> sfinae_true<decltype(std::declval<T>() = std::declval<T>())>;
    template<class T>
    static auto has_copy_assignment(long) -> sfinae_false<T>;
} // detail

template<class T>
struct is_const : decltype(detail::is_const<T>(0)){};
template<class T>
struct has_copy_constructor_t : decltype(detail::has_copy_constructor<T>(0)){};
template<class T>
struct has_copy_assignment_t : decltype(detail::has_copy_assignment<T>(0)){};

TEST_(Aviary, copy_assignment_constructor, 2) {
    bool has_copy_constructor = has_copy_constructor_t<Aviary>();
    bool has_copy_assignment = has_copy_assignment_t<Aviary>();
    EXPECT_FALSE(has_copy_constructor) << "You might have to 'make clean' (ctrl + shift + b -> Clean test Bird)\nfor any changes to this to take effect when running locally";
    EXPECT_FALSE(has_copy_assignment) << "You might have to 'make clean' (ctrl + shift + b -> Clean test Bird)\nfor any changes to this to take effect when running locally";
}
