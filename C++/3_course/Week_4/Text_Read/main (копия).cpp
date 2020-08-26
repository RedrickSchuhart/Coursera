#include <string>
#include <string_view>
#include "test_runner.h"
using namespace std;

class Editor {
 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() {
        pos = 0;
        size = 0;
        new_text.reserve(1000000);
        text.reserve(1000000);
        buffer.reserve(1000000);
        //text_ = text;

    }
  void Left() {
      if(pos!=0)
          pos-=1;
  }
  void Right() {
      if(pos!=size) {
          pos+=1;
      }
  }
  void Insert(char token) {
      //text_ = text;
      //((new_text = text_.substr(0, pos))+=token)+=text_.substr(pos);
      //text = new_text;
      text.insert(pos, 1, token);
      size += 1;
      pos += 1;
  }
  void Cut(size_t tokens = 1) {
      text_ = text;
      if(pos+tokens>size)
          tokens=size-pos;
      buffer_ = text_.substr(pos, tokens);
      text.erase(pos, tokens);
      size -= tokens;
  }
  void Copy(size_t tokens = 1) {
      text_ = text;
      if(pos+tokens>size)
          tokens=size-pos;
      buffer_ = text_.substr(pos, tokens);
  }
  void Paste() {
      //text_ = text;
      //((new_text = text_.substr(0, pos))+=buffer_)+=text_.substr(pos);
      //text = new_text;
      text.insert(pos, buffer_);
      pos += buffer.size();
      size += buffer.size();
  }
  string GetText() const {
      return text;
  }
private:
  string_view text_, buffer_;
  string text, buffer, new_text;
  size_t pos, size;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
