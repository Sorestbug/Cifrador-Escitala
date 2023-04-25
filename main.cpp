#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <locale.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

string Cifrado(string entrada) {
    string cifrado = entrada;
    int tam = entrada.size();
    int radio;
    int largo;
    int i, j, k;

    cout << "Ingrese el radio del tubo" << endl;
    cin >> radio;

    if (tam % radio == 0) {
        largo = tam / radio;
    }
    else {
        largo = (tam / radio) + 1;
    }

    k = 0;
    //Declara la Matriz
    char** matriz = new char* [radio];
    for (int i = 0; i < radio; i++) {
        matriz[i] = new char[largo];
    }

    //Guarda la Matriz
    for (i = 0; i < largo; i++) {
        for (j = 0; j < radio; j++) {
            if (k < tam) {
                matriz[j][i] = entrada[k];
                k++;
            }
        }
    }

    //Escribe el mensaje cifrado
    k = 0;
    cout << " " << endl;
    for (int i = 0; i < radio; i++) {
        for (int j = 0; j < largo; j++) {
            if (k < tam) {
                cifrado[k] = matriz[i][j];
                k++;
            }
        }
    }

    //Liberar Memoria
    for (int i = 0; i < radio; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return cifrado;
}

string Descifrado(string entrada) {
    string descifrado = entrada;
    int tam = entrada.size();
    int radio;
    int largo;
    int i, j, k;

    cout << "Ingrese el radio del tubo" << endl;
    cin >> radio;

    if (tam % radio == 0) {
        largo = tam / radio;
    }
    else {
        largo = (tam / radio) + 1;
    }

    k = 0;
    //Declara la matriz
    char** matriz = new char* [radio];
    for (int i = 0; i < radio; i++) {
        matriz[i] = new char[largo];
    }

    //Guarda el contenido en una matriz
    for (i = 0; i < radio; i++) {
        for (j = 0; j < largo; j++) {
            if (k < tam) {
                matriz[i][j] = entrada[k];
                k++;
            }
        }
    }

    //Escribe el mensaje Descifrado
    k = 0;
    cout << " " << endl;
    for (int i = 0; i < largo; i++) {
        for (int j = 0; j < radio; j++) {
            if (k < tam) {
                descifrado[k] = matriz[j][i];
                k++;
            }
        }
    }

    //Liberar Memoria
    for (int i = 0; i < radio; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return descifrado;
}


string LeerArchivo() {
    std::ifstream archivo("Principito.txt");
    std::string contenido;
    char c;

    if (archivo.is_open()) {
        while (archivo.get(c)) {
            contenido += c;
        }
        archivo.close();
    }
    else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    return contenido;
}

string LeerCifrado() {
    std::ifstream archivo("Cifrado.txt");
    std::string contenido;
    char c;

    if (archivo.is_open()) {
        while (archivo.get(c)) {
            contenido += c;
        }
        archivo.close();
    }
    else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    return contenido;
}

string LeerImagen() {

    // Lee la imagen
    Mat image = imread("Chiza.jpg");

    if (image.empty()) {
        cout << "Error al leer la imagen" << endl;
    }

    // Obtiene la matriz RGB
    Mat rgb;
    cvtColor(image, rgb, COLOR_BGR2RGB);

    // Guarda la matriz RGB en un archivo de texto
    ofstream outfile;
    outfile.open("matriz_rgb.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < rgb.rows; i++) {
            for (int j = 0; j < rgb.cols; j++) {
                outfile << (int)rgb.at<Vec3b>(i, j)[0] << " ";
                outfile << (int)rgb.at<Vec3b>(i, j)[1] << " ";
                outfile << (int)rgb.at<Vec3b>(i, j)[2] << " ";
            }
            outfile << endl;
        }
        outfile.close();
    }
    else {
        cout << "Error al abrir el archivo de texto" << endl;
    }


    std::ifstream archivo("matriz_rgb.txt");
    std::string contenido;
    char c;

    if (archivo.is_open()) {
        while (archivo.get(c)) {
            contenido += c;
        }

        archivo.close();
    }
    else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    return contenido;
}

string LeerImagenCifrada() {

    std::ifstream archivo("MatrizCifrada.txt");
    std::string contenido;
    char c;

    if (archivo.is_open()) {
        while (archivo.get(c)) {

            contenido += c;
        }

        archivo.close();
    }
    else {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }

    return contenido;
}

void CrearCifrado(string Contenido) {

    ofstream archivo("Cifrado.txt");

    if (archivo.is_open()) {
        archivo << Contenido;
        archivo.close();
        cout << "Se guardó la información en el archivo." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void MostrarImagen() {
    // Lee la matriz RGB del archivo de texto
    Mat image = imread("Chiza.jpg");
    ifstream infile("MatrizDescifrada.txt");
    Mat rgb2(image.size(), CV_8UC3);

    if (infile.is_open()) {
        for (int i = 0; i < rgb2.rows; i++) {
            for (int j = 0; j < rgb2.cols; j++) {
                int r, g, b;
                infile >> r >> g >> b;
                rgb2.at<Vec3b>(i, j)[0] = (uchar)r;
                rgb2.at<Vec3b>(i, j)[1] = (uchar)g;
                rgb2.at<Vec3b>(i, j)[2] = (uchar)b;
            }
        }
        infile.close();
    }
    else {
        cout << "Error al abrir el archivo de texto" << endl;
    }

    // Muestra la imagen
    Mat bgr;
    cvtColor(rgb2, bgr, COLOR_RGB2BGR);
    imshow("Imagen", bgr);
    waitKey(0);

}

void CrearDescifrado(string Contenido) {

    ofstream archivo("Descifrado.txt");

    if (archivo.is_open()) {
        archivo << Contenido;
        archivo.close();
        cout << "Se guardó la información en el archivo." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void CrearCifradoImagen(string Contenido) {

    ofstream archivo("MatrizCifrada.txt");

    if (archivo.is_open()) {
        archivo << Contenido;
        archivo.close();
        cout << "Se guardó la información en el archivo." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}

void CrearDescifradoImagen(string Contenido) {

    ofstream archivo("MatrizDescifrada.txt");

    if (archivo.is_open()) {
        archivo << Contenido;
        archivo.close();
        cout << "Se guardó la información en el archivo." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }

}



int main() {
    setlocale(LC_CTYPE, "Spanish");
    int opcion;
    string Entrada = "Viví así, solo, nadie con quien poder hablar verdaderamente, hasta cuando hace seis años tuve una avería en el desierto de Sahara. Algo se había estropeado en el motor. Como no llevaba conmigo ni mecánico ni pasajero alguno, me dispuse a realizar, yo solo, una reparación difícil. Era para mí una cuestión de vida o muerte, pues apenas tenía agua de beber para ocho días. La primera noche me dormí sobre la arena, a unas mil millas de distancia del lugar habitado más próximo. Estaba más aislado que un náufrago en una balsa en medio del océano. Imagínense, pues, mi sorpresa cuando al amanecer me despertó una extraña vocecita que decía: ";
    string Salida;
    string EntradaAux;
    int tam;

    do { //Menu
        cout << "Programa de Cifrado Escitala" << endl;
        cout << "----------------------\n";
        cout << " 1. Lectura y Cifrado desde Teclado\n";
        cout << " 2. Lectura y Cifrado desde Archivo\n";
        cout << " 3. Lectura y Cifrado desde Imagen\n";
        cout << " 4. Descifrado desde Teclado\n";
        cout << " 5. Descifrado desde Archivo\n";
        cout << " 6. Descifrado desde Imagen\n";
        cout << " 7. Salir\n";
        cout << "---------------------\n";
        cout << "Elige una opcion:";
        cin >> opcion;
        switch (opcion) {
        case 1: //Lectura y Cifrado desde Teclado
            fflush(stdin);
            //cout<<"Ingrese Texto para cifrar"<<endl;
            //getline(cin,Entrada);
            Salida = Cifrado(Entrada);
            cout << "El Texto Cifrado es: " << endl;
            cout << Salida << endl;
            EntradaAux = Salida;
            break;

        case 2: //Lectura y Cifrado desde Archivo
            fflush(stdin);
            Entrada = LeerArchivo();
            Salida = Cifrado(Entrada);
            CrearCifrado(Salida);
            break;
        case 3: //Lectura y Cifrado desde Imagen
            fflush(stdin);
            Entrada = LeerImagen();
            Salida = Cifrado(Entrada);
            CrearCifradoImagen(Salida);
            break;
        case 4: //Descifrado desde Teclado
            fflush(stdin);
            //cout<<"Ingrese Texto para descifrar"<<endl;
            //getline(cin,Entrada);
            Salida = Descifrado(EntradaAux);
            //Salida = descifrado(Entrada);
            cout << "El Texto Descifrado es: " << endl;
            cout << Salida << endl;
            break;
        case 5: //Descifrado desde Archivo
            fflush(stdin);
            Entrada = LeerCifrado();
            Salida = Descifrado(Entrada);
            CrearDescifrado(Salida);
            break;
        case 6: //Descifrado desde Imagen
            fflush(stdin);
            Entrada = LeerImagenCifrada();
            Salida = Descifrado(Entrada);
            CrearDescifradoImagen(Salida);
            MostrarImagen();
            break;
        default: cout << "Opcion no valida\n";
            break;
        }
        system("pause");
        system("cls");
    } while (opcion != 7); //Termina el programa
    return 1;
}