#include "ini.h"
#include <stdexcept>

using namespace std;

namespace Ini {

Section& Document::AddSection(string name) {
    return(sections[name]);
}

const Section& Document::GetSection(const string& name) const {
    auto it = sections.find(name);
    if(it!=sections.end()) {
        return (*it).second;
    } else {
        throw out_of_range("not");
    }
}

size_t Document::SectionCount() const {
    return sections.size();
}

Document Load(istream& input) {
    string str, name, value;
    Section* itSection;
    Document doc;
    while(getline(input, str)) {
        if((str[0]!=' ')&&(str.length()!=0)) {
            if(str[0]=='[') {
                itSection = &doc.AddSection(str.substr(1, str.length()-2));
            } else {
                size_t n = str.find('=');
                name = str.substr(0, n);
                value = str.substr(n+1);
                (*itSection)[name]=value;
            }
        }
    }
    return doc;
}

}
