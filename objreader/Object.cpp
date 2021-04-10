#include <iostream>
#include <fstream>
#include <string>
#include "Object.hpp"

using namespace std;

/* Extraer de un arreglo los índices del componente v, vt o vn.
    @param tokens Arreglo de strings con los elementos que forman una cara.
    @param pos Número del componente que se quiere extraer.
                0 : v, 1 : vt, 2 : vn
    @return Devuelve un arreglo de valores int con los índices extraídos.
*/
vector<int> Object::ExtractIndexes(vector<string> tokens, int pos = 0)
{
    vector<string> strcomponents; //v, vt, vn
    vector<int> indexes;       //Arreglo de índices que se extraen

    if (pos >= 0 && pos <= 2)
    {
        for (int i = 1; i < tokens.size(); i++)
        {
            //si el elemento de tokens no contiene el simbolo '/'
            if (tokens[i].find("/", 0) == string::npos)
            {
                indexes.push_back(stoi(tokens[i]));
            }
            else
            {
                //si el elemento de tokens tiene el simbolo '/' separar la cadena
                strcomponents = Split(tokens[i], "/");

                if (!strcomponents.empty())
                {
                    switch (pos)
                    {
                    case 1: //Extraer vt: Vértice de textura
                        indexes.push_back(stoi(strcomponents[pos]));
                        break;
                    case 2: //Extraer vn: Vértice normal
                        indexes.push_back(stoi(strcomponents[pos]));
                        break;

                    default: //Extraer vértice geometrico
                        indexes.push_back(stoi(strcomponents[pos]));
                        break;
                    }
                }
            }
        }
    }
    else
        exit(1);

    return indexes;
}

Object::Object() {} //Constructor por defecto

/*  Crear un objeto 3D.
    @param filename Nombre del archivo desde el cual se lee la definición del objeto.
*/
Object::Object(string filename)
{
    string line;             //Cadena de caracteres para guardar el renglón leído
    ifstream file(filename); //Flujo de entrada

    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<string> elements({Split(line, " ")}); //Componentes de la línea leída
            if (!elements.empty())
            {
                if (elements[0].compare("g") == 0 || elements[0].compare("o") == 0)
                {
                    if (this->name.empty())
                    {
                        if (elements.size() == 1)
                        {
                            //Asignar nombre del archivo
                            vector<string> str1 = this->Split(filename, "/");
                            vector<string> str2 = this->Split(str1[1], ".");
                            this->name = str2[0];
                        }
                        else
                            this->name = elements[1];
                    }
                }
                else if (elements[0].compare("v") == 0)
                {
                    this->verts.push_back(CreateVertex(elements));
                    this->verts.back().SetId(this->verts.size());
                }
                else if (elements[0].compare("f") == 0)
                {
                    vector<int> idverts(ExtractIndexes(elements));
                    vector<Vertex> verts;
                    for(int i : idverts)
                    {
                        verts.push_back(this->verts[i-1]);
                    }
                    Face f(verts);
                    this->faces.push_back(f);
                }
            }
        }
        file.close();
    }
    else
        exit(1);

    if (this->name.empty())
    {
        vector<string> str1 = this->Split(filename, "/");
        vector<string> str2 = this->Split(str1[1], ".");
        this->name = str2[0];
    }
}

/* Devuelve un arreglo dinámico con los vértices que forman el objeto. */
vector<Vertex> Object::GetVerts()
{
    return this->verts;
}

/* Devuelve un arreglo dinámico con las caras que forman el objeto. */
vector<Face> Object::GetFaces()
{
    return this->faces;
}

/* Devuelve el nombre del objeto. */
string Object::GetName()
{
    return this->name;
}

/* Divide una cadena en subcadenas.
    @param str Cadena para ser dividida.
    @param delim Cadena delimitadora.
    @return Un arreglo de cadenas con los elementos extraídos de str 
*/
vector<string> Object::Split(const string &str, const string &delim)
{
    vector<string> tokens;    //Arreglo de elementos (subcadenas)
    size_t prev = 0, pos = 0; //prev: Posición del primer caracter diferente a delim,
                              //pos: Posición del primer encuentro con delim
    do
    {
        pos = str.find(delim, prev); //Obtener la posición de delim
        if (pos == string::npos)
            pos = str.length();                      //si pos == -1, entonces no se encontró el delimitador
        string token = str.substr(prev, pos - prev); //Se extrae una subcadena desde una posición prev hasta antes del delimitador
        if (!token.empty())
            tokens.push_back(token); //Si se extrajo una subcadena, se agrega al vector
        prev = pos + delim.length(); //Se actualiza la posición del primer caracter diferente a delim
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

/*  Extrae de un arreglo de strings las coordenadas x,y,z y crea un vértice.
    @param tokens Arreglo de strings con los valores x, y, z.
    @return Un vértice.
*/
Vertex Object::CreateVertex(vector<string> tokens)
{
    float x, y, z;
    x = stod(tokens[1]);
    y = stod(tokens[2]);
    z = stod(tokens[3]);

    Vertex v(x, y, z);
    return v;
}

/*  Muestra en la salida estándar la información de un objeto. 
    Nombre, vértices y caras.
*/
void Object::Print()
{
    cout << "g " << this->name << endl;
    cout << "\n";

    for (Vertex vertex : this->verts)
        cout << "v " << vertex.X() << " " << vertex.Y() << " " << vertex.Z() << endl;

    cout << "\n";

    for (Face face : this->faces)
    {
        cout << "f ";
        for (Vertex v : face.GetVertices())
            cout << v.GetId() << " ";
        cout << "\n";
    }
    cout << endl;
}

/*  Muestra en la salida estándar el conjunto de vectores normales
    contenidos en el objeto.
*/
void Object::PrintNormals()
{
    int i = 1;
    for (Face face : this->faces)
    {
        cout << "Normal F" << i << ":\t" << face.GetNormal();
        i++;
    }

    cout << endl;
}

/*  Muestra en la salida estándar la ecuación del plano
    correspondiente a cada una de las caras de este objeto.
*/
void Object::PrintEquationsOfPlane()
{
    int i = 0;
    for (Face face : this->faces)
    {
        cout << "Ecuacion del plano F" << i + 1 << ":" << endl;
        face.PrintEquationOfPlane();
        i++;
    }
    cout << endl;
}