#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/vector_it.hpp"

gcheck::RandomSizeContainer rnd(1, 20, 0, 1000);

std::vector<int> TRead(const std::vector<int>& v) {
    std::string input;
    for(auto i : v) {
        input += std::to_string(i) + " ";
    }
    input += "!\n";
    gcheck::StdinInjecter tin(input);
    
    std::vector<int> out = ReadVector();
    
    return out;
}

TEST(Iterator, ReadVector) {
    {
        std::vector correct_not_reserved = {std::vector<int>{ 436,240,160,41,724,223,957,918},std::vector<int>{ 447,157,624,100,416,644,872,422,737,254,332,301,65,75,600,29,596,395,15,158},std::vector<int>{ 652,927,482,440,520,652},std::vector<int>{ 664,403,164,179,347,284,135,708,828,868,12,286,502,495,199,487,755,868},std::vector<int>{ 507,882},std::vector<int>{ 20,359,969,385,983,405,935,262,299,340,729,322,919,91,623,744,495,750,148,344},std::vector<int>{ 658,848,63,91,444,514,54,641,845,146,808,21,830,648,948,198,402},std::vector<int>{ 362,862,398,166,655,182,395,164,627,486,797,255,757,796},std::vector<int>{ 705,582,417,371,380,631,289,41,234,817,467,214,338,856},std::vector<int>{ 32,952,72,927}};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({436, 240, 160, 41, 724, 223, 957, 918}),std::vector<int>({447, 157, 624, 100, 416, 644, 872, 422, 737, 254, 332, 301, 65, 75, 600, 29, 596, 395, 15, 158}),std::vector<int>({652, 927, 482, 440, 520, 652}),std::vector<int>({664, 403, 164, 179, 347, 284, 135, 708, 828, 868, 12, 286, 502, 495, 199, 487, 755, 868}),std::vector<int>({507, 882}),std::vector<int>({20, 359, 969, 385, 983, 405, 935, 262, 299, 340, 729, 322, 919, 91, 623, 744, 495, 750, 148, 344}),std::vector<int>({658, 848, 63, 91, 444, 514, 54, 641, 845, 146, 808, 21, 830, 648, 948, 198, 402}),std::vector<int>({362, 862, 398, 166, 655, 182, 395, 164, 627, 486, 797, 255, 757, 796}),std::vector<int>({705, 582, 417, 371, 380, 631, 289, 41, 234, 817, 467, 214, 338, 856}),std::vector<int>({32, 952, 72, 927})});
        TestCase(10,correct_not_reserved,TRead,inputs_not_reserved0);
    };
}


std::string TPrintSum1(std::vector<int> v) {
    gcheck::StdoutCapturer tout;
    
    PrintSum1(v);
    
    return tout.str();
}

TEST(Iterator, PrintSum1) {
    {
        std::vector correct_not_reserved = {"212 827 1053 1041 1060 727 \n","1198 1646 1605 904 390 764 1209 1480 801 973 847 187 595 1105 1642 1174 1192 993 358 \n","1089 931 674 \n","843 \n","1007 1214 1131 1151 1115 518 829 1141 1108 770 1028 1361 520 182 \n","515 721 \n","1299 1142 680 656 433 329 401 464 379 289 452 760 527 162 \n","1198 232 858 1747 1631 1373 921 804 1044 1479 1318 848 1278 834 286 1214 1022 395 1250 \n","687 233 885 1551 1128 1252 1813 1608 1625 1631 909 1142 1415 809 355 664 \n","604 588 399 452 935 1505 1606 1433 578 832 1483 1641 1147 \n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({189, 23, 804, 249, 792, 268, 459}),std::vector<int>({277, 921, 725, 880, 24, 366, 398, 811, 669, 132, 841, 6, 181, 414, 691, 951, 223, 969, 24, 334}),std::vector<int>({603, 486, 445, 229}),std::vector<int>({272, 571}),std::vector<int>({524, 483, 731, 400, 751, 364, 154, 675, 466, 642, 128, 900, 461, 59, 123}),std::vector<int>({65, 450, 271}),std::vector<int>({502, 797, 345, 335, 321, 112, 217, 184, 280, 99, 190, 262, 498, 29, 133}),std::vector<int>({988, 210, 22, 836, 911, 720, 653, 268, 536, 508, 971, 347, 501, 777, 57, 229, 985, 37, 358, 892}),std::vector<int>({526, 161, 72, 813, 738, 390, 862, 951, 657, 968, 663, 246, 896, 519, 290, 65, 599}),std::vector<int>({114, 490, 98, 301, 151, 784, 721, 885, 548, 30, 802, 681, 960, 187})});
        TestCase(10,correct_not_reserved,TPrintSum1,inputs_not_reserved0);
    };
}


std::string TPrintSum2(std::vector<int> v) {
    gcheck::StdoutCapturer tout;
    
    PrintSum2(v);
    
    return tout.str();
}

TEST(Iterator, PrintSum2) {
    {
        std::vector correct_not_reserved = {"898 822 1333 713 1505 1094 1197 \n","1182 494 464 1493 1527 1929 863 \n","764 502 1210 \n","418 1402 768 1502 918 1040 1783 \n","1260 1209 1350 583 514 \n","724 586 1169 1750 \n","1033 \n","554 606 1186 966 1729 934 271 1861 1616 1017 \n","1620 1094 1264 \n","1341 1052 349 515 \n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({489, 692, 903, 359, 732, 245, 620, 577, 849, 773, 354, 430, 130, 409}),std::vector<int>({438, 310, 166, 616, 788, 966, 825, 38, 963, 739, 877, 298, 184, 744}),std::vector<int>({455, 123, 939, 271, 379, 309}),std::vector<int>({392, 409, 694, 949, 779, 359, 830, 171, 953, 681, 139, 553, 74, 993, 26}),std::vector<int>({312, 644, 939, 73, 500, 365, 14, 510, 411, 565, 948}),std::vector<int>({667, 571, 740, 817, 928, 933, 429, 15, 57}),std::vector<int>({710, 323}),std::vector<int>({206, 115, 774, 473, 818, 915, 180, 943, 676, 401, 616, 940, 918, 91, 19, 911, 493, 412, 491, 348}),std::vector<int>({785, 160, 824, 440, 934, 835}),std::vector<int>({802, 541, 212, 289, 226, 137, 511, 539})});
        TestCase(10,correct_not_reserved,TPrintSum2,inputs_not_reserved0);
    };
}
