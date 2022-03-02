#ifndef PRESENTHANDLER_H_INCLUDED
#define PRESENTHANDLER_H_INCLUDED

#include <string>
class presenthandler //Класс для управления наглядным представлением шагов, совершаемых внутри функций и прочих.
{
private:
    int CurrentFileNumber=0; //Количество уже сгенерированных файлов.
public:
    int Mode=0; //0 -не влиять на выполнение вызывающей функции; 1 -выводить шаги в командную строку; 2 -выводить шаги в файл(ы)
    
    std::string GetFileNumberAndIncrease()
    {
        CurrentFileNumber++;
        return std::to_string(CurrentFileNumber);
    }
    void ResetFileNumber()
    {
        CurrentFileNumber=0;
    }
};



#endif //PRESENTHANDLER_H_INCLUDED