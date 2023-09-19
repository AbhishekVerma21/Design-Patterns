#include<iostream>
#include<cstdio>
#include<vector>
#include<boost/lexical_cast.hpp> //boost::lexical_cast is a template function that allows you to convert between different data types in a convenient way. 
                                 //It's particularly useful for converting between numeric types and strings . hpp mean header plus plus
#include<fstream>


//lets define class journal
struct Journal{

	std::string title, check;
	std::vector<std::string> entries;

	//contructor
	Journal (const std::string &title, const std::string &check) : title(title), check(check) {}

	void add_entry(const std::string &entry) {
		static int count = 1;
		entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
	}

	//Now if you want to save your journal to a file, so wrong way to do it is to write a save method in this class.
	//This is wrong because there could be other classes also which will be sving their content to a file
	// OR you might need to refactor your write code from file saving to data base and this could be annoying as rewriting it again in every class
	//So you write these persistent methods as different class . This is called seperation of concern: Here concern related to persistance is moved
	//into seperate components.

};


struct PersistantManager{
	static void save(const Journal &j, const std::string &filename) {
		std::ofstream ofs(filename);
		for(auto & en : j.entries){ //reading each entry in entries line by line by a reference en i.e. not making copy while iterating
			ofs << en << std::endl;	
		}
	}
};


int main(){

	Journal journal("Dear Diary", "checking it");

	journal.add_entry("I started leaning Des. Patt.");
	journal.add_entry("This is Single Responsibility Principle");
	journal.add_entry("It deals with the concerns related to persistance");
	journal.add_entry("For this it uses seperation of concern");

	PersistantManager pm;
	pm.save(journal, "Single_Responsibility_Principle.txt");

	getchar(); //read single character from input stream (usually keyboard)
	return 0;
}