#include "Graphic.hpp" 
#include "Transformation.hpp"
#include "Trajectory.hpp"
#include "../objreader/Object.hpp"
	
Graphic::Graphic()
{
	
}

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

    GLclampf red = _red;
    GLclampf green = _green;
    GLclampf blue = _blue;
    GLclampf alpha = _alpha;

    glClearColor(red, green, blue, alpha);

    return 0;
}

void Graphic::openWindow()
{
    //Leer archivos obj
    Object ball("models/ball.obj");
    Object hand("models/hand.obj");
    Object net("models/net.obj");

    Transformation tr;
    Trajectory tray;
    arma::fmat Mtr_ball;
    arma::fmat Mtr_hand;
    arma::fmat Mtr_net; 

    int index_curve = 0;
    int enter_press = 0;

    do {
        glClear( GL_COLOR_BUFFER_BIT );

        //Aplicar transformaciones para la mano.
        Mtr_hand = tr.T(-0.8, -0.5, 0.0) * tr.Ry(-90);
        //Aplicar transformaciones para la red.
        Mtr_net = tr.S(0.8, 0.8, 0.8) * tr.T(2, -1.2, 0);
        
        drawObject(hand, Mtr_hand, 1.0, 1.0, 0.0);
        drawObject(net, Mtr_net, 0.0, 0.0, 0.0);

        if(glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS || enter_press == 1)
        {
            enter_press = 1;
            //Puntos de control
            Vertex p1(-0.8, yo, 0.0);
            Vertex p2(-0.7, 0.6, 0.0);
            Vertex p3(0.6, 0.6, 0.0);
            Vertex p4(0.7, -0.5, 0.0);
            vector <Vertex> curve = tray.curve(p1, p2, p3, p4, 0.1); //Vector con los puntos que forman la trayectoria curva.

            //Crear un vértice para cada punto incluido en la trayectoria curva.
            Vertex p = curve[index_curve];
            if (index_curve < curve.size()-1)
                index_curve++; 
                    
            //Crear matriz de transformaciones para el balón.
            Mtr_ball = tr.T(p.X(), p.Y(), p.Z());
            drawObject(ball, Mtr_ball, 1.0, 1.0, 1.0);
        }

        else{
            float yo = getyo();
            Mtr_ball = tr.T(-0.8, yo, 0.0); 
            drawObject(ball, Mtr_ball, 1.0, 1.0, 1.0);
        }

        if (glfwGetKey(this->window, GLFW_KEY_DELETE) == GLFW_PRESS)
        {
            yo = -0.5;
            index_curve = 0;
            enter_press = 0;
            
            Mtr_ball = tr.T(-0.8, yo, 0.0); 
            drawObject(ball, Mtr_ball, 1.0, 1.0, 1.0);
        }

        glfwSwapBuffers(this->window);
        glfwPollEvents();

    } while( glfwGetKey(this->window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(this->window) == 0 );

    glfwTerminate();	
}

void Graphic::drawObject(Object _obj, arma::fmat _Mtr, float _red, float _green, float _blue)
{
    glBegin(GL_TRIANGLES);
    glColor3f(_red, _green, _blue);
    for(Face f : _obj.GetFaces())
    {   
        for(Vertex v : f.GetVertices())
        {
            arma::fcolvec v_tr = _Mtr * v.Homog();
            v_tr = v_tr / v_tr[3];
            glVertex3f(v_tr[0], v_tr[1], v_tr[3]);
        }
    }
    glEnd();
}	

float Graphic::getyo()
{
    //Interacción: Mover el balón con las flechas arriba/abajo del teclado. 
    
    if(glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS && yo < -0.1)
    { yo += 0.05; }
    else if(glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS && yo > -0.5)
    { yo -= 0.05; }

    return yo;
}