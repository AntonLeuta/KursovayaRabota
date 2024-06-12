#include "myfunc.h" 

int main()
{
    system("color F0");
    std::map<std::string, std::vector<int>> arrays;
    std::fstream instr("instruction.txt");
    std::string line;
    std::string name;
    std::string name2;
    try
    {
        if (instr.is_open())
        {
            while (std::getline(instr, line))
            {
                std::transform(line.begin(), line.end(), line.begin(), ::toupper);

                if (getWord(line, 0) == "Load")
                {
                    Load(name, line, arrays);
                }
                if (getWord(line, 0) == "Save")
                {
                    Save(name, line, arrays);
                }
                if (getWord(line, 0) == "Rand")
                {
                    Rand(name, line, arrays);
                }
                if (getWord(line, 0) == "Concat")
                {
                    Concat(name, name2, line, arrays);
                }
                if (getWord(line, 0)[0] == 'F')
                {
                    Free(name, line, arrays);
                }
                if (getWord(line, 0) == "Remove")
                {
                    Remove(name, line, arrays);
                }
                if (getWord(line, 0) == "Copy")
                {
                    Copy(name, name2, line, arrays);
                }
                if (getWord(line, 0) == "Sort")
                {
                    Sort(name, line, arrays);
                }
                if (getWord(line, 0) == "Permute")
                {
                    Permute(name, line, arrays);
                }
                if (getWord(line, 0) == "Print" && getWord(line, 2) != "All;")
                {
                    Print_from_to(name, line, arrays);
                }
                if (getWord(line, 0) == "Intersect")
                {
                    Intersect(name, name2, line, arrays);
                }
                if (getWord(line, 0) == "Stat")
                {
                    Stat(name, line, arrays);
                }
                if (getWord(line, 0) == "Print" && getWord(line, 2) == "All;")
                {
                    Print_all(name, line, arrays);
                }
                if (getWord(line, 0) == "Xor")
                {
                    Xor(name, name2, line, arrays);
                }
            }
        }
        else
        {
            throw std::logic_error("ERROR: File is not open");
        }

        instr.close();
    }
    catch (std::logic_error const& ex)
    {
        std::cout << ex.what();
        return 1;
    }


    return 0;
}
