#pragma once
#include "date.h"
#include "token.h"
#include <memory>

struct Node {
    virtual bool Evaluate(const Date& _date, const string& _event) const = 0;
};

struct EmptyNode : public Node {
    bool Evaluate(const Date& _date, const string& _event) const override;
};

struct LogicalOperationNode : public Node {
    LogicalOperationNode(LogicalOperation _cmp, shared_ptr<Node> _left, shared_ptr<Node> _right)
        : cmp(_cmp), left(_left), right(_right){}
    bool Evaluate(const Date& _date, const string& _event) const override;
private:
  const LogicalOperation cmp;
  shared_ptr<const Node> left, right;

};

struct DateComparisonNode : public Node {
    DateComparisonNode(Comparison cmp_, Date date_) : cmp(cmp_), date(date_) {}
    bool Evaluate(const Date& _date, const string& _event) const override;

private:
  const Comparison cmp;
  const Date date;
};

struct EventComparisonNode : public Node {
    EventComparisonNode(Comparison cmp_, string event_) : cmp(cmp_), event(event_) {}
    bool Evaluate(const Date& _date, const string& _event) const override;

private:
  const Comparison cmp;
  const string event;
};
