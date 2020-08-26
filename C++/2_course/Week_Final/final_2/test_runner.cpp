#include "date.h"
#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

void TestParseDateandEvent() {
  {
    istringstream is("2017-11-07 big sport event");
    const auto date = ParseDate(is);
    ostringstream stream;
    stream << date;
    string str =  stream.str();
    AssertEqual(str, "2017-11-07", "date");
    AssertEqual(ParseEvent(is), "big sport event", "Parse event without leading spaces");
  }

    {
      istringstream is("2017-11-07  first event  \n  second event");
      const auto date = ParseDate(is);
      ostringstream stream;
      stream << date;
      string str =  stream.str();
      AssertEqual(str, "2017-11-07", "Parse event without leading spaces");
      vector<string> events;
      events.push_back(ParseEvent(is));
      events.push_back(ParseEvent(is));
      AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestParseCondition() {
    istringstream is("date == 2017-10-11 AND event == \"uuuu\"");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);

    };
    Date date(2017,10,11);
    AssertEqual(predicate(date, "uuuu"), true, "Parse");

}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseDateandEvent, "TestParseDateandEvent");
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
