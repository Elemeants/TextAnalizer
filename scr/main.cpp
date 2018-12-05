/**
    Project: TextAnalizer
    File: main.cpp
    Autor: Jdany
    Version: 1.0
    Date: 2018/10/08
*/
#include "main.h"

const int WIDTH = 100;

void ImprSeparador();
void ImprDatos();

struct FILE_MANAGER
{
    /// Data of the structure
    bool isOpen;
    char* FILENAME;

    /// Functions
    bool Close()
    {
        this->isOpen = fclose(this->dataFile) ? true : false;
        return !this->isOpen;
    }
    bool Open()
    {
        this->isOpen = (this->dataFile = fopen(this->FILENAME, "r"))
                        == NULL ? false : true;
        return this->isOpen;
    }

    void ImprFile()
    {
        if(this->isOpen)
        {
            char buffer[WIDTH - 1] = {0};
            while(fgets(buffer, WIDTH - 1, this->dataFile))
                printf(" %s\n", buffer);
        }
        else
            printf(" - No esta abierto el archivo\n");
    }

    int GetSizeFile()
    {
        int sizeFile = 0;
        if(this->isOpen)
        {
            rewind(this->dataFile);
            int ch;
            while (EOF != (ch = getc(this->dataFile)))
                sizeFile++;
            return sizeFile;
        }
        return 0;
    }

    FILE *dataFile;
    char *GetFilename(){ return this->FILENAME; }

    /// Constructors
    FILE_MANAGER(const char *PATH){ this->FILENAME = (char*)PATH; }
};

FILE_MANAGER TextFile("texto.txt");

int main(void)
{
    ImprSeparador();
    printf(" - Abriendo documento\n");
    if(!TextFile.Open())
    {
        perror(TextFile.GetFilename());
        return EXIT_FAILURE;
    }
    else
    {
        printf(" - Leyendo archivo: \n");
        TextFile.ImprFile();
        ImprSeparador();
        printf(" # DATOS: \n");
        ImprDatos();
        ImprSeparador();
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}

void ImprSeparador()
{
    for(int x = 0; x < WIDTH; x++)
        printf("-");
    printf("\n");
}

void ImprDatos()
{
    if(TextFile.Open())
    {
        /// Control variables
        int whiteSpace = 0;
        int puntosChar = 0;
        int comaChars  = 0;
        int Mayusculas = 0;
        int Numeros    = 0;
        int Vocales    = 0;
        int Consonantes= 0;
        int SaltosLinea= 0;
        /// Searcher
        char buffer[WIDTH - 1] = {0};
        rewind(TextFile.dataFile);
        while(fgets(buffer, WIDTH - 1, TextFile.dataFile))
        {
            for(int x = 0; x < (WIDTH - 1); x++)
            {
                if(isspace(buffer[x]))
                    whiteSpace++;
                if(isdigit(buffer[x]))
                    Numeros++;
                if(buffer[x] == '.')
                    puntosChar++;
                if(buffer[x] == ',')
                    comaChars++;
                if(buffer[x] == '\n')
                    SaltosLinea++;
                if(isupper(buffer[x]))
                    Mayusculas++;
                if(buffer[x] == 'a' || buffer[x] == 'e' ||
                    buffer[x] == 'i' || buffer[x] == 'o' ||
                    buffer[x] == 'u')
                    Vocales++;
                else
                    Consonantes++;
            }
        }
        printf("   -> Tamanio:        %03i Bytes\n", TextFile.GetSizeFile());
        printf("   -> Espacios:       %03i\n", whiteSpace);
        printf("   -> Puntos:         %03i\n", puntosChar);
        printf("   -> Comas:          %03i\n", comaChars);
        printf("   -> Mayusculas:     %03i\n", Mayusculas);
        printf("   -> Numeros:        %03i\n", Numeros);
        printf("   -> Vocales:        %03i\n", Vocales);
        printf("   -> Consonantes:    %03i\n", Consonantes);
        printf("   -> Salto de Linea: %03i\n", SaltosLinea);
    }
}
