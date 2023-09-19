/**********

Open-Close principle: It states that, your system should be open to extensions. So you that you should be able to extend your system by inheritance (for example)
					  But it should be closed to modification. Above we are modifying the existing code (filter by color, filter by size) instead of using 
					  inheritance. 
					  Now we will build a better filter and we are going to do it with the help of specification pattern, which is an enterprise
					  patter, a pattern related to data. Do it by defining two interfaces: specification and filter
***********/

#include<iostream>
#include<boost/lexical_cast.hpp>
#include<cstdlib>
#include<vector>
#include<string>

enum class Color {red, green, blue};
enum class Size {small, medium, large};


struct Product{
	std::string name;
	Color color;
	Size size;

	Product(const std::string name, Color color, Size size){
		this->name = name;
		this->color = color;
		this->size = size;
	}
};


struct ProductFilter{
	std::vector<Product*> by_color(std::vector<Product*> items, Color color){
		std::vector<Product*> result;
		for(auto &i : items){
			if(i->color == color) result.push_back(i);
		}
		return result;
	}
 //Similar we can make filter by size, and for all kind of requirement you need to copy your code which is ineffective
};


//Specification interface
// template <typename T> struct AndsSpecification;

template<typename T> struct specification {
	//defining pure virtual method
	virtual bool is_satisfied(T *item) = 0;

	//we can add both specification using operator here
	// AndsSpecification<T> operator &&(specification<T> &&other) {
	// 	return AndsSpecification<T>(*this, other);
	// }
};

template<typename T> struct Filter {
	virtual std::vector<T *> filter(std::vector<T*> items, specification<T> &spec) = 0;
};

//Now we will extend the Filter to implemet the filter method
struct BetterFilter : Filter<Product> {
	std::vector<Product *> filter(std::vector<Product*> items, specification<Product> &spec) override {
			std::vector<Product *> result;
			for(auto &i : items){
				if(spec.is_satisfied(i)) result.push_back(i);
			}
			return result;
	}
};

struct ColorSpecification : specification<Product> {
	Color color;
	ColorSpecification(Color color) : color(color) {}
	bool is_satisfied(Product *items) override {
		return items->color == color;
	}
};


struct SizeSpecification : specification<Product> {
	Size size;
	explicit SizeSpecification(Size size) : size(size) {}
	bool is_satisfied(Product *item) override {
		return item->size == size;
	}
};


template<typename T> struct AndSpecification : specification<T> {
		specification<T> &first;
		specification<T> &second;

		AndSpecification(specification<T> &first, specification<T> &second) : first(first), second(second) {}

		bool is_satisfied(T *item) override {
			return first.is_satisfied(item) && second.is_satisfied(item);
		}
};


int main(){

	Product apple("Apple", Color::green, Size::small);
	Product banana("Banana", Color::blue, Size::medium);
	Product house("House", Color::green, Size::large);

	std::vector<Product*> items{ &apple, &banana, &house};

	/*******filter not efficiently

	ProductFilter pm;
	std::vector<Product*> res = pm.by_color(items, Color::blue);
	// std::cout << colors[res[0]->color];
	for(auto &i : res){
		std::cout<<i->name<<" "<<static_cast<int>(i->color)<<std::endl; // to get the names of enum instead integer values, you need to use the maps
	}

	********/

	BetterFilter bf;
	ColorSpecification green(Color::green);

	SizeSpecification large(Size::large);

	for(auto &item : bf.filter(items, green)){
			std::cout << "This item : "<<item->name << " is green" <<std::endl; 
	}
	for(auto &item : bf.filter(items, large)){
			std::cout << "This item : "<<item->name << " is large" <<std::endl; 
	}

	AndSpecification<Product> green_and_large(green, large); 

	for(auto &item : bf.filter(items, green_and_large)){
			std::cout << "This item : "<<item->name << " is green and large " <<std::endl; 
	}

	// auto spec = green && large;
	// for(auto &item : bf.filter(items, spec)){
	// 		std::cout << "New way -- This item : "<<item->name << " is green and large " <<std::endl; 
	// }

	getchar();
	return 0;
}