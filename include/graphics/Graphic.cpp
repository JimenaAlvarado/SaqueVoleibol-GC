#include "Graphic.hpp" 
#include "Transformation.hpp"
#include "Trajectory.hpp"
#include "../objreader/Object.hpp"
#include "../models/Ball.hpp"
#include "../models/Hand.hpp"
#include "../models/Net.hpp"

/* Espacio gráfico. */	
Graphic::Graphic()
{
	
}

/* Crea una nueva ventana y su contexto. 
    @param _width Ancho de la ventana, en coordenadas de pantalla. Debe ser mayor a cero.
    @param _height Alto de la ventana, en coordenadas de pantalla. Debe ser mayor a cero.
    @param _red Valor entre 0 y 1 para el color primario rojo.
    @param _green Valor entre 0 y 1 para el color primario verde.
    @param _blue Valor entre 0 y 1 para el color primario azul.
    @param _alpha Valor entre 0 y 1 para la trasparencia.
*/ 
int Graphic::newWindow(int _width, int _height, float _red, float _green, float _blue, float _alpha)
{
    GLFWwindow* window;
    this->window =  window;
    
    if( !glfwInit() )
    {
        cout << stderr << "Fallo al inicializar GLFW" << endl;
        return -1;
    }
    this->window = glfwCreateWindow(_width, _height, "Saque de voleibol", NULL, NULL);
    if( this->window == NULL ) {
        cout << stderr << "Fallo al abrir la ventana de GLFW." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(this->window);
    glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(_red, _green, _blue, _alpha);

    return 0;
}

/* Abre una ventana después de crearla con el método newWindow(). 
   Dibuja los objetos 3D y las animaciones.
*/
void Graphic::openWindow()
{
    //Crear objetos
    Ball ball(-0.8, -0.5, 0.0, 1.0, 1.0, 1.0);
    Hand hand(-0.8, -0.5, 0.0, 1.0, 1.0, 0.0);
    Net net(2.0, -1.2, 0.0, 0.0, 0.0, 0.0, 0.8);

    Transformation tr;
    Trajectory tray;

    do {
        glClear( GL_COLOR_BUFFER_BIT );

        //  Matriz de transformación para la mano.
        hand.setMtr(tr.T(hand.posInit()[0], hand.posInit()[1], hand.posInit()[2]) * tr.Ry(hand.angle()));
        //Aplicar transformaciones para la red.
        net.setMtr(tr.S(net.scale(), net.scale(), net.scale()) * tr.T(net.posInit()[0], net.posInit()[1], net.posInit()[2]));

        //Puntos de control
        Vertex p1(ball.posInit()[0], ball.posInit()[1], ball.posInit()[2]);
        Vertex p2(-0.7, 0.6, 0.0);
        Vertex p3(0.6, 0.6, 0.0);
        Vertex p4(0.7, ball.posInit()[1], 0.0);
        vector <Vertex> curve = tray.curve(p1, p2, p3, p4, 0.1); //Vector con los puntos que forman la trayectoria curva.
    
        hand.draw();
        net.draw();

        if(glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS || keyenter_press == 1)
        {
            keyenter_press = 1;

            //Crear un vértice para cada punto incluido en la trayectoria curva.
            Vertex p = curve[index_curve];
            if (index_curve < curve.size()-1)
                index_curve++; 
                    
            //Crear matriz de transformación y dibujar balón
            ball.setMtr(tr.T(p.X(), p.Y(), p.Z()));
            ball.draw();
        }

        else{
            //Crear matriz de transformación y dibujar balón
            ball.setPosInit(ball.posInit()[0], getyo(), ball.posInit()[2]);
            ball.setMtr(tr.T(ball.posInit()[0], ball.posInit()[1], ball.posInit()[2]));
            ball.draw();
        }

        if (glfwGetKey(this->window, GLFW_KEY_DELETE) == GLFW_PRESS)
        {
            reset();
            ball.setPosInit(ball.posInit()[0], yo, ball.posInit()[2]);
            ball.setMtr(tr.T(ball.posInit()[0], ball.posInit()[1], ball.posInit()[2]));
            ball.draw();
        }

        glfwSwapBuffers(this->window);
        glfwPollEvents();

    } while( glfwGetKey(this->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(this->window) == 0 );

    glfwTerminate();	
}

//Devuelve la posición sobre el eje y, cuando se usan las flechas arriba/abajo del teclado.
float Graphic::getyo()
{
    //Interacción: Mover el balón con las flechas arriba/abajo del teclado. 
    if(glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS && yo < -0.1)
    { yo += 0.05; }
    else if(glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS && yo > -0.5)
    { yo -= 0.05; }

    return yo;
}

//Reinicia el estado de las variables
void Graphic::reset()
{
    yo = -0.5;
    index_curve = 0;
    keyenter_press = 0;
}