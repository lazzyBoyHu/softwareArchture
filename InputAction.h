#ifndef INPUTACTION_H_
#define INPUTACTION_H_

#include <list>


#include "AbstractAction.h"
#include "SetenceData.h"


#define RESOURCE_PATH "data"

enum StringSplitError
{
    StringSplitError_Success,
    StringSplitError_NoSetenceData,
    StringSplitError_NoBuffer,
    StringSplitError_NoOriginList,
};

class InputAction : public AbstractAction
{
    private:
        std::list<std::string *> fileNameList;
    public:
        /**
         * 构造
         */
        InputAction(int type, AbstractBlackboard * owner);
        /**
         * 析构
         */
        ~InputAction();
        /**
         * 虚函数的实现
         */
        void doAction();
    private:
        /**
         * 读取文件夹中所有的文件
         */
        void readAllFile();
        /**
         * 读取所有的资源文件的名称
         * 解析时, 将数据解析完成时, 会将这些保存在 fileNameList 中
         */
        void readAllFilesName();
        /**
         * 根据文件名读取一个文件
         */
        bool readOneFileByName(std::string * fileName);
        /**
         * 分割字符串
         */
        int stringSplit(SetenceData * tempSetenceData, std::string * buffer);
        /**
         * 解析错误码
         */
        void explainSplitErrorNo(int errNo, long lineno);
};

#endif


