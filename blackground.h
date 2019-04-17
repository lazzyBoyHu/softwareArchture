#ifndef BLACKGROUND_H_
#define BLACKGROUND_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <string.h>

#define MAXLENGTH 20

enum AbstractActionType
{
    AbstractActionType_Input,
    AbstractActionType_Output,
    AbstractActionType_Shift,
    AbstractActionType_Alphabetizer,
};

class AbstractBlackboard;

class AbstractAction
{
    protected:
        AbstractBlackboard * owner;
    public:
        void virtual fire() = 0;
        AbstractAction() {}
        virtual ~AbstractAction() {}
        bool setOwner(AbstractBlackboard * abstractBlackboard)
        {
            if (abstractBlackboard == nullptr)
                return false;
            owner = abstractBlackboard;
            return true;
        }
};

class AbstractBlackboard
{
    private:
        AbstractAction * input;
        AbstractAction * output;
        AbstractAction * shift;
        AbstractAction * alphabetizer;
    public:
        bool setAbstractActionByType(int type, AbstractAction * abstractAction)
        {
            if (abstractAction == nullptr)
                return false;
            if (type > AbstractActionType_Alphabetizer or type < AbstractActionType_Input)
                return false;
            switch (type)
            {
                case AbstractActionType_Input :
                    {
                        if (input != nullptr)
                            delete input;
                        input = abstractAction;
                        input->setOwner(this);
                    }
                    break;
                case AbstractActionType_Output :
                    {
                        if (output != nullptr)
                            delete output;
                        output = abstractAction;
                        output->setOwner(this);
                    }
                    break;
                case AbstractActionType_Shift :
                    {
                        if (shift != nullptr)
                            delete shift;
                        shift = abstractAction;
                        shift->setOwner(this);
                    }
                    break;
                case AbstractActionType_Alphabetizer :
                    {
                        if (alphabetizer != nullptr)
                            delete alphabetizer;
                        alphabetizer = abstractAction;
                        alphabetizer->setOwner(this);
                    }
                    break;
                default:
                    break;
            }
            return true;
        }
        virtual void * getData() = 0;
        virtual void call() = 0;
};

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
            auto listBegin = originData.begin();
            auto listEnd = originData.end();
            for (auto element = listBegin; element !=listEnd; element++)
                delete *element;
            originData.clear();
        }
};

class BlackBoard : public AbstractBlackboard
{
    public:
        std::list<SetenceData*> allData;
    public:
        BlackBoard() : AbstractBlackboard()
        {
            allData.clear();
        }
        ~BlackBoard()
        {
            allData.clear();
        }
        void * getData()
        {
            return &allData;
        }
        void call()
        {
        }
};

class ShiftAction : public AbstractAction
{
    public:
        ShiftAction() : AbstractAction()
        {
        }
        ~ShiftAction()
        {
        }
        void shift()
        {
            std::cout << "function   shift" << std::endl;
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);
            if (bb == nullptr)
            {
                std::cout << "shift   bb   ======    nullptr" << std::endl;
                return;
            }

            std::cout << "shift   bb   !=====    nullptr" << std::endl;
            auto allDataBegin = bb->allData.begin();
            auto allDataEnd = bb->allData.end();

            for (auto temp = allDataBegin; temp != allDataEnd; temp++)
            {
                SetenceData * tempSetenceData = *temp;
                if (tempSetenceData == nullptr || tempSetenceData->originData.empty())
                {
                    std::cout << "tempSetenceData == null or tempSetenceData->originData.empty() == true" << std::endl;
                    continue;
                }

                int index = 1;
                int length = tempSetenceData->originData.size();
                for ( ; index <= length; index++)
                {
                    std::list<std::string*>::iterator copyBegin;
                    std::list<std::string*>::iterator copyEnd;
                    copyBegin = tempSetenceData->shiftData[index-1].begin();
                    copyEnd = tempSetenceData->shiftData[index-1].end();
                    if (index == 1)
                    {
                        copyBegin = tempSetenceData->originData.begin();
                        copyEnd = tempSetenceData->originData.end();
                    }

                    std::list<std::string*> tempList;
                    tempList.clear();

                    for (auto tempString = copyBegin; tempString != copyEnd; tempString++)
                    {
                        tempList.push_back(*tempString);
                        std::cout << "index   ===    " << index << std::endl;
                        std::cout << "string   ===   " << **tempString << std::endl;
                    }

                    if (index == 1)
                    {
                        std::string * copyString = *tempList.begin();
                        tempList.erase(tempList.begin());
                        tempList.push_back(copyString);
                    }
                }
            }
        }
        void fire()
        {
            std::cout << "shift   =====     start-----------------------      =========" << std::endl;
            shift();
            std::cout << "shift   =====     end-------------------------      =========" << std::endl;
        }
};

class OutputAction : public AbstractAction
{
    public:
        OutputAction()
        {
        }
        ~OutputAction()
        {
        }
        void fire()
        {
            std::cout << "output------=========--------        start" << std::endl;
            //void printAll();
            printOriginData();
            std::cout << "output------=========--------          end" << std::endl;
        }

        void printAll()
        {
            printAllShiftSetence();
            printAllSortSetence();
        }

        void printOriginData()
        {
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);
            if (bb == nullptr)
                return;

            auto allDataBegin = bb->allData.begin();
            auto allDataEnd = bb->allData.end();

            for (auto temp = allDataBegin; temp != allDataEnd; temp++)
                printOneOriginData(*temp);
        }

        void printOneOriginData(SetenceData * tempSetenceData)
        {
            if (tempSetenceData == nullptr)
                return;

            std::string result("");
            spliteString(&result, tempSetenceData->originData);
            printOneString(&result);
        }

        void printOneShiftSetence(SetenceData * tempSetenceData)
        {
            if (tempSetenceData == nullptr)
                return;

            auto shiftBegin = tempSetenceData->shiftData.begin();
            auto shiftEnd = tempSetenceData->shiftData.end();

            for (auto temp = shiftBegin; temp != shiftEnd; temp++)
            {
                std::string result("");
                spliteString(&result, temp->second);
                printOneString(&result);
            }
        }

        void printAllShiftSetence()
        {
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);
            if (bb == nullptr)
                return;

            auto allDataBegin = bb->allData.begin();
            auto allDataEnd = bb->allData.end();

            for (auto temp = allDataBegin; temp != allDataEnd; temp++)
                printOneShiftSetence(*temp);
        }

        void printOneSortSetence(SetenceData *tempSetenceData, int index)
        {
            if (tempSetenceData == nullptr)
                return;

            int max = tempSetenceData->sortData.size();
            if (index <= 0 && index > max)
                return;

            std::string result("");
            spliteString(&result, tempSetenceData->shiftData[index]);
            printOneString(&result);
        }

        void printOneAllSortSetence(SetenceData *tempSetenceData)
        {
            if (tempSetenceData == nullptr)
                return;

            int max = tempSetenceData->sortData.size();
            for (int index = 1; index <= max; index++)
                printOneSortSetence(tempSetenceData, index);
        }

        void printAllSortSetence()
        {
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);
            if (bb == nullptr)
                return;

            auto allDataBegin = bb->allData.begin();
            auto allDataEnd = bb->allData.end();

            for (auto temp = allDataBegin; temp != allDataEnd; temp++)
                printOneAllSortSetence(*temp);
        }

        void spliteString(std::string * result, std::list<std::string*> list)
        {
            auto listBegin = list.begin();
            auto listEnd = list.end();

            for (auto temp = listBegin; temp != listEnd; temp++)
            {
                result->append(**temp);
                if (temp != list.cend())
                    result->append(" ");
            }
        }

        void printOneString(std::string * oneString)
        {
            std::cout << *oneString << std::endl;
        }
};

class SortAction : public AbstractAction
{
    private:
        std::map<char, std::vector<int> > letterMap;
    public:
        SortAction()
        {
            buildLetterMap();
        }

        ~SortAction()
        {
            clearLetterMap();
        }

        bool buildLetterMap()
        {
            char letter = 'A';

            for (int i = 0; i < 26; i++)
            {
                std::vector<int> tempVector;
                letterMap.insert(std::pair<char,std::vector<int> >(letter, tempVector));
            }

            return true;
        }

        void clearLetterMap()
        {
            auto letterMapBegin = letterMap.begin();
            auto letterMapEnd = letterMap.end();

            for (auto temMap = letterMapBegin; temMap != letterMapEnd; temMap++)
                temMap->second.clear();
            letterMap.clear();
        }

        void fire()
        {
            std::cout << "sort============               ====================start" << std::endl;
            sort();
            std::cout << "sort============               ======================end" << std::endl;
        }

        void sort()
        {
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);
            if (bb == nullptr)
                return;

            auto allDataBegin = bb->allData.begin();
            auto allDataEnd = bb->allData.end();

            for (auto temp = allDataBegin; temp != allDataEnd; temp++)
                sortOneSetence(*temp);
        }

        void sortOneSetence(SetenceData * tempSetenceData)
        {
            if (tempSetenceData == nullptr)
                return;
            if (tempSetenceData->originData.empty())
                return;

            int index = 1;
            char letter = 'A';
            auto originBegin = tempSetenceData->originData.begin();
            auto originEnd = tempSetenceData->originData.end();

            for (auto temp = originBegin; temp != originEnd; temp++)
            {
                char tempChar = (**temp)[0];
                tempChar = (tempChar >= 'A' && tempChar <= 'Z') ? tempChar : (tempChar-32);
                letterMap[tempChar].insert(letterMap[tempChar].end(), index++);
            }

            for (int i = 0; i < 26; i++)
            {
                std::vector<int> tempVector = letterMap[letter++];

                if (tempVector.empty())
                    continue;

                for (unsigned long j = 1; j <= tempVector.size(); j++)
                    tempSetenceData->sortData.insert(tempSetenceData->sortData.end(), tempVector[j]);
            }

            clearLetterMap();
            buildLetterMap();
        }
};

class InputAction : public AbstractAction
{
    private:
        enum StringSplitError
        {
            StringSplitError_Success,
            StringSplitError_NoSetenceData,
            StringSplitError_NoBuffer,
            StringSplitError_NoOriginList,
        };
        std::list<std::string *> fileNameList;
    public:
        InputAction()
        {
            fileNameList.clear();
        }
        ~InputAction()
        {
            if (!fileNameList.empty())
            {
                auto listBegin = fileNameList.begin();
                auto listEnd = fileNameList.end();

                for (auto temp = listBegin; temp != listEnd; temp++)
                    delete *temp;
            }
            fileNameList.clear();
        }

        void fire()
        {
            std::cout << "input start------------------" << std::endl;
            readAllFilesName();

            auto listBegin = fileNameList.begin();
            auto listEnd = fileNameList.end();

            for (auto temp = listBegin; temp != listEnd; temp++)
                readOneFileByName(*temp);
            std::cout << "input end--------------------" << std::endl;
        }

        void readAllFilesName()
        {
            std::string path = "data";
            DIR * dir;
            struct dirent *ent;

            if ((dir = opendir(path.c_str())) == nullptr)
                return ;

            while ((ent = readdir (dir)) != nullptr) {
                std::string * s = nullptr;
                if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,".."))
                    continue;
                s = new std::string("data/");
                s->append(ent->d_name);
                fileNameList.push_back(s);
            }
            closedir(dir);
        }

        bool readOneFileByName(std::string * fileName)
        {
            BlackBoard * bb = dynamic_cast<BlackBoard*>(owner);

            if (fileName == nullptr)
                return false;
            if (bb == nullptr)
                return false;

            long lineno = 1;
            std::ifstream infile;
            infile.open(fileName->c_str(), std::ios::in);

            if (!infile.is_open())
                return false;

            while (!infile.eof())
            {
                int errNo = 0;
                std::string buffer;
                SetenceData * tempSetenceData = new SetenceData();
                getline(infile, buffer);
                errNo = stringSplit(tempSetenceData, &buffer);
                explainSplitErrorNo(errNo, lineno++);
                if (errNo == 0)
                    bb->allData.push_back(tempSetenceData);
            }

            infile.close();

            return true;
        }

        int stringSplit(SetenceData * tempSetenceData, std::string * buffer)
        {
            std::cout << "buffer   ===    " << *buffer << std::endl;
            if (tempSetenceData == nullptr)
                return StringSplitError_NoSetenceData;
            if (buffer == nullptr)
                return StringSplitError_NoBuffer;
            if (!tempSetenceData->originData.empty())
                return StringSplitError_NoOriginList;

            int index = buffer->size();

            while(index)
            {
                int oneWorldLastIndex = 0;
                int oneWorldFirstIndex = 0;

                while (1)
                {
                    if (isalpha((*buffer)[index]) && index >= 0)
                    {
                        oneWorldLastIndex = index;
                        break;
                    } else index--;
                }

                while (1)
                {
                    if (!isalpha((*buffer)[index]))
                    {
                        oneWorldFirstIndex = index+1;
                        break;
                    } else {
                        if (index == 0)
                        {
                            oneWorldFirstIndex = index;
                            break;
                        }
                        else
                            index--;
                    }
                }

                if (oneWorldLastIndex > oneWorldFirstIndex)
                {
                    std::string * s = new std::string(buffer->substr(oneWorldFirstIndex, oneWorldLastIndex - oneWorldFirstIndex + 1));
                    tempSetenceData->originData.push_back(s);
                }
            }
            return StringSplitError_Success;
        }

        void explainSplitErrorNo(int errNo, long lineno)
        {
            std::cout << "第" << lineno << "行, ";
            switch (errNo)
            {
                case StringSplitError_Success :
                    std::cout << "分割成功! " << std::endl;
                    break;
                case StringSplitError_NoSetenceData :
                    std::cout << "出错, SetenceData 为空! " << std::endl;
                    break;
                case StringSplitError_NoBuffer :
                    std::cout << "出错, buffer 为空! " << std::endl;
                    break;
                case StringSplitError_NoOriginList :
                    std::cout << "出错, originList 不存在! " << std::endl;
                    break;
                default:
                    break;
            }
        }
};

#endif
