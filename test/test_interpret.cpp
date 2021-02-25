#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../libs/lib_interpret.h"
#include "TestPrinter.h"

class inerpretTester : public interpreter{

public:
	inerpretTester(size_t size): interpreter{size}{}	

	std::vector<std::string> getBlock(){
		std::vector<std::string>  block{m_block};
		return block;
	}
};

void testInputOutput(std::vector<std::string>& input,
					std::vector<std::string>& output,
					int size = 3)
{
    std::shared_ptr<inerpretTester> inter1 = std::make_shared<inerpretTester>(size);
	inter1->addPrinter(std::make_shared<ConsolePrinter>());
    inter1->addPrinter(std::make_shared<FilePrinter>(2));
	inter1->addPrinter(std::make_shared<TestPrinter>(1, "Tester"));
	inter1->StartTread();
	for (auto &cmd : input)
  		inter1->putString(std::string(cmd));

	std::this_thread::sleep_for (std::chrono::milliseconds(10));	
	std::ifstream Tester("Tester");
	std::string str;
	std::vector<std::string> result;
	//std::this_thread::sleep_for (std::chrono::milliseconds(10));
	while (std::getline(Tester, str))
    	if(str.size() > 0)
        	result.push_back(str);	
	ASSERT_EQ( result, output);
}

TEST(gtest_interpret_test1, test_file_simple1){
	std::vector<std::string>  input {"cmd11"};
	std::vector<std::string>  output {};
	testInputOutput(input, output);
}

TEST(gtest_interpret_test1, test_file_simple2){
	std::vector<std::string>  input {"cmd11", "cmd22"};
	std::vector<std::string>  output {};
	testInputOutput(output, output);
}

TEST(gtest_interpret_test1, test_file_bulksize1){
	std::vector<std::string>  input {"cmd1", "cmd2", "cmd3"};
	std::vector<std::string>  output {"bulk: cmd1", ",cmd2"};
	testInputOutput(input, output, 2);
}

TEST(gtest_interpret_test1, test_file_bulksize2){
	std::vector<std::string>  input {"cmd1", "cmd2", "cmd3", "cmd4", "cmd5"};
	std::vector<std::string>  output {"bulk: cmd1", ",cmd2", "bulk: cmd3", ",cmd4"};
	testInputOutput(input, output, 2);
}

TEST(gtest_interpret_test1, test_file_brackets){
	std::vector<std::string>  input {"cmd1", "cmd2", "{"};
	std::vector<std::string>  output {"bulk: cmd1", ",cmd2"};
	testInputOutput(input, output);
}


TEST(gtest_interpret_test1, test_file_brackets2){
	std::vector<std::string>  input {"cmd1", "cmd2", "{", "cmd3", "cmd4" };
	std::vector<std::string>  output {"bulk: cmd1", ",cmd2"};
	testInputOutput(input, output);
}

TEST(gtest_interpret_test1, test_file_brackets3){
	std::vector<std::string>  input {"cmd1", "cmd2", "{", "cmd3", "cmd4", "}"};
	std::vector<std::string>  output {"bulk: cmd1", ",cmd2", "bulk: cmd3", ",cmd4"};
	testInputOutput(input, output);
}


int main (int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
