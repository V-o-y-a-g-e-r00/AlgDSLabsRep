#ifndef PLOTHANDLER_H
#define PLOTHANDLER_H
//Имена файлов, из которых берутся данные для графиков

#include <string>
#include <vector>
#include <fstream>

class plothandler
{
private:
    std::vector<std::string> v;
public:
    std::string addandreturn(std::string filename)
    {
        v.push_back(filename);
        return filename;
    }
    void tofile(std::string filename="Plotfilelist.txt")
    {
        std::ofstream fd(filename);
        fd<<"filename=\t\"";
        for(auto& i: v)
        {
            fd<<i<<" ";
        }
        fd<<"\"";
        fd.close();
    }
};


#endif /* PLOTHANDLER_H */
