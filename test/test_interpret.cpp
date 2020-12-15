#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../libs/lib_interpret.h"
#include "../libs/FilePrinter.h"


class inerpretTester : public interpreter{

public:
	inerpretTester(int size): interpreter{size}{}	

	std::vector<std::string> getBlock(){
		std::vector<std::string>  block{m_block};
		return block;
	}
};

/*
class fileTester : public FilePrinter{

public:
	fileTester(std::ofstream& fstr) : FilePrinter{fstr}{}
};*/


void testInputOutput(std::vector<std::string>& input,
					std::vector<std::string>& output,
					int size = 3)
{
	inerpretTester test1{size};
	std::ofstream FileStream1;
    std::shared_ptr<Printer> File1 = std::make_shared<FilePrinter>(FileStream1);
	
	std::stringstream ss;
	for (auto &cmd : input)
  		ss << cmd << std::endl;

  	test1.processStream(ss);
	ASSERT_EQ( test1.getBlock(), output );
}

TEST(gtest_interpret_test1, test_file_simple1){
	std::vector<std::string>  output {"cmd1"};
	testInputOutput(output, output);
}

TEST(gtest_interpret_test1, test_file_simple2){
	std::vector<std::string>  output {"cmd1", "cmd2", "cmd3"};
	testInputOutput(output, output);
}

TEST(gtest_interpret_test1, test_file_bulksize1){
	std::vector<std::string>  input {"cmd1", "cmd2", "cmd3"};
	std::vector<std::string>  output {"cmd3"};
	testInputOutput(input, output, 2);
}

TEST(gtest_interpret_test1, test_file_bulksize2){
	std::vector<std::string>  input {"cmd1", "cmd2", "cmd3", "cmd4", "cmd5", "cmd6"};
	std::vector<std::string>  output {"cmd5", "cmd6"};
	testInputOutput(input, output, 2);
}

TEST(gtest_interpret_test1, test_file_brackets){
	std::vector<std::string>  input {"cmd1", "cmd2", "{"};
	std::vector<std::string>  output {};
	testInputOutput(input, output);
}

TEST(gtest_interpret_test1, test_file_brackets2){
	std::vector<std::string>  input {"cmd1", "cmd2", "{", "cmd3", "cmd4" };
	std::vector<std::string>  output {"cmd3", "cmd4"};
	testInputOutput(input, output);
}

TEST(gtest_interpret_test1, test_file_brackets3){
	std::vector<std::string>  input {"cmd1", "cmd2", "{", "cmd3", "cmd4", "}"};
	std::vector<std::string>  output {};
	testInputOutput(input, output);
}

int main (int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
