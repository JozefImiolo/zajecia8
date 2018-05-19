#include <iostream>
#include "example.hpp"
#include "rational.hpp"
#include <memory>

using namespace std;


class Literal;
class Add;
class Mult;

class Visitor {
public:
    virtual void visit(const Literal& e) = 0;
    virtual void visit(const Add& e) = 0;
    virtual void visit(const Mult& e) = 0;
    virtual ~Visitor() = default;
};


class Expression {
public:
    virtual ~Expression() = 0;
    virtual double eval() const = 0;
    virtual void accept(Visitor& v) const = 0;
    //przeciazony operator wypisania
};

inline Expression::~Expression() = default;

inline double Expression::eval() const {
    return 0;
}

class Literal : public Expression {
    double val;
public:
    explicit Literal(double val): val{val} { }

    double eval() const override {
        return val;
    }

    double getval() const {
        return val;
    }
    void accept(Visitor& v) const {
        v.visit(*this);
    }
};

class BinaryOp : public Expression {
protected:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    BinaryOp(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left{std::move(left)}, right{std::move(right)} { }
    Expression& getLeft() const { return *left; }
    Expression& getRight() const { return *right; }
};

class Add : public BinaryOp {
public:
    using BinaryOp::BinaryOp;

    double eval() const override {
        return left->eval() + right->eval();
    }
    void accept(Visitor& v) const {
        v.visit(*this);
    }
};

class Mult : public BinaryOp {
public:
    using BinaryOp::BinaryOp;

    double eval() const override {
        return left->eval() * right->eval();
    }
    void accept(Visitor& v) const {
        v.visit(*this);
    }
};

double eval_expression(const Expression&e){
   // dynaic cast na wsk lub refeerencji

    //Literal& lit=dynamic cast<Literal&>(e);
    // w przypadku referencji rzuci wyjatek

    if(const Literal* lit=dynamic_cast<const Literal*>(&e))
    {
            return lit->getval();
    }
    else if(const Add* add=dynamic_cast<const Add*>(&e))
    {
            return eval_expression(add->getLeft())+ eval_expression(add->getRight());
    }

    else if(const Mult* mult=dynamic_cast<const Mult*>(&e))
    {
            return eval_expression(mult->getLeft())* eval_expression(mult->getRight());
    }
// danimi cast kosztowny jak wywolanie funkcji wirualnej duza liczba wywolan
    // w Visitorze szybciej

  // minus nowe przypadki pododawac

    // wzorce Visitor nowa metoda w vivitor i implementacja tej mwetody wszedzie

      // niebezpieczen
    //const Literal* lit2=static_cast<const Literal*>(&e);

    //jesli nie to null
    // static cast nie sprawdzi czy tyly sie zgadzaja

}
/*
class Printer : public Visitor {
    std::ostream& os
public:

    void visit(const Literal& e) override {
        std::cout << e.eval();
    }
    void visit(const Add& e) override {
        e.getLeft().accept(*this);
        std::cout << " + ";
        e.getRight().accept(*this);
    }
    void visit(const Mult& e) override {

    }
*/


class Evaluator : public Visitor
{double value;
public:
     void visit(const Literal& e) override{
         value=e.getval();
     }
 void visit(const Add& e) override{
         e.getLeft().accept(*this);
         double leftvalue=value;
         e.getRight().accept(*this);
         double rightvalue=value;
         value=leftvalue+rightvalue;
     }
   void visit(const Mult& e) {}
    ~Evaluator(){}

     double getval() const{
         return value;
     }
};
// dla kazdej klasy
//std::ostream& operator<<(std::ostream& os, const Literal& l) { return os<<getValue();


//dla add referencje get left na expression komiplator nie wike ktora wersja
//wesja hard dynamic cast dla kazdego
/*
std::ostream& operator<<(std::ostream& os, const Expression& w) {
   // return os<<getValue();
    Printer printer(os);
    w.accept(printer);
    return os;
}*/

//doadac pole do prinetra refernacja na ostram
// przeczytac wzorzec odwiedzajacy

int main()
{
    std::unique_ptr<Expression> l1{ new Literal{5} };
    std::unique_ptr<Expression> l2{ new Literal{3} };
    std::unique_ptr<Expression> add{ new Add{std::move(l1), std::move(l2)} };
    //Printer p{};
    //add->accept(p);
    /*
    std::cout<<std::endl<<add->eval()<<std::endl;
     std::cout<<eval_expression(*add)<<std::endl;

     Evaluator e;
     add->accept(e);
             std::cout<<e.getval()<<std::endl;
*/

}

