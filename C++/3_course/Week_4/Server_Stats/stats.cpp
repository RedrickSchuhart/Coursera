#include "stats.h"
#include "vector"

using namespace std;

HttpRequest ParseRequest(string_view line) {
    size_t pos = 0, space;
    string_view method, uri, protocol;
    while(line[pos]==' ')
        pos++;
    space = line.find(' ', pos);
    method = line.substr(pos, space-pos);
    pos = space+1;
    space = line.find(' ', pos);
    uri = line.substr(pos, space-pos);
    protocol = line.substr(space+1);
    return {method, uri, protocol};
}

const vector<string> Methods = {"GET",
                               "PUT",
                               "POST",
                               "DELETE",
                               "UNKNOWN",};

const vector<string> Uris = {"/",
                            "/order",
                            "/product",
                            "/basket",
                            "/help",
                            "unknown",};

Stats::Stats() {
    methods = {{Methods[0], 0},
               {Methods[1], 0},
               {Methods[2], 0},
               {Methods[3], 0},
               {Methods[4], 0},};
    uris = {{Uris[0], 0},
            {Uris[1], 0},
            {Uris[2], 0},
            {Uris[3], 0},
            {Uris[4], 0},
            {Uris[5], 0},};
}

void Stats::AddMethod(string_view method) {
    bool f=false;
    for(int i=0; i<4; i++) {
        if(method==Methods[i])
            f=true;
    }
    if(f) {
        methods[method]++;
    } else {
        methods[Methods[4]]++;
    }
}

void Stats::AddUri(string_view uri) {
    bool f=false;
    for(int i=0; i<5; i++) {
        if(uri==Uris[i])
            f=true;
    }
    if(f) {
        uris[uri]++;
    } else {
        uris[Uris[5]]++;
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return methods;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uris;
}
