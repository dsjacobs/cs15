/*
gerp.h
November 22, 2025
Project 3, gerp
Danielle Jacobs

*/
#include <string>
#include <fstream> 

class gerp {
    public:
        gerp(std::string input_directory, std::string output_file);
        ~gerp();
        void run();
        void new_output_file(std::string filename);
        void search(std::string search_string);
        void insensitive_search(std::string search_string);
    private:
        bool has_quit;
        std::string output_file;
        std::string input_directory;
        std::ofstream output_stream;

        std::ofstream create_ofstream(std::string filename, bool first);
        std::string request_input();
        void determine_word(std::string input);
        void route_cmd(std::string input);
        void quit();
};