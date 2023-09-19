/*Interface Segregation Principle
   Def: Clients should not be forced to implement or depend on methods they do not use.

   The Interface Segregation Principle (ISP) is one of the SOLID principles of object-oriented design, and it deals with the design of interfaces.
   ISP states that a client should not be forced to depend on interfaces it does not use. 
   In other words, it suggests that interfaces should be fine-grained and tailored to the specific needs of the clients that use them, rather than having large,
   monolithic interfaces that include methods irrelevant to some clients.
*/
#include<iostream>
#include<string>

struct Document{
	std::string str;
	Document(const std::string &str) : str(str) {} //using const is required here, because we are passing a string literal which is in ROM, and when you defile a method like this,
	                                               // It expects that the parameter you passed is modifiable, but the string you passed can not be modified so you need to write
	                                               // const here to tell compiler that this method accept const string only
};

struct IMachine {
	virtual void print(Document &doc) = 0;
	virtual void scan(Document &doc) = 0;
	virtual void fax(Document &doc) = 0;
};

//Now assume you want to implement a multifunctional printer, so above interface suits really well

//Example
struct MFP : IMachine {
	void print(Document &doc) override {
		//code here
	}

	void scan(Document &doc) override {
		//code here
	}
	
	void fax(Document &doc) override {
		//code here
	}
};

//Now assume, if I just want to implemt scanner using IMachine interface

// struct scanner : IMachine {
// 	void print(Document &doc) override {
// 		//Not implemented or exception here
// 	}
// 	void scan(Document &doc) override {
// 		//code here
// 	}
// 	void fax(Document &doc) override {
// 		//Not implemented or exception here
// 	}
// };


//This is wrong so you need to segregate the interfaces

struct IPrinter {
	virtual void print(struct Document &doc) = 0;
};

struct IScanner {
	virtual void scan(struct Document &doc) = 0;
};

struct IFax {
	virtual void fax(struct Document &doc) = 0;
};


//Implement seperately
struct printer : IPrinter{
	void print(struct Document &doc) override{
		std::cout<<"The printer prints : "<<doc.str<<std::endl;
	}
};

struct scanner : IScanner{
	void scan(struct Document &doc) override{
		std::cout<<"The printer prints : "<<doc.str<<std::endl;
	}
};


//OR
//lets assume that you want a machine that can print and scan;
//In that case you can just make an abstract interface that can use reuse scanner and printer interfaces

struct IMachP_S : IPrinter, IScanner {};

//Now you want to implement them by implemeting that extented interface
struct MachP_S : IMachP_S {
	IPrinter &printer;
	IScanner &scanner;

	MachP_S(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

	void print(struct Document &doc) override {
		printer.print(doc); //Call the print method from the printer object as we passed the printer objects in the main method
	}

	void scan(struct Document &doc) override {
		scanner.scan(doc);
	}
};


int main(){

	//we are going to print by using correct interfaces
	Document doc("This is the doc");
	printer p;
	scanner s;
	MachP_S mp(p, s); //Pass the printer and scanner instances to MachP_S

	mp.print(doc);

	getchar();
	return 0;
}


//Lets assume that you reuse the Printer and scanner implementation, so for that you can use a decorator


//Core: Do not stuck to much into a single interface
