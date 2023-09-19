/*
	Dependency Inversion Principle (DIP): It is one of the five SOLID principles of object-oriented programming and design. 
	It is a guideline that helps in creating more flexible and maintainable software by promoting loose coupling between high-level modules and low-level modules. 
	The principle consists of two key ideas:
	1. High-level modules should not depend on low-level modules. Both should depend on abstractions.
	2. Abstractions should not depend on details. Details should depend on abstractions.

	Abstraction : Interfaces, base clases, 

    In simpler terms, this principle encourages the use of interfaces or abstract classes to define how different components of a system should interact with each other.
    Concrete implementations of these interfaces or abstract classes should be injected into the high-level modules,
    allowing for easier changes and substitutions without affecting the overall system.
*/

//Lets  model relationship between different people


#include<iostream>
#include<string>
#include<vector>
#include<tuple>


enum class Relationship{ //class after enum is c++style writing, which gives you power to use scope.
	parent,
	child,
	sibling,
};


struct Person{
	std::string name;
	// std::string mane;

};


//To fix the below problem in high level, we use abstraction
struct RelationshipBrowser {
	virtual std::vector<Person> find_all_child_of(const std::string &parent) = 0;
};


struct Relationships : RelationshipBrowser {  //low-level module/contruct for our module
	std::vector<std::tuple<Person, Relationship, Person>> relations;

	//providing API for adding elements to this relations collection
	void add_parent_and_child(const Person &parent, const Person &child){
		relations.push_back({parent, Relationship::parent, child});
		relations.push_back({child, Relationship::child, parent});
	}

	std::vector<Person> find_all_child_of(const std::string &parent) override{
		std::vector<Person> result;

		for(auto &&[first, rel, second] : relations){
			if(first.name == parent && rel == Relationship::parent)
				result.push_back(second);
		}
		return result;
	}
};



struct Research{ //High-level

	Research(RelationshipBrowser &browser){ //Always remember to make object of abstract class as a reference otherwise compilation fail
		for(auto &child : browser.find_all_child_of("John")){
			std::cout<<"John has child name : "<<child.name<<std::endl;
		}
	}

	//to break this depency principle, we can just take the low level module object here. This is wrong
	//It breaks here, because let say, the low level module made vector private then your code will break.
	//So depency inversion principle exists for the same, it protects you from the change in the implementation details.
	// Research(Relationships &relationships){
	// 	auto &relations = relationships.relations;
	// 	for(auto &&[first, rel, second] : relations){
	// 		if(first.name == "John" && rel == Relationship::parent) 
	// 			std::cout<<"John has child : "<<second.name<<std::endl;
	// 		// std::cout<<"checking the second variable in mane string : "<<first.mane<<std::endl;
	// 	}
	// }
};


int main(){
	Person parent{"John"};
	Person child1{"Chris"}, child2{"Matt"};
	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships); // relationships implements RelationshipBrowser, so if we put into the constructor of Research, because of polymorphism it will work just fine. 

	getchar();
	return 0;
}