#include <iostream>
#include <time.h>


#include "blackground.h"

int main()
{
    clock_t start,end;
    BlackBoard * bb = new BlackBoard();
    InputAction * input = new InputAction();
    OutputAction * output = new OutputAction();
    ShiftAction * shift = new ShiftAction();
    SortAction * sort = new SortAction();

    bb->setAbstractActionByType(AbstractActionType_Input, input);
    bb->setAbstractActionByType(AbstractActionType_Output, output);
    bb->setAbstractActionByType(AbstractActionType_Shift, shift);
    bb->setAbstractActionByType(AbstractActionType_Alphabetizer, sort);

    input->setOwner(bb);
    output->setOwner(bb);
    shift->setOwner(bb);
    sort->setOwner(bb);

    start = clock();
/*    input->fire();
    shift->fire();
    sort->fire();
    output->fire();*/
    bb->call();
    end = clock();
    std::cout << "运行时间为: " << end-start << "ms" <<std::endl;

    return 0;
}
