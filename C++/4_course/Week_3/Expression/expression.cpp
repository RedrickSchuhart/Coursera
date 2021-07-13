#include "Common.h"


class ValueNode: public Expression {
public:
  //virtual ~Expression() = default;
    ValueNode(int value_) : value(value_) {
    }
  // Вычисляет значение выражения
    virtual int Evaluate() const{
        return value;
    }

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const {
        return std::to_string(value);
    }
private:
    int value;
};

class SumNode: public Expression {
public:
  //virtual ~Expression() = default;
    SumNode(ExpressionPtr left_, ExpressionPtr right_) : left(move(left_)), right(move(right_)) {
    }
  // Вычисляет значение выражения
    virtual int Evaluate() const{
        return left->Evaluate()+right->Evaluate();
    }

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const {
        return ("("+left->ToString()+")+("+right->ToString()+")");
    }
private:
    ExpressionPtr left, right;
};

class ProductNode: public Expression {
public:
  //virtual ~Expression() = default;
    ProductNode(ExpressionPtr left_, ExpressionPtr right_) : left(move(left_)), right(move(right_)) {
    }
  // Вычисляет значение выражения
    virtual int Evaluate() const{
        return left->Evaluate()*right->Evaluate();
    }

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const {
        return ("("+left->ToString()+")*("+right->ToString()+")");
    }
private:
    ExpressionPtr left, right;
};

ExpressionPtr Value(int value) {
    return std::make_unique<ValueNode>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<SumNode>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<ProductNode>(move(left), move(right));
}
