// Projet Algorithmique et Programmation : Jeu des Châteaux
// Lucie Boutou
// S1C1

#include <QApplication>
#include <DrawingWindow.h>
#include <cmath>
#include <iostream>

using namespace std;

// paramètres du graphique
const float xMin = -10;
const float xMax = 10;
const float yMin = 0;
const float yMax = 15;

// conversion coordonnées réelles -> coordonnées fenêtre
int rtowX(const DrawingWindow& w, float rx)
{
    return (int )roundf((w.width - 1) * (rx - xMin) / (xMax - xMin));
}

int rtowY(const DrawingWindow& w, float ry)
{
    return (int )roundf((w.height - 1) * (yMax - ry) / (yMax - yMin));
}

// conversion coordonnées fenêtre -> coordonnées réelles
float wtorX(const DrawingWindow& w, int wx)
{
    return (xMax - xMin) * wx / (w.width - 1) + xMin;
}

float wtorY(const DrawingWindow& w, int wy)
{
    return -(yMax - yMin) * wy / (w.height - 1) - yMax;
}

// affichage de l'interface graphique
void interface(DrawingWindow& w)
{
    // entête des fonctions
    void dessineColline(DrawingWindow& w);
    void dessineChateaux(DrawingWindow& w);

    // couleur de fond et sol
    w.setBgColor("cyan");
    w.clearGraph();

    // appel aux différentes fonctions pour afficher la colline et les châteaux
    dessineColline(w);
    dessineChateaux(w);
    w.setColor("maroon");
    w.fillRect(rtowX(w,-10),rtowY(w,1),rtowX(w,10),rtowX(w,10));

    // affichage des noms des joueurs
    w.setColor("white");
    w.drawText(rtowX(w,-9.5),rtowY(w,1),"Joueur 1");
    w.drawText(rtowX(w,8),rtowY(w,1),"Joueur 2");

}

// renvoie un nombre aléatoire
int hasard(int min, int max)
{

return (int) (min + ((float) rand() / RAND_MAX * (max - min + 1)));

}

// parabole représentant la colline
float fonctionColline(float x, int hauteur, int largeur)
{

    return hauteur*(1-((2*x)/largeur)*((2*x)/largeur));

}

//dessin de la colline
void dessineColline(DrawingWindow& w)
{

    const int hmin=4;
    const int hmax=8;
    const int lmin=6;
    const int lmax=10;

    int hauteur,largeur;

    float xg,xf,yg,yf;

    hauteur=hasard(hmin,hmax);
    largeur=hasard(lmin,lmax);

    w.setColor("lime");

    // calcul de yf pour tout xf dans la largeur de la fenêtre    
    for(xf=0;xf<w.width;xf++)
    {

        xg=wtorX(w,xf);
        yg=fonctionColline(xg, hauteur, largeur);
        yf=rtowY(w,yg);
        w.drawPoint(xf,yf);
        w.drawLine(xf,yf,xf,w.height); //dessin d'une ligne de yf jusqu'au bas de la fenêtre pour coloriser la colline

    }

    


}

//dessin des châteaux
void dessineChateaux(DrawingWindow& w)
{

    w.setColor("darkgrey");
    w.fillRect(rtowX(w,8),rtowY(w,2),rtowX(w,9),rtowY(w,1));
    w.fillRect(rtowX(w,-8),rtowY(w,2),rtowX(w,-9),rtowY(w,1));

    w.setColor("grey");
    w.fillRect(rtowX(w,9),rtowY(w,2.5),rtowX(w,9.5),rtowY(w,1));
    w.fillRect(rtowX(w,7.5),rtowY(w,2.5),rtowX(w,8),rtowY(w,1));
    w.fillRect(rtowX(w,-9.5),rtowY(w,2.5),rtowX(w,-9),rtowY(w,1));
    w.fillRect(rtowX(w,-8),rtowY(w,2.5),rtowX(w,-7.5),rtowY(w,1));

    //dessin des créneaux
    w.setColor("cyan");
    w.fillRect(rtowX(w,8.2),rtowY(w,2),rtowX(w,8.4),rtowY(w,1.8));
    w.fillRect(rtowX(w,8.6),rtowY(w,2),rtowX(w,8.8),rtowY(w,1.8));
    w.fillRect(rtowX(w,-8.4),rtowY(w,2),rtowX(w,-8.2),rtowY(w,1.8));
    w.fillRect(rtowX(w,-8.8),rtowY(w,2),rtowX(w,-8.6),rtowY(w,1.8));
    w.fillRect(rtowX(w,9.1),rtowY(w,2.5),rtowX(w,9.2),rtowY(w,2.4));
    w.fillRect(rtowX(w,9.3),rtowY(w,2.5),rtowX(w,9.4),rtowY(w,2.4));
    w.fillRect(rtowX(w,7.6),rtowY(w,2.5),rtowX(w,7.7),rtowY(w,2.4));
    w.fillRect(rtowX(w,7.8),rtowY(w,2.5),rtowX(w,7.9),rtowY(w,2.4));
    w.fillRect(rtowX(w,-9.4),rtowY(w,2.5),rtowX(w,-9.3),rtowY(w,2.4));
    w.fillRect(rtowX(w,-9.2),rtowY(w,2.5),rtowX(w,-9.1),rtowY(w,2.4));
    w.fillRect(rtowX(w,-7.9),rtowY(w,2.5),rtowX(w,-7.8),rtowY(w,2.4));
    w.fillRect(rtowX(w,-7.7),rtowY(w,2.5),rtowX(w,-7.6),rtowY(w,2.4));
}

// envoi des boulets
bool envoiBoulet(DrawingWindow& w, int f, int a, int vvent, bool j1)
{
    const int v0=f;
    float alpha;
    const float k = 0.1;
    const float g = 9.81;
    const float dt = 0.01;
    bool i=true,j=true;
    float x,y,vx,vy,vr,ax,ay,xprec,yprec;

    // position de départ du boulet et calcul de l'angle en fonction du joueur qui joue
    if (j1)
    {
        x=-8.5;
        y=2.5;
        alpha=(a*2*3.14)/360;
    }
    else
    {
        x=8.5;
        y=2.5;
        alpha=((180-a)*2*3.14)/360;
    }

    // calcul des vitesses initiales
    vx = v0*cos(alpha);
    vy = v0*sin(alpha);

    // calcul de la position du boulet en fonction du temps
    while(i)
    {
        // dessin de la flèche représentant la force du vent à chaque itération au cas où le boulet l'effacerait
        if(vvent!=0)
        {
            w.setColor("black");
            w.drawLine(300-vvent*5, 20, 300+vvent*5, 20);

            if(vvent<0)
            {
                w.drawLine(300+vvent*5, 20, 310+vvent*5, 30);
                w.drawLine(300+vvent*5, 20, 310+vvent*5, 10);
            }
            else
            {
                w.drawLine(300+vvent*5, 20, 290+vvent*5, 30);
                w.drawLine(300+vvent*5, 20, 290+vvent*5, 10);
            }
        }
        
        // efface la trace du boulet
        xprec=x;
        yprec=y;
        w.setColor("cyan");
        w.fillCircle(rtowX(w,xprec),rtowY(w,yprec),5); 

        // ensemble des calculs amenant à la position du boulet
        vr=sqrt((vx-vvent)*(vx-vvent)+(vy*vy));        
        ax=-k*vr*(vx-vvent);
        ay=-k*vr*vy-g;
        x=x+vx*dt;
        y=y+vy*dt;
        vx=vx+ax*dt;
        vy=vy+ay*dt;

        // trace du boulet
        w.setColor("black");
        w.fillCircle(rtowX(w,x),rtowY(w,y),5);
        w.sync();
        w.msleep(50);

        // détection de la sortie du boulet de la fenêtre
        if((rtowX(w,x)<0 || rtowX(w,x)>w.width) && rtowY(w,y)<w.height)
        {
            i=false;
            w.setColor("cyan");
            w.fillCircle(rtowX(w,x),rtowY(w,y),5);
        }

 
        // détection de la colline et cratère
        if((w.getPointColor((int)rtowX(w,x)+6,(int)rtowY(w,y))==-16711936)
          || (w.getPointColor((int)rtowX(w,x)-6,(int)rtowY(w,y))==-16711936)
          || (w.getPointColor((int)rtowX(w,x),(int)rtowY(w,y)+6)==-16711936))
        {
            i=false;
            w.setColor("cyan");
            w.fillCircle(rtowX(w,x),rtowY(w,y),10);
        }
         
        // détection du sol et cratère
        if(w.getPointColor((int)rtowX(w,x),(int)rtowY(w,y)+6)==-8388608)
        {
            i=false;
            w.setColor("cyan");
            w.fillCircle(rtowX(w,x),rtowY(w,y),10);
        }

        // détection des chateaux et cratère
        if((w.getPointColor((int)rtowX(w,x)+6,(int)rtowY(w,y))==-5658199)
          || (w.getPointColor((int)rtowX(w,x)-6,(int)rtowY(w,y))==-5658199)
          || (w.getPointColor((int)rtowX(w,x),(int)rtowY(w,y)+6)==-5658199)
          || (w.getPointColor((int)rtowX(w,x)+6,(int)rtowY(w,y))==-8355712)
          || (w.getPointColor((int)rtowX(w,x)-6,(int)rtowY(w,y))==-8355712)
          || (w.getPointColor((int)rtowX(w,x),(int)rtowY(w,y)+6)==-8355712))
        {
            // condition déterminant le château touché
            if(x>0)
            {
                w.setColor("white");
                w.drawText(rtowX(w,-2),rtowY(w,1),"Le Joueur 1 gagne !");
                w.setColor("cyan");
                w.fillCircle(rtowX(w,x),rtowY(w,y),15);

                // affichage de feux d'artifice au dessus du château gagnant
                w.setColor("yellow");
                w.fillCircle(rtowX(w,-7.8),rtowY(w,3.5),3);
                w.setColor("red");
                w.fillCircle(rtowX(w,-8.1),rtowY(w,3.75),3);
                w.setColor("yellow");
                w.fillCircle(rtowX(w,-8.5),rtowY(w,4),3);
                w.setColor("red");
                w.fillCircle(rtowX(w,-8.9),rtowY(w,3.75),3);
                w.setColor("yellow");
                w.fillCircle(rtowX(w,-9.2),rtowY(w,3.5),3);            
            }
            else
            {
                w.setColor("white");
                w.drawText(rtowX(w,-2),rtowY(w,1),"Le Joueur 2 gagne !");
                w.setColor("cyan");
                w.fillCircle(rtowX(w,x),rtowY(w,y),15);

                // affichage de feux d'artifice au dessus du château gagnant
                w.setColor("yellow");
                w.fillCircle(rtowX(w,7.8),rtowY(w,3.5),3);
                w.setColor("red");
                w.fillCircle(rtowX(w,8.1),rtowY(w,3.75),3);
                w.setColor("yellow");
                w.fillCircle(rtowX(w,8.5),rtowY(w,4),3);
                w.setColor("red");
                w.fillCircle(rtowX(w,8.9),rtowY(w,3.75),3);
                w.setColor("yellow");
                w.fillCircle(rtowX(w,9.2),rtowY(w,3.5),3);

            }

            i=false;
            j=false;

        }
    }

    return j;    
}

// lance la partie
void lancerPartie(DrawingWindow& w)
{
    int force,angle,vvent;
    const int ventmax = 5;
    bool partie=true, j1=true;

    // calcule une vitesse de vent aléatoire entre -5 et 5
    vvent = hasard((-ventmax),ventmax);

    // dessin de la flèche représentant la force du vent
    if(vvent!=0)
    {
        w.setColor("black");
        w.drawLine(300-vvent*5, 20, 300+vvent*5, 20);

        if(vvent<0)
        {
            w.drawLine(300+vvent*5, 20, 310+vvent*5, 30);
            w.drawLine(300+vvent*5, 20, 310+vvent*5, 10);
        }
        else
        {
            w.drawLine(300+vvent*5, 20, 290+vvent*5, 30);
            w.drawLine(300+vvent*5, 20, 290+vvent*5, 10);
        }
    }

    // partie devient faux quand un château est touché
    while(partie)
    {
        //le booléen j1 permet d'alterner le joueur qui joue
        if(j1)
        {
            cout<<"Au joueur 1 de jouer !"<<endl;
            cout<<"Entrer une force : "<<endl;
            cin>>force;
            cout<<"Entrer un angle : "<<endl;
            cin>>angle;

            partie=envoiBoulet(w,force,angle,vvent,j1);
            j1=false;
        }
        else
        {
            cout<<"Au joueur 2 de jouer !"<<endl;
            cout<<"Entrer une force : "<<endl;
            cin>>force;
            cout<<"Entrer un angle : "<<endl;
            cin>>angle;

            partie=envoiBoulet(w,force,angle,vvent,j1);
            j1=true;
        }
    }

}

void jeu(DrawingWindow& w)
{
    char nouv;

    interface(w);
    lancerPartie(w);

    cout<<endl<<"Nouvelle partie ? (O pour oui, N pour non)"<<endl;
    cin>>nouv;

    //boucle permettant de relancer une partie
    while(nouv=='O')
    {
        interface(w);
        lancerPartie(w);
        nouv='N';
        cout<<endl<<"Nouvelle partie ? (O pour oui, N pour non)"<<endl;
        cin>>nouv;
        
    }
    
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    DrawingWindow fenetre(jeu, 640, 480);
    fenetre.show();
    return application.exec();
}

