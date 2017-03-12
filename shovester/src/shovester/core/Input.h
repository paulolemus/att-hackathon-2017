#ifndef SHOVESTER_CORE_INPUT_H
#define SHOVESTER_CORE_INPUT_H

template <typename InputFormat, typename OutputFormat>
class Input {
    virtual void handle(InputFormat inputFormat) = 0;

    OutputFormat outputFormat; 
};

#endif // SHOVESTER_CORE_INPUT_H
