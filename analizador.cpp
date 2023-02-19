//INCLUIR LIBRERIAS
#include <iostream>
#include<conio.h>
#include<windows.h>
#include<thread>
#include <cstdlib>
#include <string>

using namespace std;

//Variables
string codigo = "BEGIN a = b + c ^ 9 ; END ";
string output = "";
string checkspace = "";
string palabra = "";



int main(){
    //Abrir Archivo
FILE * file = fopen("output.txt", "w+");
    std::string str = codigo;

    //LEE CADA DIGITO DEL CODIGO
for(std::string::size_type i = 0; i < str.size(); ++i) {
    //REVISA SI EL SIGUIENTE CARACTER ES UN ESPACIO VACIO
    checkspace = str[i+1];
    if (checkspace == " ")
    {
        output += str[i];
        palabra += str[i];
        if (palabra == "BEGIN")
        {
            output += '\t';
            output += "PR";
            palabra = "";
        }else{
            if (palabra == "END")
        {
            output += '\t';
            output += "PR";
            palabra = "";
        }else{
            if (palabra == "=")
        {
            output += '\t';
            output += "Asignacion";
            palabra = "";
        }else{
            if (palabra == "+")
        {
            output += '\t';
            output += "OP_Airmetico";
            palabra = "";
        }else{
            if (palabra == "^")
        {
            output += '\t';
            output += "OP_Airmetico";
            palabra = "";
        }else{
            if (palabra == "0" || palabra == "1" || palabra == "2" || palabra == "3" || palabra == "4" || palabra == "5" || palabra == "6" || palabra == "7" || palabra == "8"|| palabra == "9"  )
        {
            output += '\t';
            output += "NUM";
            palabra = "";
        }else{
            output += '\t';
            output += "IDEN";
            palabra = "";
        }}}}}}

        output += "\n";
        palabra = "";
        i++;
    }else{
        palabra += str[i];
        output += str[i];
    }
    
}

//MOSTRAR RESULTADO
printf("%s", output);
 
//SOBREESCRIBE EL ARCHIVO
fwrite(output.data(), sizeof(char), output.size(), file);



return 0;
}