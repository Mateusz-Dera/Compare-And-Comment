//  Compare-And-Comment
//  Copyright © 2022 Mateusz Dera

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>

#include <iostream>
#include <fstream>

using namespace std;

// Version
string version = "2022.03.31";

// Errors
string error_input1_flag       = "Wrong or missing first input file.";
string error_input1_multiple   = "Multiple input values for first file.";
string error_input2_flag       = "Wrong or missing second input file.";
string error_input2_multiple   = "Multiple input values for second file.";
string error_output_flag       = "Wrong or missing output file.";
string error_output_create     = "Can not create or write to output file.";
string error_output_multiple   = "Multiple output values.";
string error_unknown_parameter = "Unknown parameter: ";
string error_comment_flag      = "Wrong or missing value for comment."; 
string error_comment_multiple  = "Multiple input values for comment.";

// Other
string writing_test = "Writing test.";

// Help
string help_title   = "Program adds a comment if a line of text from the first file is also found in the second file.";
string help_help    = "-h     --help      Show help";
string help_version = "-v     --version   Show version";
string help_input1  = "-i1    --input1    First input file";
string help_input2  = "-i2    --input2    Second input file";
string help_output  = "-o     --output    Output file";
string help_comment = "-c     --comment   Comment value";

int get_help(){
    cout 
    << help_title << endl 
    << help_help << endl 
    << help_version << endl 
    << help_input1 << endl 
    << help_input2 << endl 
    << help_output << endl 
    << help_comment << endl; 
    exit(0);
    return 0;
}

int get_version(){
    cout << "Version: " << version << endl;
    exit(0);
    return 0;
}

bool file_exist(char* file)
{
    ifstream f(file);
    return f.good();
}

bool file_writable(char* file)
{
    ofstream f(file);
    f << writing_test << endl;
    return f.good();
}

int main(int argc,char* argv[]){
    bool comment_flag = false;
    bool input1_flag = false;
    bool input2_flag = false;
    bool output_flag = false;

    string input1_name;
    string input2_name;
    string output_name;
    string comment_name;

    for (int a = 1; a < argc; ++a){
        string s = argv[a];
        if(s == "-h" || s == "--help"){
            get_help();
        }
        else if(s == "-v" || s == "--version"){
            get_version();
        }
        else if(s == "-i1" || s == "--input1"){
            if(input1_flag == true){
                cout << error_input1_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                if(file_exist(argv[a])){
                    input1_name = argv[a];
                    input1_flag = true;
                }
                else{
                    cout << error_input1_flag << endl;
                    exit(1);
                    return 1;
                }
            }
            else{
                cout << error_input1_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-i2" || s == "--input2"){
            if(input2_flag == true){
                cout << error_input2_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                if(file_exist(argv[a])){
                    input2_name = argv[a];
                    input2_flag = true;
                }
                else{
                    cout << error_input2_flag << endl;
                    exit(1);
                    return 1;
                }
            }
            else{
                cout << error_input2_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-o" || s == "--output"){
            if(output_flag == true){
                cout << error_output_multiple << endl;
                exit(1);
                return 1; 
            }
            a = a + 1;
            if(a < argc){
                if(file_writable(argv[a])){
                    output_name = argv[a];
                    output_flag = true;
                }
                else{
                    cout << error_output_create << endl;
                    exit(1);
                    return 1;
                }
            }
            else{
                cout << error_output_flag << endl;
                exit(1);
                return 1;
            }
        }
        else if(s == "-c" || s == "--comment"){
            if(comment_flag == true){
                cout << error_comment_multiple << endl;
                exit(1);
                return 1; 
            }else{
                a = a + 1;
                if(a < argc){
                    comment_name = argv[a];
                    comment_flag = true;
                }
                else{
                    cout << error_comment_flag << endl;
                    exit(1);
                    return 1;
                }
            }
        }
        else{
            cout << error_unknown_parameter << argv[a] << endl;
            exit(1);
            return 1;
        }
    }

    if (input1_flag == false){
        cout << error_input1_flag << endl;
        exit(1);
        return 1;
    }
    
    if (input2_flag == false){
        cout << error_input2_flag << endl;
        exit(1);
        return 1;
    }

    if (output_flag == false){
        cout << error_output_flag << endl;
        exit(1);
        return 1;
    }

    if(comment_flag == true){
        // TODO główna robota
        fstream input1;
        ofstream output;

        input1.open(input1_name, ifstream::in);
        output.open(output_name, ios::trunc);

        string l1;
        string l2;

        while (getline(input1, l1)){
            fstream input2;
            input2.open(input2_name, ifstream::in);

            bool found = false;

            while (getline(input2, l2)){
                if(l1 == l2){
                    found = true;
                    break;
                }
            }

            if(found){
                if(input1.eof()){
                    output << comment_name << l1;
                }
                else{
                    output << comment_name << l1 << endl;
                }
            }
            else{
                if(input1.eof()){
                    output << l1;
                }
                else{
                    output << l1 << endl;
                }
            }

            input2.close();
        }

        input1.close();
        output.close();
    }
    else if( comment_flag == false){
        cout << error_comment_flag << endl;
        exit(1);
        return 1; 
    }
}
