#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date& _date, const string& _event) const{
    return true;
}

bool LogicalOperationNode::Evaluate(const Date& _date, const string& _event) const{
    if (cmp == LogicalOperation::And){
        return left->Evaluate(_date, _event) && right->Evaluate(_date, _event);
    }else if(cmp == LogicalOperation::Or){
        return left->Evaluate(_date, _event) || right->Evaluate(_date, _event);
    }else {
      throw logic_error("Unknown Logical evaluate");
    }
}

bool DateComparisonNode::Evaluate(const Date& _date, const string& _event) const{
    if (cmp == Comparison::Less){
        return _date < date;
    }else if(cmp == Comparison::LessOrEqual){
        return _date <= date;
    }else if(cmp == Comparison::Greater){
        return _date > date;
    }else if(cmp == Comparison::GreaterOrEqual){
        return _date >= date;
    }else if(cmp == Comparison::Equal){
        return _date == date;
    }else if(cmp == Comparison::NotEqual){
        return _date != date;
    }else {
      throw logic_error("Unknown comparison date");
    }
}

bool EventComparisonNode::Evaluate(const Date& _date, const string& _event) const{
    if (cmp == Comparison::Less){
        return _event < event;
    }else if(cmp == Comparison::LessOrEqual){
        return _event <= event;
    }else if(cmp == Comparison::Greater){
        return _event > event;
    }else if(cmp == Comparison::GreaterOrEqual){
        return _event >= event;
    }else if(cmp == Comparison::Equal){
        return _event == event;
    }else if(cmp == Comparison::NotEqual){
        return _event != event;
    }else {
      throw logic_error("Unknown comparison event");
    }
}
