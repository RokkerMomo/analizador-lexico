//INCLUIR LIBRERIAS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <cstdlib>
#include <string>
#include <vector>



using namespace std;

//Variables
string output = "TOKEN\tLEXENA\n";
string checkspace = "";
string palabra = "";
string caracter = "";
std::vector< char > Palabras;
std::vector< int > arr;
std::string words[500];
int wordsi = 0;
int wtf = 0;
int saltar = 1;
bool error = false;
int parentopen = 0;
int parentclose = 0;
bool abrirexp = false;
bool cerrarexp = false;
bool igualdad = false;
int prueba = 0;



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
string codigo = "VARIABLES x=5. y=10. w = 25. BEGIN op = x+(y*w). END";




void red () {
    printf("\033[1;31m");
    }

void reset () {
  printf("\033[0m");
}

void green () {
  printf("\033[0;32m");
}

//inicio
int main(){
    //Abrir Archivo
    FILE * file = fopen("output.txt", "w+");
    //cargar codigo
    std::string str = codigo;

//ANALIZADOR LEXICO
    //LEE CADA DIGITO DEL CODIGO
    
for(std::string::size_type i = 0; i < str.size(); ++i) {
    //variable para revisar el siguiente caracter
    checkspace = str[i+1];
    //variable para revisar el caracter actual
    caracter = str[i];

    //revisa si ya termino la palabra o si el caracter actual es un operador
    if (checkspace == " " || str[i] == str.back() || checkspace == "=" || checkspace == "+" || checkspace == "^" || checkspace == "-" || checkspace == "*" || checkspace == "/" || checkspace == "." || caracter == "=" || caracter == "+" || caracter == "^" || caracter == "-" || caracter == "*" || caracter == "/" || caracter == "." || checkspace == "(" || caracter == "(" || checkspace == ")" || caracter == ")")
    {
        //variable de salto
        saltar = 1;

        //el "output" es lo que se escribe en el archivo
        output += str[i];
        //la "palabra" es el token que se va a evaluar
        palabra += str[i];
        
        
        //revisa si el siguiente caracter es un operador para no realizar el salto
        if (checkspace == "=" || checkspace == "+" || checkspace == "^" || checkspace == "-" || checkspace == "*" || checkspace == "/" || checkspace == "." || caracter == "=" || caracter == "+" || caracter == "^" || caracter == "-" || caracter == "*" || caracter == "/" || checkspace == "(" || caracter == "(" || checkspace == ")" || caracter == ")")
        {
            saltar=0; 
        }
        caracter= "";

 //verifica la palabra leida
 wtf++;
        if (palabra == "BEGIN" || palabra == "END" || palabra == "VARIABLES")
        {
            output += '\t';
            output += "PR";
            words[wordsi]=palabra;
            wordsi++;
            palabra = "";
        }else{
            if (palabra == ".")
        {
            output += '\t';
            output += "Finalizador";
            
            words[wordsi]=palabra;
            wordsi++;
            palabra = "";
        }else{
            if (palabra == "=")
        {
            output += '\t';
            output += "Asignacion";
            
            words[wordsi]=palabra;
            wordsi++;
            palabra = "";
        }else{
            if (palabra == "+" || palabra == "-" || palabra == "/" || palabra == "*" || palabra == "^")
        {
            output += '\t';
            output += "OP_Airmetico";
            
            words[wordsi]=palabra;
            wordsi++;
            palabra = "";
        }else{
            if (palabra == "(" || palabra == ")")
        {
            output += '\t';
            output += "Agrupador";
            
            words[wordsi]=palabra;
            wordsi++;
            palabra = "";
        }else{
            if (palabra == "0" || palabra == "1" || palabra == "2" || palabra == "3" || palabra == "4" || palabra == "5" || palabra == "6" || palabra == "7" || palabra == "8"|| palabra == "9")
        {
            output += '\t';
            output += "NUM";
            
            words[wordsi]="NUM";
            wordsi++;
            palabra = "";
        }else{
            //comprueba si la palabra es un numero
            if (isNumber(palabra))
            {
            output += '\t';
            output += "NUM";
            
            words[wordsi]="NUM";
            wordsi++;
            palabra = "";

            //si no es un numero es un IDEN
            }else
            {
            output += '\t';
            output += "IDEN";
            
            words[wordsi]="IDEN";
            wordsi++;
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
printf("%s \n", output);


//ANALIZADOR SINTACTICO

for (size_t i = 0; i < wtf; i++)
{if (words[i]=="(")
    {parentopen+=1;}
    if (words[i]==")")
    {parentclose+=1;}}


for (size_t i = 0; i < wtf; i++)
{
    // std::cout << words[i] << "\n";


    if (words[i]=="=")
    {
        if (words[i-1]!="IDEN")
        {
            error=true;
                red();
                printf("Error de Sintaxis en la linea %d En el lado izquierdo de una igualdad debe de haber un IDEN. \n", i);
                reset();
                igualdad=false;
        }
        
        igualdad=true;
        for (size_t y = i+1; y < wtf; y++)
        {
                if (words[y]=="."){
               igualdad=false;
               break;
            }else{
            if (words[y]=="="&&igualdad==true)
            {
                error=true;
                red();
                printf("Error de Sintaxis en la linea %d Se espera el uso del finalizador . \n", i);
                reset();
                igualdad=false;
                break;
            }
            }
        }
        if (igualdad==true)
        {
            error=true;
                red();
                printf("Error de Sintaxis en la linea %d Se espera el uso del finalizador . \n", i);
                reset();
        }
        
        // if (words[i+1]=="IDEN"||words[i+1]=="NUM")
        // {
        //     if (words[i+2]==".")
        //     {

        //     }else{
        //     error=true;
        //     red();
        //     printf("Error de Sintaxis en la linea %d Se espera el uso del finalizador . \n", i);
        //     reset();
        //     }
            
        // }
        
    }
    



    if (words[i]=="IDEN")
    {
        
        
        if (words[i+1]!="="&&words[i+1]!="+"&&words[i+1]!="-"&&words[i+1]!="*"&&words[i+1]!="/"&&words[i-1]!="="&&words[i-1]!="+"&&words[i-1]!="-"&&words[i-1]!="*"&&words[i-1]!="/")
        {
            error=true;
            red();
            printf("Error de Sintaxis en la linea %d \n", i);
            reset();
        }
        if (words[i+1]=="IDEN")
        {
            error=true;
            red();
            printf("Error de Sintaxis en la linea %d Hay 2 Identificadores seguidos\n", i);
            reset();
        }
        
    }
    

    if (words[i]=="+"||words[i]=="-"||words[i]=="*"||words[i]=="/")
    {
        if (words[i+1]=="+"||words[i+1]=="-"||words[i+1]=="*"||words[i+1]=="/")
        {
            error=true;
            red();
            printf("Error de Sintaxis en la linea %d Hay 2 operadores seguidos\n", i);
            reset();
        }

        if (words[i+1]!="IDEN" || words[i-1]!="IDEN")
        {
            if (words[i+1]!="IDEN" || words[i-1]!="NUM")
            {
                if (words[i+1]!="NUM" || words[i-1]!="IDEN")
            {
                if (words[i+1]!="NUM" || words[i-1]!="NUM")
            {
            if (words[i+1]!="(" || words[i-1]!="NUM")
            {
            if (words[i+1]!="NUM" || words[i-1]!=")")
            {
            if (words[i+1]!="(" || words[i-1]!="IDEN")
            {
           if (words[i+1]!="IDEN" || words[i-1]!=")")
            {
            error=true;
            red();
            printf("Error de Sintaxis en la linea %d Uso incorrecto del operador\n", i);
            reset();
            }
            }
            }
            }
            }
            }
            }
            
            
        }


        
    }

    if (words[i]=="("|| words[i]==")")
    {
        if (parentopen!=parentclose)
        {
            error=true;
            red();
            printf("Error de Sintaxis en la linea %d No hay la misma cantidad de parentesis abiertos que cerrados\n", i);
            reset();
        }
        
    }
    

    if (words[i]=="END")
    {
        if(words[i+1]==""){
        
        }else{
        error=true;
        red();
        printf("Error en la linea %d No puede haber codigo despues de la palabra reservada END \n", i);
        reset();
        }
        
    }

  
    }
    

      
        

    if (error==false)
    {
        green();
        printf("El Codigo es Valido, ahora sera compilado \n");
        reset();
    }


    
//SOBREESCRIBE EL ARCHIVO
fwrite(output.data(), sizeof(char), output.size(), file);

    
    

    
}


