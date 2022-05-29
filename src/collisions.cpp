#include <SDL2/SDL.h> //pour le Uint32

#include "../include/shape.hpp"
#include "../include/personnages.hpp"
#include "../include/quad_tree.hpp"

int m=60; //doit être identique au n de personnages.cpp

int ecartPositionVictoire=5;

bool memePlanHorizontal(const Perso perso, const Platform bloc)
{
    if (perso.py-perso.height>bloc.position.y)
    {
        return false;
    }

    else if (perso.py<bloc.position.y-bloc.size.y)
    {
        return false;
    }

    return true;   
}

bool memePlanVertical(const Perso perso, const Platform bloc)
{
    if (perso.px > bloc.position.x+bloc.size.x)
    {
        return false;
    }

    else if (perso.px+perso.width < bloc.position.x)
    {
        return false;
    }

    return true;   
}

void collision(const int nbPersos, Perso listedespersos[], const int nbBlocs, Platform listedesblocs[], const Uint32 elapsedTime, Quadtree quadtree, int currentPerso) 
{
    Perso perso = listedespersos[currentPerso];

    if (DetectePersoInLeaf (perso, quadtree) == true)
    {
        for (int n=0; n<nbPersos; n++)
        {
            Perso* perso=&listedespersos[n];

            if (std::abs(perso->vx)>std::abs(perso->vy))
            {

                if ((perso->vx)/(2*m) > 0) //droite
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=listedesblocs[i].position.x-(perso->px+perso->width);
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanHorizontal(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.x;
                        float futurePositionBordPerso=perso->px+(perso->vx)/(2*m)*elapsedTime+perso->width;
                    
                        // si le perso rentre dans l'obstacle
                        if (positionBordObstacle - futurePositionBordPerso < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vx=0;
                            perso->px = positionBordObstacle-perso->width-1;
                        }
                    }
                }

                else if ((perso->vx)/(2*m) < 0) //gauche
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=perso->px
                                        -(listedesblocs[i].position.x+listedesblocs[i].size.x);
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanHorizontal(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.x+listedesblocs[obstacleIndex].size.x;
                        float futurePositionBordPerso=perso->px+(perso->vx)/(2*m)*elapsedTime;
                    
                        // si le perso rentre dans l'obstacle
                        if (futurePositionBordPerso - positionBordObstacle < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vx=0;
                            perso->px = positionBordObstacle+1;
                        }
                    }
                }

                if ((perso->vy)/(2*m) > 0) //haut
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=listedesblocs[i].position.y-listedesblocs[i].size.y - perso->py;
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanVertical(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.y - listedesblocs[obstacleIndex].size.y;
                        float futurePositionBordPerso=perso->py+(perso->vy)/(2*m)*elapsedTime;
                    
                        // si le perso rentre dans l'obstable
                        if (positionBordObstacle - futurePositionBordPerso < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vy=0;
                            perso->py = positionBordObstacle-1;
                        }
                    }
                }

                else if ((perso->vy)/(2*m) < 0) //bas
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=perso->py-perso->height - listedesblocs[i].position.y;
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanVertical(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.y;
                        float futurePositionBordPerso=perso->py+(perso->vy)/(2*m)*elapsedTime-perso->height;
                    
                        // si le perso rentre dans l'obstable
                        if (futurePositionBordPerso - positionBordObstacle < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vy=0;
                            perso->py = positionBordObstacle+perso->height+1;
                        }
                    }
                }
            }
            else 
            {
                if ((perso->vy)/(2*m) > 0) //haut
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=listedesblocs[i].position.y-listedesblocs[i].size.y - perso->py;
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanVertical(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.y - listedesblocs[obstacleIndex].size.y;
                        float futurePositionBordPerso=perso->py+(perso->vy)/(2*m)*elapsedTime;
                    
                        // si le perso rentre dans l'obstable
                        if (positionBordObstacle - futurePositionBordPerso < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vy=0;
                            perso->py = positionBordObstacle-1;
                        }
                    }
                }

                else if ((perso->vy)/(2*m) < 0) //bas
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=perso->py-perso->height - listedesblocs[i].position.y;
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanVertical(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.y;
                        float futurePositionBordPerso=perso->py+(perso->vy)/(2*m)*elapsedTime-perso->height;
                    
                        // si le perso rentre dans l'obstable
                        if (futurePositionBordPerso - positionBordObstacle < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vy=0;
                            perso->py = positionBordObstacle+perso->height+1;
                        }
                    }
                }

                if ((perso->vx)/(2*m) > 0) //droite
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=listedesblocs[i].position.x-(perso->px+perso->width);
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanHorizontal(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.x;
                        float futurePositionBordPerso=perso->px+(perso->vx)/(2*m)*elapsedTime+perso->width;
                    
                        // si le perso rentre dans l'obstacle
                        if (positionBordObstacle - futurePositionBordPerso < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vx=0;
                            perso->px = positionBordObstacle-perso->width-1;
                        }
                    }
                }

                else if ((perso->vx)/(2*m) < 0) //gauche
                {
                    float distanceMin=10000000000000000000000.0f;
                    int obstacleIndex=NULL;

                    for (int i = 0 ; i < nbCollisionInLeaf(listedesblocs, quadtree, nbBlocs, nbPersos, listedespersos) ; i++)
                    {
                        float distance=perso->px
                                        -(listedesblocs[i].position.x+listedesblocs[i].size.x);
                        
                        if (distance>=0 && distance<distanceMin 
                            && memePlanHorizontal(*perso,listedesblocs[i])==true
                            )
                        {
                            distanceMin=distance;
                            obstacleIndex=i;
                        }
                    }
                    if(obstacleIndex)
                    {
                        float positionBordObstacle=listedesblocs[obstacleIndex].position.x+listedesblocs[obstacleIndex].size.x;
                        float futurePositionBordPerso=perso->px+(perso->vx)/(2*m)*elapsedTime;
                    
                        // si le perso rentre dans l'obstacle
                        if (futurePositionBordPerso - positionBordObstacle < 0 && listedesblocs[obstacleIndex].solid != 0) 
                        {
                            perso->vx=0;
                            perso->px = positionBordObstacle+1;
                        }
                    }
                }
            }
        }
    }
}


bool checkGround(const Perso perso, const int nbBlocs, const Platform listedesblocs[])
{
    for (int i=0; i<nbBlocs; i++)
    {
        if (perso.px+perso.width > listedesblocs[i].position.x 
        && perso.px < listedesblocs[i].position.x+listedesblocs[i].size.x 
        && perso.py-perso.height-1 <= listedesblocs[i].position.y
        && perso.py > listedesblocs[i].position.y-listedesblocs[i].size.y
        && listedesblocs[i].solid == 1) 
        {
            return true;
        }
    }

    return false;
}

bool victory(const int nbPersos, const Perso listedespersos[], const Goal listedesgoals[])
{
    if(nbPersos==0)
    {
        return false;
    }
    for (int i=0; i<nbPersos; i++)
    {
        if(listedespersos[i].px>listedesgoals[i].position.x+ecartPositionVictoire 
        || listedespersos[i].px<listedesgoals[i].position.x-ecartPositionVictoire)
        {
            return false;
        }
        if(listedespersos[i].py>listedesgoals[i].position.y+ecartPositionVictoire 
        || listedespersos[i].py<listedesgoals[i].position.y-ecartPositionVictoire)
        {
            return false;
        }
    }
    return true;
}