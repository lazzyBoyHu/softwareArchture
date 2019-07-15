#ifndef SETENCEDATA_H_
#define SETENCEDATA_H_


#include <list>
#include <map>
#include <vector>
#include <string>


class SetenceData
{
    public:
        std::list<std::string*> originData;
        std::map<int, std::list<std::string*> > shiftData;
        std::vector<int> sortData;
        SetenceData()
        {
            originData.clear();
            shiftData.clear();
            sortData.clear();
        }
        ~SetenceData()
        {
            shiftData.clear();
            sortData.clear();
            auto listBegin = originData.rbegin();
            auto listEnd = originData.rend();
            for (auto element = listBegin; element !=listEnd; element++)
                delete *element;
            originData.clear();
        }
};


#endif
