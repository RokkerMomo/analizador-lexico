//INCLUIR LIBRERIAS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <cstdlib>
#include <string>
using namespace std;

//Variables
string output = "TOKEN\tLEXENA\n";
string checkspace = "";
string palabra = "";
string caracter = "";
int saltar = 1;
int salir = 1;

//funcion para comprobar numeros de mas de un digito
bool isNumber(const string& s)
{
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

//Codigo que se va a compilar
string codigo = "VARIABLES variable1=25. variable2=30. variable3=84. BEGIN resultado=variable1/( variable2*variable3 ). END";

//inicio
int main(){
    //Abrir Archivo
    FILE * file = fopen("output.txt", "w+");
    //cargar codigo
    std::string str = codigo;

    //LEE CADA DIGITO DEL CODIGO
for(std::string::size_type i = 0; i < str.size(); ++i) {
    //variable para revisar el siguiente caracter
    checkspace = str[i+1];
    //variable para revisar el caracter actual
    caracter = str[i];

    //revisa si ya termino la palabra o si el caracter actual es un operador
    if (checkspace == " " || str[i] == str.back() || checkspace == "=" || checkspace == "+" || checkspace == "^" || checkspace == "-" || checkspace == "*" || checkspace == "/" || checkspace == "." || caracter == "=" || caracter == "+" || caracter == "^" || caracter == "-" || caracter == "*" || caracter == "/" || caracter == ".")
    {
        //variable de salto
        saltar = 1;

        //el "output" es lo que se escribe en el archivo
        output += str[i];
        //la "palabra" es el token que se va a evaluar
        palabra += str[i];
        
        
        //revisa si el siguiente caracter es un operador para no realizar el salto
        if (checkspace == "=" || checkspace == "+" || checkspace == "^" || checkspace == "-" || checkspace == "*" || checkspace == "/" || checkspace == "." || caracter == "=" || caracter == "+" || caracter == "^" || caracter == "-" || caracter == "*" || caracter == "/")
        {
            saltar=0; 
        }
        caracter= "";

 //verifica la palabra leida
        if (palabra == "BEGIN" || palabra == "END" || palabra == "VARIABLES")
        {
            output += '\t';
            output += "PR";
            palabra = "";
        }else{
            if (palabra == ".")
        {
            output += '\t';
            output += "Finalizador";
            palabra = "";
        }else{
            if (palabra == "=")
        {
            output += '\t';
            output += "Asignacion";
            palabra = "";
        }else{
            if (palabra == "+" || palabra == "-" || palabra == "/" || palabra == "*" || palabra == "^")
        {
            output += '\t';
            output += "OP_Airmetico";
            palabra = "";
        }else{
            if (palabra == "(" || palabra == ")")
        {
            output += '\t';
            output += "Agrupador";
            palabra = "";
        }else{
            if (palabra == "0" || palabra == "1" || palabra == "2" || palabra == "3" || palabra == "4" || palabra == "5" || palabra == "6" || palabra == "7" || palabra == "8"|| palabra == "9")
        {
            output += '\t';
            output += "NUM";
            palabra = "";
        }else{
            //comprueba si la palabra es un numero
            if (isNumber(palabra))
            {
            output += '\t';
            output += "NUM";
            palabra = "";

            //si no es un numero es un IDEN
            }else
            {
            output += '\t';
            output += "IDEN";
            palabra = "";
            }
            
            
            
        }}}}}}

        //realiza el salto de linea
        output += "\n";
        //se limpia el valor de la palabra
        palabra = "";
        //verifica si hay que realizar un salto
        if (saltar == 1)
        {
            saltar=1;
            i++;
        }
        
        
    }else{
        //añade caracter a la palabra
        palabra += str[i];
        //y al output
        output += str[i];
    }
    
}

//MOSTRAR RESULTADO
printf("%s", output);
 
//SOBREESCRIBE EL ARCHIVO
fwrite(output.data(), sizeof(char), output.size(), file);

}