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
    vector<string> components;     //v, vt, vn
    vector<int> indexes; //Arreglo de números identificadores (índices)
    if (pos >= 0 && pos <= 2)
    {
        for (int i = 1; i < tokens.size(); i++)
        {
            components = Split(tokens[i], "/");

            if (!components.empty())
            {
                switch (pos)
                {
                case 1: //Extraer vt: Vértice de textura
                    indexes.push_back(stoi(components[pos]));
                    break;
                case 2: //Extraer vn: Vértice normal
                    indexes.push_back(stoi(components[pos]));
                    break;

                default: //Extraer vértice geometrico
                    indexes.push_back(stoi(components[pos]));
                    break;
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
    float x, y, z;

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
                    Face f(idverts);
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
{ return this->verts; }

/* Devuelve un arreglo dinámico con las caras que forman el objeto. */
vector<Face> Object::GetFaces()
{ return this->faces; }

/* Devuelve el nombre del objeto. */
string Object::GetName()
{ return this->name; }

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
    double x, y, z;
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
        for (int id : face.GetVertices())
            cout << id << " ";
        cout << "\n";
    }
    cout << endl;
}

/*  Calcula el vector normal de un plano.
    @param _face Plano del cual se calculará el vector normal.
    @return Un vector en un solo renglón.
*/
arma::drowvec Object::CalculateNormal(Face _face)
{
    vector<arma::drowvec> auxverts;
    arma::drowvec NF;
    for (int i : _face.GetVertices())
    {
        arma::drowvec vertex = {verts[i - 1].X(), verts[i - 1].Y(), verts[i - 1].Z()};
        auxverts.push_back(vertex);
    }

    //Producto cruz
    NF = arma::cross(auxverts[1] - auxverts[0], auxverts[2] - auxverts[0]);

    return NF;
}

/*  Calcula el vector normal de todos los planos que forman el objeto 
    y las concentra en un arreglo dinámico.
*/
void Object::CalculateAllNormals()
{
    for (Face &face : this->faces)
    {
         face.SetNormal(CalculateNormal(face));
    }   
}

/*  Genera los coeficientes de la ecuación de un plano.
    @param _face Plano del cual se obtiene la ecuación.
*/
void Object::EquationPlane(Face &_face)
{
    _face.SetA(_face.Normal()[0]);
    _face.SetB(_face.Normal()[1]);
    _face.SetC(_face.Normal()[2]);

   double D = -((_face.A() * this->verts[_face.GetVertices()[0] - 1].X()) +
                (_face.B() * this->verts[_face.GetVertices()[0] - 1].Y()) +
                (_face.C() * this->verts[_face.GetVertices()[0] - 1].Z()));
    
   _face.SetD(D);
}

/*  Muestra en la salida estándar el conjunto de vectores normales
    contenidos en el objeto.
*/
void Object::PrintNormals()
{
    int i = 1;
    for (Face face : this->faces)
    {
        cout << "Normal F" << i << ":\t" << face.Normal();
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
    for(Face face : this->faces)
    {
        cout << "Ecuacion del plano F" << i+1 << ":" << endl;
        EquationPlane(face);
        cout << face.A() << "x + " << face.B() << "y + " << face.C() << "z + " << face.D() << " = 0" << endl;
        i++;
    }
    cout << endl;
}