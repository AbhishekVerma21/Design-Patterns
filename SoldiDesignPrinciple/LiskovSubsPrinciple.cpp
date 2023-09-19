/***************
 * LiskovSubstitutionPrinciple
 * Def: Subtypes should be immediately substitutable though their base types
 * 
 * Example for Voilation of LSP
 * The Liskov Substitution Principle states that subtypes should be immediately substitutable for their base types without altering the correctness of the program.
 * In your code, "you've attempted to create a Square class that inherits from the Rectangle class, and this is where the violation occurs.
 * In this Square class, you have overridden the setWidth and setHeight methods to ensure that both width and height are set to the same value, which is fine for a square. 
 * However, this violates the Liskov Substitution Principle because it changes the behavior of the base class, Rectangle".
 * In a Rectangle, you should be able to set the width and height independently, but in a Square, you are forced to set them to the same value.
 * 
*/
#include <iostream>
#include <cstdio>
class Rectangle {
    protected:
        int width, height;
    public:
        Rectangle(int width, int height) : width(width), height(height) {}

        int getWidth() const {
            return width;
        }
        int getHeight() const {
            return height;
        }
        virtual void setWidth(int width) {  //virtual so that we can override them in child class
            this->width = width; //Rectangle::width = width;
        }
        virtual void setHeight(int height) {
            this->height = height; //Rectangle::height = height;
        }

        int area() const {
            return (this->width * this->height) ;
        }
};


//Somewhere down the line, you think that let extend the Rectange and make it square


//Wrong way to use extend a class breaks the LSP
class Square : public Rectangle {
public:
    Square(int size) : Rectangle(size, size) {}

    void setWidth (int width) override{
        this->width = this->height = width;
    }
    void setHeight (int height) override    {
        this->width = this->height = height;
    }

};


//To fix this, we need to just make a factory
/** Fine but not corrct : Read the top paragraph
class RectangleFactory{
public:
    static Rectangle create_rectangle(int width, int height){
        return Rectangle(width, height);
    }
    static Rectangle create_square(int size){   //changing rectangle behaviour so violating the LSP here also
        return Rectangle(size, size);         
    }
};
*/

//Assume I have some API to working with rectange

void process(Rectangle &r){
    int w = r.getWidth();
    r.setHeight(10);

    std::cout<<"expected area = "<<(w*10)<<std::endl<<"Actual Area in process = "<<r.area()<<std::endl;
}

int main(){

    Rectangle r(3, 4);
    process(r);

    
    Square s(3);
    process(s);
    
    /*
    Rectangle re = RectangleFactory::create_rectangle(8,9);
    Rectangle sq = RectangleFactory::create_square(7);
    std::cout<<"rectangle area = "<<re.area()<<",  Square area = "<<sq.area()<<std::endl;
    */
    getchar();
    return 0;
}