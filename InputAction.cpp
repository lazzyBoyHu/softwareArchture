#include <iostream>
#include <fstream>
#include <dirent.h>
#include <assert.h>


#include "InputAction.h"


InputAction::InputAction(int type, AbstractBlackboard * owner) : AbstractAction(type, owner)
{
    fileNameList.clear();
}

InputAction::~InputAction()
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

void InputAction::doAction()
{
    readAllFile();
}

void InputAction::readAllFile()
{
    auto listBegin = fileNameList.begin();
    auto listEnd = fileNameList.end();

    readAllFilesName();

    for (auto temp = listBegin; temp != listEnd; temp++)
        readOneFileByName(*temp);
}

void InputAction::readAllFilesName()
{
    DIR * dir;
    struct dirent *ent;

    assert((dir = opendir(RESOURCE_PATH)) != nullptr);
    while ((ent = readdir (dir)) != nullptr) {
        if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,".."))
            continue;

        std::string * s = new std::string("data/");
        s->append(ent->d_name);
        fileNameList.push_back(s);
    }
    closedir(dir);
}

bool InputAction::readOneFileByName(std::string * fileName)
{
    BlackBoard * bb = dynamic_cast<BlackBoard*>(m_owner);
    long lineno = 1;
    std::ifstream infile;

    if (fileName == nullptr)
        return false;
    if (bb == nullptr)
        return false;

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

int InputAction::stringSplit(SetenceData * tempSetenceData, std::string * buffer)
{
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
            oneWorldLastIndex = index;

            if (isalpha((*buffer)[index]) && index >= 0)
                break;
            index--;
        }

        while (1)
        {
            oneWorldFirstIndex = index+1;

            if (!isalpha((*buffer)[index]))
                break;
            if (--oneWorldFirstIndex == 0)
                break;
            index--;
        }

        if (oneWorldLastIndex > oneWorldFirstIndex)
        {
            std::string * s = new std::string(buffer->substr(oneWorldFirstIndex, oneWorldLastIndex - oneWorldFirstIndex + 1));
            tempSetenceData->originData.push_back(s);
        }
    }
    return StringSplitError_Success;
}

void InputAction::explainSplitErrorNo(int errNo, long lineno)
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


