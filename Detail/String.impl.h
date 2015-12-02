#ifndef STRING_IMPL_H
#define STRING_IMPL_H

namespace mstd{

    void string::append(const string &s)
    {
        for(size_type i = 0;i<s.size();++i){
            push_back(s[i]);
        }
    }

    void string::append(const char *s)
    {
        char tmp = *s;
        for(size_type i = 1;tmp != '\0';++i){
            push_back(tmp);
            tmp = *(s + i);
        }
    }
}

#endif // STRING_IMPL_H
