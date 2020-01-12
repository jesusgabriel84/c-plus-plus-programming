#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <tuple>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/dragon.hpp"
#include "../src/fantasy_dragon.hpp"
#include "../src/magic_dragon.hpp"
#include "../src/chinese_dragon.hpp"
#include "../src/dragon_cave.hpp"

std::string to_string(TreasureType t) {
    switch (t) {
    case Wisdom:
        return "Wisdom";
    case Potions:
        return "Potions";
    case Jewellery:
        return "Jewellery";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Treasure& t) {
    return "[" + to_string(t.type) + ", " + t.name + "]";
}
bool operator==(const Treasure& l, const Treasure& r) {
    return l.type == r.type && l.name == r.name;
}

std::string to_string(FoodType t) {
    switch (t) {
    case People:
        return "People";
    case PeopleFood:
        return "PeopleFood";
    case Herbs:
        return "Herbs";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Food& f) {
    return "[" + to_string(f.type) + ", " + f.name + "]";
}
bool operator==(const Food& l, const Food& r) {
    return l.type == r.type && l.name == r.name;
}

std::vector<Treasure> CreateRandomTreasures(size_t count) {
    std::vector<Treasure> treasures;
    
    // Jewellery
    gcheck::Random j_names({"Ruby", "Gold bar", "Agate", "Amber", "Silver coins", "Jade stone", "Bag of pearls", "Topaz", "Sapphire dust"});
    // Wisdom
    gcheck::Random w_names({"Scroll of infinite wisdom", "Sun Tzu's Art of War", "Biographia literaria", "MAOL", "Gabriel's Wing", "Critique of pure reason", "The C++ standard", "The Symposium", "Thus Spoke Zarathustra"});
    // Potions
    gcheck::Random p_names({"Cough syrup", "Liquid luck", "Stoneskin potion", "Blemish blitzer", "Elixir of euphoria", "Garroting gas", "Essence of insanity", "Gin tonic", "Truth serum"});

    gcheck::Random rnd_type(std::vector<TreasureType>({Jewellery, Wisdom, Potions}));
    std::unordered_map<TreasureType, gcheck::Random<const char*>*> names({std::pair(Jewellery, &j_names), std::pair(Wisdom, &w_names), std::pair(Potions, &p_names)});

    for(size_t i = 0; i < count; i++) {
        TreasureType type = rnd_type.Next();
        treasures.push_back({type, std::string(names[type]->Next())});
    }

    return treasures;
}

std::vector<Food> CreateRandomFood(size_t count) {
    std::vector<Food> food;

    // PeopleFood
    gcheck::Random pf_names({"Tenderloin steak", "Carnivore pizza", "Beef chuck", "Pork ribs", "Cornered beef", "Flank steak", "Pork rack", "Half of a pork's ass", "Horse (salami)"});
    // People
    gcheck::Random p_names({"Raimo", "Petteri", "Joonas", "Konsta", "Jack Sparrow", "John Smith", "Random crusader", "Barack Obama", "The Pope"});
    // Herbs
    gcheck::Random h_names({"Arrowroot", "Bay leaves", "Hawthorn", "Hypericum perforatum", "Poppy seeds", "Magic mushrooms", "Salvia divinorum", "Salvia officinalis", "Peppermint root"});

    gcheck::Random rnd_type(std::vector<FoodType>({People, PeopleFood, Herbs}));
    std::unordered_map<FoodType, gcheck::Random<const char*>*> names({std::pair(People, &p_names), std::pair(PeopleFood, &pf_names), std::pair(Herbs, &h_names)});

    for(size_t i = 0; i < count; i++) {
        FoodType type = rnd_type.Next();
        food.push_back({type, std::string(names[type]->Next())});
    }

    return food;
}

gcheck::RandomSizeContainer<Treasure, std::list> rnd_treasures(10, 30, CreateRandomTreasures(50));
gcheck::RandomSizeContainer<Food, std::list> rnd_foods(10, 30, CreateRandomFood(50));
gcheck::Random<std::string> rnd_name(std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
gcheck::Random<size_t> rnd_age(0, 10000);
gcheck::Random<size_t> rnd_size(5, 30);
gcheck::RandomContainer<std::string> rnd_names(3, std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
gcheck::RandomContainer<size_t> rnd_ages(3, (size_t)0, (size_t)10000);
gcheck::RandomContainer<size_t> rnd_sizes(3, (size_t)5, (size_t)30);


PREREQ_TEST(Dragons, constructors, 1, 0) {

    int puff_age = rnd_age.Next();
    int bahamut_age = rnd_age.Next();
    int haku_age = rnd_age.Next();
    int puff_size = rnd_size.Next();
    int bahamut_size = rnd_size.Next();
    int haku_size = rnd_size.Next();
    MagicDragon* mdragon = new MagicDragon("Puff", puff_age, puff_size);
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", bahamut_age, bahamut_size);
    ChineseDragon* cdragon = new ChineseDragon("Haku", haku_age, haku_size);

    EXPECT_EQ("Puff", mdragon->GetName());
    EXPECT_EQ(puff_age, mdragon->GetAge());
    EXPECT_EQ(puff_size, mdragon->GetSize());

    EXPECT_EQ("Bahamut", fdragon->GetName());
    EXPECT_EQ(bahamut_age, fdragon->GetAge());
    EXPECT_EQ(bahamut_size, fdragon->GetSize());

    EXPECT_EQ("Haku", cdragon->GetName());
    EXPECT_EQ(haku_age, cdragon->GetAge());
    EXPECT_EQ(haku_size, cdragon->GetSize());

    delete cdragon;
    delete fdragon;
    delete mdragon;
}

template<typename T>
std::string THoardOutput(std::list<Treasure> treasures) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Hoard(treasures);
    return tout.str();
} 
template<typename T>
std::vector<Treasure> THoardList(std::list<Treasure> treasures) {
    T("", 0, 0).Hoard(treasures);
    return std::vector<Treasure>(treasures.begin(), treasures.end());
} 
template<typename T>
std::vector<Treasure> THoardDragons(std::list<Treasure> treasures) {
    T dragon("", 0, 0);
    dragon.Hoard(treasures);
    auto& treas = dragon.GetTreasures();
    return std::vector<Treasure>(treas.begin(), treas.end());
} 

PREREQ_TEST(MagicDragon, Hoard_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Magic dragon received: Garroting gas\nMagic dragon received: Blemish blitzer\nMagic dragon received: Elixir of euphoria\nMagic dragon received: Elixir of euphoria\nMagic dragon received: Gin tonic\n","Magic dragon received: Cough syrup\nMagic dragon received: Gin tonic\nMagic dragon received: Garroting gas\nMagic dragon received: Essence of insanity\nMagic dragon received: Cough syrup\nMagic dragon received: Garroting gas\nMagic dragon received: Garroting gas\nMagic dragon received: Elixir of euphoria\n","Magic dragon received: Essence of insanity\nMagic dragon received: Truth serum\nMagic dragon received: Elixir of euphoria\nMagic dragon received: Gin tonic\nMagic dragon received: Stoneskin potion\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")}}),std::list({Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}}),std::list({Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Topaz")}})});
        TestCase(3,correct_not_reserved,THoardOutput<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Fantasy dragon received: Bag of pearls\nFantasy dragon received: Agate\nFantasy dragon received: Bag of pearls\nFantasy dragon received: Agate\nFantasy dragon received: Ruby\nFantasy dragon received: Agate\nFantasy dragon received: Sapphire dust\nFantasy dragon received: Sapphire dust\n","Fantasy dragon received: Jade stone\nFantasy dragon received: Topaz\nFantasy dragon received: Ruby\nFantasy dragon received: Bag of pearls\nFantasy dragon received: Topaz\nFantasy dragon received: Agate\nFantasy dragon received: Topaz\n","Fantasy dragon received: Topaz\nFantasy dragon received: Bag of pearls\nFantasy dragon received: Ruby\nFantasy dragon received: Sapphire dust\nFantasy dragon received: Agate\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")}}),std::list({Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Essence of insanity")}}),std::list({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Elixir of euphoria")}})});
        TestCase(3,correct_not_reserved,THoardOutput<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Hoard_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Chinese dragon received: Sun Tzu\'s Art of War\nChinese dragon received: Gabriel\'s Wing\nChinese dragon received: Sun Tzu\'s Art of War\nChinese dragon received: Thus Spoke Zarathustra\nChinese dragon received: Gabriel\'s Wing\nChinese dragon received: The C++ standard\n","Chinese dragon received: Sun Tzu\'s Art of War\nChinese dragon received: The Symposium\nChinese dragon received: Thus Spoke Zarathustra\nChinese dragon received: Gabriel\'s Wing\nChinese dragon received: MAOL\nChinese dragon received: MAOL\nChinese dragon received: Critique of pure reason\nChinese dragon received: Thus Spoke Zarathustra\nChinese dragon received: Gabriel\'s Wing\n","Chinese dragon received: Thus Spoke Zarathustra\nChinese dragon received: Gabriel\'s Wing\nChinese dragon received: Biographia literaria\nChinese dragon received: Gabriel\'s Wing\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Truth serum")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("The C++ standard")}}),std::list({Treasure{Jewellery, std::string("Silver coins")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Gabriel's Wing")}}),std::list({Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Essence of insanity")}})});
        TestCase(3,correct_not_reserved,THoardOutput<ChineseDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Hoard_treasures_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The C++ standard")}}),std::vector({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}}),std::vector({Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Blemish blitzer")}}),std::list({Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}}),std::list({Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Bag of pearls")}})});
        TestCase(3,correct_not_reserved,THoardList<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_treasures_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}}),std::vector({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")}}),std::vector({Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Truth serum")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("MAOL")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}}),std::list({Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")}}),std::list({Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Truth serum")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Garroting gas")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")}})});
        TestCase(3,correct_not_reserved,THoardList<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Hoard_treasures_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Blemish blitzer")}}),std::vector({Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Sapphire dust")}}),std::vector({Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("MAOL")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Biographia literaria")}}),std::list({Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Sapphire dust")}}),std::list({Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Sapphire dust")}})});
        TestCase(3,correct_not_reserved,THoardList<ChineseDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Hoard_dragons_treasures, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Essence of insanity")}}),std::vector({Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Cough syrup")}}),std::vector({Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Elixir of euphoria")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Essence of insanity")}}),std::list({Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Cough syrup")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")}}),std::list({Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")}})});
        TestCase(3,correct_not_reserved,THoardDragons<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Hoard_dragons_treasures, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Jewellery, std::string("Sapphire dust")}}),std::vector({Treasure{Jewellery, std::string("Silver coins")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Agate")},Treasure{Jewellery, std::string("Bag of pearls")}}),std::vector({Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("The C++ standard")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Blemish blitzer")}}),std::list({Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Topaz")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Stoneskin potion")}}),std::list({Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Truth serum")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Blemish blitzer")}})});
        TestCase(3,correct_not_reserved,THoardDragons<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Hoard_dragons_treasures, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Critique of pure reason")}}),std::vector({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")}}),std::vector({Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Truth serum")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Jewellery, std::string("Ruby")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Jewellery, std::string("Topaz")}}),std::list({Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Jade stone")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Sapphire dust")}}),std::list({Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("MAOL")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Truth serum")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Potions, std::string("Truth serum")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("Gabriel's Wing")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Stoneskin potion")}})});
        TestCase(3,correct_not_reserved,THoardDragons<ChineseDragon>,inputs_not_reserved0);
    };
}


template<typename T>
std::string TEatOutput(std::list<Food> foods) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Eat(foods);
    return tout.str();
} 
template<typename T>
std::vector<Food> TEatList(std::list<Food> foods) {
    T("", 0, 0).Eat(foods);
    return std::vector<Food>(foods.begin(), foods.end());
} 
template<typename T>
size_t TEatSize(std::list<Food> foods) {
    T dragon("", 0, 0);
    dragon.Eat(foods);
    return dragon.GetSize();
} 

PREREQ_TEST(MagicDragon, Eat_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Magic dragon ate: Arrowroot\nMagic dragon ate: Salvia officinalis\nMagic dragon ate: Salvia divinorum\n","Magic dragon ate: Magic mushrooms\nMagic dragon ate: Poppy seeds\nMagic dragon ate: Salvia divinorum\n","Magic dragon ate: Salvia divinorum\nMagic dragon ate: Poppy seeds\nMagic dragon ate: Arrowroot\nMagic dragon ate: Arrowroot\nMagic dragon ate: Salvia officinalis\nMagic dragon ate: Arrowroot\nMagic dragon ate: Poppy seeds\nMagic dragon ate: Salvia divinorum\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{People, std::string("John Smith")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia divinorum")}}),std::list({Food{People, std::string("Raimo")},Food{People, std::string("Random crusader")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Magic mushrooms")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Konsta")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("John Smith")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")}}),std::list({Food{People, std::string("The Pope")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Beef chuck")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Flank steak")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Petteri")}})});
        TestCase(3,correct_not_reserved,TEatOutput<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Fantasy dragon ate: Flank steak\nFantasy dragon ate: The Pope\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Tenderloin steak\nFantasy dragon ate: Raimo\nFantasy dragon ate: Raimo\n","Fantasy dragon ate: Horse (salami)\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Joonas\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Pork ribs\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Tenderloin steak\nFantasy dragon ate: Flank steak\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Flank steak\nFantasy dragon ate: The Pope\nFantasy dragon ate: The Pope\nFantasy dragon ate: Pork rack\nFantasy dragon ate: Pork rack\nFantasy dragon ate: John Smith\nFantasy dragon ate: Joonas\nFantasy dragon ate: Beef chuck\nFantasy dragon ate: Flank steak\n","Fantasy dragon ate: Petteri\nFantasy dragon ate: Raimo\nFantasy dragon ate: Flank steak\nFantasy dragon ate: Raimo\nFantasy dragon ate: Raimo\nFantasy dragon ate: Tenderloin steak\nFantasy dragon ate: Konsta\nFantasy dragon ate: Jack Sparrow\nFantasy dragon ate: Horse (salami)\nFantasy dragon ate: Flank steak\nFantasy dragon ate: Half of a pork\'s ass\nFantasy dragon ate: Cornered beef\nFantasy dragon ate: Tenderloin steak\nFantasy dragon ate: Petteri\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Raimo")}}),std::list({Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Flank steak")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Flank steak")}}),std::list({Food{People, std::string("Petteri")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Flank steak")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Raimo")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Konsta")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Cornered beef")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Arrowroot")}})});
        TestCase(3,correct_not_reserved,TEatOutput<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Eat_printed_output, 1, 1) {
    {
        std::vector correct_not_reserved = {"Chinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Arrowroot\nChinese dragon ate: Cornered beef\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Bay leaves\n","Chinese dragon ate: Arrowroot\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Magic mushrooms\nChinese dragon ate: Carnivore pizza\nChinese dragon ate: Pork rack\nChinese dragon ate: Horse (salami)\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Horse (salami)\nChinese dragon ate: Arrowroot\nChinese dragon ate: Arrowroot\nChinese dragon ate: Arrowroot\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Arrowroot\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Flank steak\nChinese dragon ate: Half of a pork\'s ass\n","Chinese dragon ate: Salvia divinorum\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Pork rack\nChinese dragon ate: Salvia divinorum\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Arrowroot\nChinese dragon ate: Half of a pork\'s ass\nChinese dragon ate: Poppy seeds\nChinese dragon ate: Horse (salami)\nChinese dragon ate: Cornered beef\nChinese dragon ate: Arrowroot\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("John Smith")},Food{People, std::string("The Pope")},Food{People, std::string("Petteri")},Food{People, std::string("The Pope")},Food{People, std::string("Random crusader")}}),std::list({Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Magic mushrooms")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Half of a pork's ass")}}),std::list({Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Petteri")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Arrowroot")}})});
        TestCase(3,correct_not_reserved,TEatOutput<ChineseDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Eat_foods_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Joonas")},Food{People, std::string("Random crusader")},Food{People, std::string("John Smith")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")}}),std::vector({Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Half of a pork's ass")}}),std::vector({Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("The Pope")},Food{People, std::string("Joonas")},Food{People, std::string("Konsta")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{People, std::string("Joonas")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Flank steak")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Joonas")},Food{People, std::string("Random crusader")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")}}),std::list({Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Magic mushrooms")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")}}),std::list({Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Magic mushrooms")},Food{People, std::string("Joonas")},Food{People, std::string("Konsta")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Arrowroot")}})});
        TestCase(3,correct_not_reserved,TEatList<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_foods_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")}}),std::vector({Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia divinorum")}}),std::vector({Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Poppy seeds")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Carnivore pizza")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Jack Sparrow")}}),std::list({Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Beef chuck")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Joonas")},Food{People, std::string("Konsta")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")}}),std::list({Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Joonas")},Food{People, std::string("Random crusader")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Poppy seeds")}})});
        TestCase(3,correct_not_reserved,TEatList<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Eat_foods_left_in_list, 1, 1) {
    {
        std::vector correct_not_reserved = {std::vector({Food{People, std::string("Joonas")},Food{People, std::string("The Pope")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Konsta")},Food{People, std::string("Random crusader")},Food{People, std::string("Raimo")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")}}),std::vector({Food{People, std::string("Raimo")},Food{People, std::string("Petteri")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{People, std::string("Random crusader")},Food{People, std::string("Joonas")}}),std::vector({Food{People, std::string("John Smith")},Food{People, std::string("Joonas")},Food{People, std::string("Raimo")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")}})};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Konsta")},Food{People, std::string("Random crusader")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Flank steak")}}),std::list({Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Joonas")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Beef chuck")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Horse (salami)")}}),std::list({Food{People, std::string("John Smith")},Food{Herbs, std::string("Magic mushrooms")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Raimo")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia divinorum")}})});
        TestCase(3,correct_not_reserved,TEatList<ChineseDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(MagicDragon, Eat_dragon_size, 1, 1) {
    {
        std::vector correct_not_reserved = {(size_t)4,(size_t)2,(size_t)7};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("John Smith")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("John Smith")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Petteri")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Magic mushrooms")},Food{People, std::string("The Pope")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Petteri")}}),std::list({Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Carnivore pizza")},Food{PeopleFood, std::string("Flank steak")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Horse (salami)")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Flank steak")}}),std::list({Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Magic mushrooms")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Konsta")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Joonas")},Food{People, std::string("Raimo")},Food{People, std::string("Joonas")},Food{People, std::string("John Smith")},Food{People, std::string("The Pope")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Raimo")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{People, std::string("Konsta")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Bay leaves")}})});
        TestCase(3,correct_not_reserved,TEatSize<MagicDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(FantasyDragon, Eat_dragon_size, 1, 1) {
    {
        std::vector correct_not_reserved = {(size_t)20,(size_t)20,(size_t)11};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("The Pope")},Food{People, std::string("Raimo")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Magic mushrooms")},Food{People, std::string("John Smith")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Random crusader")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("Joonas")},Food{People, std::string("John Smith")},Food{Herbs, std::string("Arrowroot")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("Raimo")},Food{People, std::string("Joonas")},Food{People, std::string("Petteri")},Food{PeopleFood, std::string("Cornered beef")},Food{People, std::string("Joonas")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Cornered beef")},Food{Herbs, std::string("Poppy seeds")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Poppy seeds")}}),std::list({Food{Herbs, std::string("Poppy seeds")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Pork ribs")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Raimo")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("Joonas")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Arrowroot")},Food{PeopleFood, std::string("Pork ribs")},Food{People, std::string("The Pope")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Pork rack")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Bay leaves")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Jack Sparrow")}}),std::list({Food{People, std::string("Jack Sparrow")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Jack Sparrow")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Salvia officinalis")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Konsta")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia officinalis")},Food{PeopleFood, std::string("Tenderloin steak")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Salvia divinorum")},Food{Herbs, std::string("Poppy seeds")},Food{PeopleFood, std::string("Pork rack")}})});
        TestCase(3,correct_not_reserved,TEatSize<FantasyDragon>,inputs_not_reserved0);
    };
}
PREREQ_TEST(ChineseDragon, Eat_dragon_size, 1, 1) {
    {
        std::vector correct_not_reserved = {(size_t)6,(size_t)6,(size_t)12};
        gcheck::SequenceArgument inputs_not_reserved0({std::list({Food{People, std::string("Joonas")},Food{PeopleFood, std::string("Pork rack")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Flank steak")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{People, std::string("John Smith")},Food{People, std::string("Petteri")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Horse (salami)")},Food{Herbs, std::string("Poppy seeds")}}),std::list({Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Joonas")},Food{People, std::string("Joonas")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("Random crusader")},Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{Herbs, std::string("Bay leaves")},Food{Herbs, std::string("Bay leaves")},Food{PeopleFood, std::string("Tenderloin steak")}}),std::list({Food{People, std::string("Jack Sparrow")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia divinorum")},Food{PeopleFood, std::string("Tenderloin steak")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Joonas")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Carnivore pizza")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Salvia divinorum")},Food{People, std::string("Raimo")},Food{PeopleFood, std::string("Pork ribs")},Food{PeopleFood, std::string("Horse (salami)")},Food{People, std::string("Konsta")},Food{PeopleFood, std::string("Pork rack")},Food{Herbs, std::string("Salvia officinalis")},Food{People, std::string("The Pope")},Food{Herbs, std::string("Arrowroot")},Food{People, std::string("Jack Sparrow")},Food{PeopleFood, std::string("Half of a pork's ass")},Food{PeopleFood, std::string("Flank steak")},Food{People, std::string("Jack Sparrow")}})});
        TestCase(3,correct_not_reserved,TEatSize<ChineseDragon>,inputs_not_reserved0);
    };
}


template<typename T>
std::string TPrint(std::tuple<std::list<Treasure>, std::string, size_t, size_t> input) {
    std::list<Treasure>& treasures = std::get<0>(input);
    std::string& name = std::get<1>(input);
    size_t& age = std::get<2>(input);
    size_t& size = std::get<3>(input);
    T dragon(name, age, size);
    dragon.Hoard(treasures);
    std::stringstream os;
    os << dragon;
    return os.str();
} 


PREREQ_TEST(Dragon, ostream_write_operator, 1, 2) {
    {
        std::vector correct_not_reserved = {"Dragon named: Haku, age: 1201, size: 29\nTreasures:\nGin tonic\nElixir of euphoria\nElixir of euphoria\nElixir of euphoria\nStoneskin potion\nBlemish blitzer\nEssence of insanity\nEssence of insanity\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::string, size_t, size_t>(std::list({Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Agate")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Ruby")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Silver coins")},Treasure{Potions, std::string("Essence of insanity")}}),"Haku",1201,29)});
        TestCase(1,correct_not_reserved,TPrint<MagicDragon>,inputs_not_reserved0);
    };
    {
        std::vector correct_not_reserved = {"Dragon named: Puff, age: 6991, size: 6\nTreasures:\nTopaz\nTopaz\nJade stone\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::string, size_t, size_t>(std::list({Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("Scroll of infinite wisdom")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Jewellery, std::string("Topaz")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Gin tonic")},Treasure{Jewellery, std::string("Jade stone")}}),"Puff",6991,6)});
        TestCase(1,correct_not_reserved,TPrint<FantasyDragon>,inputs_not_reserved0);
    };
    {
        std::vector correct_not_reserved = {"Dragon named: Drogon, age: 6021, size: 9\nTreasures:\nBiographia literaria\nMAOL\nThus Spoke Zarathustra\nThe Symposium\nBiographia literaria\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::string, size_t, size_t>(std::list({Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Essence of insanity")},Treasure{Potions, std::string("Gin tonic")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Jewellery, std::string("Sapphire dust")},Treasure{Potions, std::string("Gin tonic")},Treasure{Wisdom, std::string("MAOL")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Garroting gas")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Ruby")},Treasure{Wisdom, std::string("Thus Spoke Zarathustra")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Wisdom, std::string("Biographia literaria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Jewellery, std::string("Sapphire dust")}}),"Drogon",6021,9)});
        TestCase(1,correct_not_reserved,TPrint<ChineseDragon>,inputs_not_reserved0);
    };
}

PREREQ_TEST(DragonCave, Accommodate, 2, 2) {
    
    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());
    ChineseDragon* cdragon = new ChineseDragon("Haku", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    cave.Accommodate(cdragon);

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(mdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(fdragon, *it) << "Second item in GetDragons";
    it++;

    EXPECT_EQ(cdragon, *it) << "Third item in GetDragons";
}

TEST_(DragonCave, Evict, 3) {
    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());
    ChineseDragon* cdragon = new ChineseDragon("Haku", rnd_age.Next(), rnd_size.Next());
    MagicDragon* mdragon2 = new MagicDragon("Drogon", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    cave.Accommodate(cdragon);
    cave.Accommodate(mdragon2);

    cave.Evict("Puff");

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(fdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(cdragon, *it) << "Second item in GetDragons";
    it++;

    EXPECT_EQ(mdragon2, *it) << "Third item in GetDragons";

    delete mdragon;
}

std::string TCavePrint(std::tuple<std::list<Treasure>, std::vector<std::string>, std::vector<size_t>, std::vector<size_t>> input) {
    std::list<Treasure>& treasures = std::get<0>(input);
    std::vector<std::string>& names = std::get<1>(input);
    std::vector<size_t>& ages = std::get<2>(input);
    std::vector<size_t>& sizes = std::get<3>(input);
    DragonCave cave;
    MagicDragon* mdragon = new MagicDragon(names[0], ages[0], sizes[0]);
    FantasyDragon* fdragon = new FantasyDragon(names[1], ages[1], sizes[1]);
    ChineseDragon* cdragon = new ChineseDragon(names[2], ages[2], sizes[2]);
    mdragon->Hoard(treasures);
    fdragon->Hoard(treasures);
    cdragon->Hoard(treasures);
    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    cave.Accommodate(cdragon);
    std::stringstream os;
    os << cave;
    return os.str();
} 

TEST_(DragonCave, stream_write_operator, 3) {
    {
        std::vector correct_not_reserved = {"DragonCave dwellers:\n\nDragon named: Drogon, age: 7507, size: 29\nTreasures:\nStoneskin potion\nGarroting gas\nCough syrup\nGarroting gas\nElixir of euphoria\nBlemish blitzer\nBlemish blitzer\n\nDragon named: Haku, age: 2444, size: 28\nTreasures:\nBag of pearls\nBag of pearls\nAgate\nTopaz\nTopaz\nSilver coins\n\nDragon named: Drogon, age: 4757, size: 21\nTreasures:\nSun Tzu\'s Art of War\nThe C++ standard\nSun Tzu\'s Art of War\nThe C++ standard\nThe Symposium\nThe C++ standard\nCritique of pure reason\nThe Symposium\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::make_tuple<std::list<Treasure>, std::vector<std::string>, std::vector<size_t>, std::vector<size_t>>(std::list({Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Bag of pearls")},Treasure{Jewellery, std::string("Agate")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Stoneskin potion")},Treasure{Wisdom, std::string("Sun Tzu's Art of War")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Jewellery, std::string("Topaz")},Treasure{Potions, std::string("Cough syrup")},Treasure{Wisdom, std::string("The C++ standard")},Treasure{Potions, std::string("Garroting gas")},Treasure{Wisdom, std::string("Critique of pure reason")},Treasure{Potions, std::string("Elixir of euphoria")},Treasure{Wisdom, std::string("The Symposium")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Potions, std::string("Blemish blitzer")},Treasure{Jewellery, std::string("Silver coins")}}),std::vector({std::string("Drogon"),std::string("Haku"),std::string("Drogon")}),std::vector({(size_t)7507,(size_t)2444,(size_t)4757}),std::vector({(size_t)29,(size_t)28,(size_t)21}))});
        TestCase(1,correct_not_reserved,TCavePrint,inputs_not_reserved0);
    };
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
    static auto has_copy_constructor(int) -> sfinae_true<decltype(T(std::declval<T>()))>;
    template<class T>
    static auto has_copy_constructor(long) -> sfinae_false<T>;
    
    template<class T>
    static auto has_copy_assignment(int) -> sfinae_true<decltype(std::declval<T>() = std::declval<T>())>;
    template<class T>
    static auto has_copy_assignment(long) -> sfinae_false<T>;
} // detail

template<class T>
struct has_copy_constructor_t : decltype(detail::has_copy_constructor<T>(0)){};
template<class T>
struct has_copy_assignment_t : decltype(detail::has_copy_assignment<T>(0)){};

TEST_(DragonCave, copy_assignment_constructor, 2) {
    bool has_copy_constructor = has_copy_constructor_t<DragonCave>();
    bool has_copy_assignment = has_copy_assignment_t<DragonCave>();
    EXPECT_FALSE(has_copy_constructor) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Bird)\nfor any changes to this to take effect when running locally";
    EXPECT_FALSE(has_copy_assignment) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Bird)\nfor any changes to this to take effect when running locally";
}