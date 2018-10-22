#include <Tests/lib/googletest/googletest/include/gtest/gtest.h>
#include <Output/Output.h>


char* path = const_cast<char *>("../lib");
struct stat st;

TEST(FullPath_Test, get_full_path){
    Output output(path);
    EXPECT_EQ("../lib/ProgramOutput", output.getFullPath());
}

TEST(Constructor_Tests, folder_making){
    Output output(path);
    EXPECT_EQ(stat("../lib/ProgramOutput",&st), 0);
}

TEST(Constructor_Tests, file_making){
    Output output(path);
    EXPECT_EQ(stat("../lib/ProgramOutput/Summery.txt",&st), 0);
}

TEST(Constructor_Tests, write_to_file){
    Output output(path);
    ifstream file("../lib/ProgramOutput/Summery.txt");
    string line;
    getline(file, line);
    EXPECT_EQ("Summery", line);
}

TEST(Constructor_Tests, case_directory_not_exists){
    EXPECT_THROW(Output output("../li"), ios_base::failure);
}



