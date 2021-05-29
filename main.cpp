#include "include/objreader/Object.hpp"
#include "include/graphics/Trajectory.hpp"
#include "include/graphics/Transformation.hpp"
#include "GLFW/glfw3.h"
#include <vector>

using namespace std;
 
int main()
{
    Object ball("obj/ball.obj");
    Object hand("obj/hand.obj");
    Object net("obj/net.obj");

    Transformation tr;
    Trajectory tray;

    //Puntos de control
    Vertex p1(-0.7, -0.6, 0.0);
    Vertex p2(-0.6, 0.6, 0.0);
    Vertex p3(0.6, 0.6, 0.0);
    Vertex p4(0.7, -0.6, 0.0);
    vector <Vertex> curve = tray.curve(p1, p2, p3, p4, 0.1); //Vector con los puntos que forman la trayectoria curva.
    int index_curve = 0;

    cout << "Curva de Bezier" << endl;
    for(Vertex v : curve)
        cout << v.X() << " " << v.Y() << " " << v.Z() << endl; 

    //Aplicar transformaciones para la mano.
    arma::fmat Mtr_hand = tr.T(-0.8, -0.5, 0.0) * tr.Ry(-90);
    //Aplicar transformaciones para la red.
    arma::fmat Mtr_net = tr.S(0.8, 0.8, 0.8) * tr.T(2, -1.2, 0);

    //Dibujar en ventana
    GLFWwindow* window;

    if( !glfwInit() )
    {
        cout << stderr << "Fallo al inicializar GLFW" << endl;
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Saque de voleibol", NULL, NULL);
    if( window == NULL ) {
        cout << stderr << "Fallo al abrir la ventana de GLFW." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    do {
        glClear( GL_COLOR_BUFFER_BIT );

        //Crear un vértice para cada punto incluido en la trayectoria curva.
        Vertex p = curve[index_curve];
        if(index_curve < curve.size()-1)
            index_curve++; 
        
        //Crear matriz de transformaciones para el balón.
        arma::fmat Mtr_ball = tr.T(p.X(), p.Y(), p.Z());

        glBegin(GL_TRIANGLES);

            //Dibujar balón
            glColor3f(1.0, 1.0, 1.0);
            for(Face f : ball.GetFaces())
            {   
                for(Vertex v : f.GetVertices())
                {
                    arma::fcolvec v_tr = Mtr_ball * v.Homog();
                    v_tr = v_tr / v_tr[3];
                    glVertex3f(v_tr[0], v_tr[1], v_tr[3]);
                }
            }

            //Dibujar mano (izquierda)
            glColor3f(1.0, 1.0, 0.0);
            for(Face f : hand.GetFaces())
            {   
                for(Vertex v : f.GetVertices())
                {
                    arma::fcolvec v_tr = Mtr_hand * v.Homog();
                    v_tr = v_tr / v_tr[3];
                    glVertex3f(v_tr[0], v_tr[1], v_tr[3]);
                }
            }

            //Dibujar red
            glColor3f(0.0, 0.0, 0.0);
            for(Face f : net.GetFaces())
            {   
                for(Vertex v : f.GetVertices())
                {
                    arma::fcolvec v_tr = Mtr_net * v.Homog();
                    v_tr = v_tr / v_tr[3];
                    glVertex3f(v_tr[0], v_tr[1], v_tr[3]);
                }
            }

        glEnd();
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();	

    return 0;
}   
 

 