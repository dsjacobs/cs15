/*
 * Editor.h
 *
 * CS15 Proj 2: Typewriter
 * 
 * TODO: Purpose
 *
 * Author: Danielle Jacobs
 */

 class Editor {
    public:
        Editor(string text_fname);
        ~Editor();
        std::ifstream read_text_file(ifstream &text_file);
    private:
 }