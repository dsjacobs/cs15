/*
 * Editor.h
 *
 * CS15 Proj 2: Typewriter
 * 
 * The Editor class can either make a new file or open an existing file,
 * and allows the user to insert characters, use backspace and enter keys,
 * undo and redo actions, quit and save the file.
 *
 * Author: Danielle Jacobs
 * Date: November 3, 2025
 */

#include "TextUI.h"
#include "ActionStack.h"
#include <string>
#include <vector>

 class Editor {
    public:
        Editor(std::string text_fname);
        Editor(std::string filename, std::string logfile);
        ~Editor();
        void run();
      
    private:
        std::string text_filename;
        std::vector<std::string> curTextLines;
        size_t cursorCol;
        size_t cursorLine;
        bool end;
        TextUI UI;
        size_t numLines;

        ActionStack undoStack;
        ActionStack redoStack; 

        void constructor_helper(std::string filename);
        std::ifstream read_text_file(std::ifstream &text_file);
        std::ifstream read_file_open_stream(std::string text_file);

        void add_logfile(std::string log_filename);
        void determine_next(int c);
        void determine_next_arrow_keys(int c);

        void move_down();
        void move_up();
        void move_right();
        void move_left();

        void type_char(int c, int line, int col);
        void insert(int c, int line, int col);
       
        void backspace();
        void delete_char(size_t line, size_t col);
        void enter_key();
        void insert_new_line(size_t line);
        void delete_new_line(size_t line);

        void command_mode();
        void command_save();
        void command_quit();
        void command_undo();
        void undo_new_line(int line, int col, bool deleted);
        void undo_character(char c, int line, int col, bool deleted);
        void command_redo();

        std::string pre_character(int col, int row);
        std::string post_character(int col, int row);
        size_t lineLength(int line);
        std::ofstream open_file_output_stream(std::string filename);
 };
