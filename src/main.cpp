
// Inclusion des bibliothèques
#include <raylib.h>
#include <cmath> 
#include <vector>
#include <cfloat> 
#include "abeille.h"
#include "button.h"
#include "chnometre.h"
#include "labyranthe.h"
#include "score.h"
#include "obstacle.h"
#include <stdlib.h>
#include <time.h>
#include "position.h"
#include "cell.h"
#include "niveau.h"
#include "config.h"
using namespace std;

// Déclaration des constantes globales
constexpr int screenWidth = 1600;
constexpr int screenHeight = 900;

int main() 
{
    // initialisation
    InitWindow(screenWidth, screenHeight, "PROJET ABEILLE");
    SetTargetFPS(60);
   
   InitAudioDevice(); // initialiser le système audio
   // chargement des sons
    Sound introSound = LoadSound("Graphique/intro.wav");        // son de l'intro
    Sound jeuSound = LoadSound("Graphique/game2.wav");          // son en cours de jeu
    Sound collisionSound = LoadSound("Graphique/obstacle.wav");// son de collision avec l'obstacle
    Sound victoireSound = LoadSound("Graphique/WIN.wav"); // son de victoire

    PlaySound(introSound);// jouer le son de l'intro

    // Chargement des textures et des images
    Texture2D background1 = LoadTexture("Graphique/honey2.png");
    Texture2D background2 = LoadTexture("Graphique/gaz.png");
    Texture2D textureheur = LoadTexture("Graphique/chronometre.png");
    Texture2D youWin = LoadTexture("Graphique/youwin.png");
    Texture2D abeilleCont = LoadTexture("Graphique/abeilleCont.png");
    

    // Boutons
    Button playButton = Button("Graphique/play.png", {600, 600}, 0.30f);
    Button exitButton = Button("Graphique/exit.png", {600, 750}, 0.30f);
    Button nextButton = Button("Graphique/next.buton.png", {630, 600}, 0.20f);
    Button repplay = Button("Graphique/rep.png", {7, 5}, 0.80f);
    Button song = Button("Graphique/song.png", {5, 80}, 0.80f);
    Button notsong = Button("Graphique/notSong.png", {5, 155}, 0.80f);
    Button stop = Button("Graphique/stop.png", {5, 230}, 0.80f);
    Button contin = Button("Graphique/continue.png", {820, 500}, 0.80f);
    Button homeButton = Button("Graphique/home.png", {1500, 800}, 0.80f);
    Button easyButton = Button("Graphique/easy.button.png", {550, 150}, 0.50f);
    Button mediumButton = Button("Graphique/middle.button.png", {450, 230}, 0.70f);
    Button hardButton = Button("Graphique/difficult.button.png", {450, 650}, 0.70f);
    Button level = Button("Graphique/level.png", {600, -5}, 0.70f);


    // Gestion du chronomètre et du score
    Chronometre chronometre;
    TableauScores tableauScores;


    // Création du labyrinthe
    Maze maze;
    maze.generatemaze(0, 0);


    // Création de l'abeille
    Player abeille(0, MazeConfig::grid_height - 1, maze, "Graphique/abeille.png");
    
    // gestion de la sortie du labyrinthe 
    maze.maze[MazeConfig::grid_width - 1][0].bottomwall = false;
    maze.maze[MazeConfig::grid_width - 1][0].topwall = false;

    // initialisation du niveau
    Niveau niv(maze);

    // Création de l'objectif(fleur)
    Player fleur(MazeConfig::grid_width - 1, 0, maze, "Graphique/fleur6.png");


    // Variables pour la logique du jeu
    bool menu = true;// menu principal
    bool menu2 = false;// menu de choix de niveau
    bool isPlaying = false;// jeu en cours
    bool exit = false;// fermeture du jeu
    bool isStoped = false;//jeu en pause
    bool facil = false;//niveau facile
    bool moyen = false;//niveau moyen
    bool difficile = false;//niveau difficile
    bool victoire = false;//Gagner
    bool collision = false;//collision entre l'abeille et l'obstacle
    double displayStartTime = 0;//temps d'affichage du message de collision

    // Variables pour le score
    float scoreFinal = 0.0f;
    float meilleurScore = FLT_MAX;
    
    // Initialisation du chronomètre et le demarer 
    chronometre.demarrer();
    chronometre.setTexture(textureheur);

    // Boucle principale
    while (!WindowShouldClose() && !exit)
    {   
        //dessiner les textures
        BeginDrawing();
        ClearBackground(WHITE);

       
        if (menu) {
            // Affichage du menu principal
            
            DrawTexture(background1, 0, 0, WHITE);
            playButton.Draw();
            exitButton.Draw();
            
            // Gestion des clics sur les boutons
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, playButton.rect)) {
                    
                    menu = false;//menu principal
                    menu2 = true;//menu de choix de niveau
                    
                } else if (CheckCollisionPointRec(mousePoint, exitButton.rect)) {
                    exit = true;//quitter le jeu
                }
            }
        
        } 
        else if (menu2) {
            
            // Affichage du menu de choix de niveau
            DrawTexture(background2, 0, 0, WHITE);
            easyButton.Draw();
            mediumButton.Draw();
            hardButton.Draw();
            homeButton.Draw();
            level.Draw();//afficher un message de choisi le niveau par un photo 

            // Gestion des clics sur les boutons
           if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();
                //------button facile----
                if (CheckCollisionPointRec(mousePoint, easyButton.rect)) {
                 isPlaying = true;//commencer le jeu 
                 moyen = false;//niveau moyen
                 difficile = false;//niveau difficile
                 facil = true;
                 menu2 = false;//fermer le menu des niveau 
                 niv.easyNiveau();//generer le niveau facile
                 maze.miseajour();//mise a jour du labyrinthe
                 StopSound(introSound);//arreter le son de l'intro
                 PlaySound(jeuSound);//jouer le son de jeu
                 
               }
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();
                 //------button moyen----
                if (CheckCollisionPointRec(mousePoint, mediumButton.rect)) {
                 isPlaying = true;
                 moyen = true;
                 facil = false;
                 difficile = false;
                 niv.mediumNiveau();//generer le niveau moyen
                 menu2 = false;
                 maze.miseajour();;//mise a jour du labyrinthe
                 StopSound(introSound);
                 PlaySound(jeuSound);
                 
               }
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();
                 //------button difficile----
                if (CheckCollisionPointRec(mousePoint, hardButton.rect)) {
                 isPlaying = true;
                 difficile = true;
                 niv.difficultNiveau(abeille.getPosition());//generer le niveau difficile
                 moyen = false;
                 facil = false;
                 menu2 = false;
                 niv.miseAJourNiveau();//mise a jour du niveau
                 StopSound(introSound);
                 PlaySound(jeuSound);
               }
            }
           
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();
                 //------button home----
                if (CheckCollisionPointRec(mousePoint, homeButton.rect)) {
                 
                 chronometre.arreter();//arreter le chronometre
                 isPlaying = false;//arreter le jeu
                 abeille.possistionabb();//remettre l'abeille au debut
                 menu= true;//afficher le menu principal
                 chronometre.demarrer();
                 niv.miseAJourNiveau();//mise a jour du labyrinthe
                 StopSound(introSound);
                 PlaySound(jeuSound);
                 
               }
            }
            
        }
        else if (isPlaying) {
            //comencer le jeu 
            chronometre.mettre_a_jour();//mettre a jour le chronometre

             DrawTexture(background2, 0, 0, WHITE);//afficher le fond de l'ecran
             // Gestion des touches de déplacement
            if (IsKeyPressed(KEY_RIGHT)) abeille.moveplayer(1, 0);
            if (IsKeyPressed(KEY_LEFT)) abeille.moveplayer(-1, 0);
            if (IsKeyPressed(KEY_UP)) abeille.moveplayer(0, -1);
            if (IsKeyPressed(KEY_DOWN)) abeille.moveplayer(0, 1);

            // Affichage le chronometre
            chronometre.afficher();

            //gestion des obstacle dand lrd different niveau
            if(facil){
              niv.easyNiveau();
              moyen = false;
              difficile = false;
              // generer les obstacles
              std::vector<Obstacle>& obstacles = niv.getObstacles();
                for (auto& obstacle : obstacles) {
                        obstacle.move(maze);//deplacement de l'obstacle   
                        obstacle.draw();  //dessiner l'obstacle     
                        
                        // Vérification de collision avec l'abeille
                        Rectangle abeilleRect = abeille.getCollisionRectangle();
                        Rectangle obstacleRect = obstacle.getCollisionRectangle();
                        
                        if (CheckCollisionRecs(abeilleRect, obstacleRect)) {
                            PlaySound(collisionSound);
                            collision = true;
                            displayStartTime = GetTime();//temps d'affichage du message de collision
                            abeille.possistionabb();//remettre l'abeille au debut
                            PlaySound(jeuSound);
                        }
                }
              
            }else if(moyen){
                niv.mediumNiveau();
                facil = false;
                difficile = false;
                // generer les obstacles
                std::vector<Obstacle>& obstacles = niv.getObstacles();
                for (auto& obstacle : obstacles) {
                    obstacle.move(maze);   
                    obstacle.draw();       
                    
                    // Vérification de collision avec l'abeille
                    Rectangle abeilleRect = abeille.getCollisionRectangle();
                    Rectangle obstacleRect = obstacle.getCollisionRectangle();
                    
                    if (CheckCollisionRecs(abeilleRect, obstacleRect)) {
                        PlaySound(collisionSound);
                        collision = true;
                        displayStartTime = GetTime();
                        abeille.possistionabb();
                        PlaySound(jeuSound);
                    }
                }
               
            }else if(difficile){
                niv.difficultNiveau(abeille.getPosition());
               facil = false;
               moyen = false;
                // generer les obstacles
               std::vector<Obstacle>& obstacles = niv.getObstacles();
               for (auto& obstacle : obstacles) {
                    obstacle.move(maze);   
                    obstacle.draw();       
                    
                    // Vérification de collision avec l'abeille
                    Rectangle abeilleRect = abeille.getCollisionRectangle();
                    Rectangle obstacleRect = obstacle.getCollisionRectangle();
                    
                    if (CheckCollisionRecs(abeilleRect, obstacleRect)) {
                        PlaySound(collisionSound);
                        collision = true;
                        displayStartTime = GetTime();
                        abeille.possistionabb();
                        PlaySound(jeuSound);
                    }
                }
           }
            // Affichage des textures
           
            abeille.draw();
            fleur.drawGoal();
            
            //les buttons de l'ecran de jeu
            repplay.Draw();
            song.Draw();
            notsong.Draw();
            stop.Draw();
            homeButton.Draw();

            //afficher le message de collision
            if (collision && GetTime() - displayStartTime <= 2.0) {
                DrawText("Ooooups!", 650, 450, 80, RED);
            } else if (GetTime() - displayStartTime > 3.0) {
                collision = false;
            }
           
            // Gestion des clics sur les boutons
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, homeButton.rect)) {
                 
                 chronometre.reinitialiser();
                 isPlaying = false;
                 abeille.possistionabb();
                 menu= true;
                victoire = false;
                 chronometre.demarrer();
                 niv.miseAJourNiveau();
                 PlaySound(introSound);
                 
               }
            }
            //gestion des clics sur les boutons : ------
            //------button replay -----
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, repplay.rect)) {
                 
                 chronometre.reinitialiser();//reinitialiser le chronometre
                 chronometre.demarrer();//demarer le chronometre
                 niv.miseAJourNiveau();//mise a jour du niveau
                 abeille.possistionabb();//remettre l'abeille au debut
                 
               }
            }
             //------button stop -----
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, stop.rect)) {
                 
                 chronometre.arreter();//arreter le chronometre
                  isStoped = true;//jeu en pause
                   
               }
                 
            }
            //------button continue -----
            if(isStoped) {
                DrawTexture(abeilleCont, 600,250, WHITE);//afficher une image affiche un fliche pour continue aprer le stop
                contin.Draw();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, contin.rect)) {
                
                    chronometre.continuer();//continuer le chronometre
                    isStoped = false;//jeu en cours
                 
               }
            }
            }
            //------button song -----
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, song.rect)) {
                 
                 PlaySound(jeuSound);  
                     
               }
                 
            }
            //------button not song (pas du music)-----
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, notsong.rect)) {
                 
                 StopSound(jeuSound);//arreter le son de jeu
                   
                   
               }
                 
            }

            // Affichage de la victoire
            if (abeille.hasWon) {
                scoreFinal = chronometre.temps_actuel;//score final
                chronometre.arreter();//arreter le chronometre
                
                // Mise à jour du meilleur score
                if (scoreFinal < meilleurScore) {
                    meilleurScore = scoreFinal;
                }

                // animation de victoire
                
                if (!victoire) {  
                        victoire = true;
                        StopSound(jeuSound); // arrêter le son de jeu
                        PlaySound(victoireSound); // jouer le son de victoire    
                }

                 //afficher le message de victoire
                tableauScores.afficher(meilleurScore, scoreFinal, 630, 500, youWin, 100);
                nextButton.Draw();//afficher le button pour passer au niveau suivant
                
                // Gestion des clics sur le bouton next
                 if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                          Vector2 mousePoint = GetMousePosition();//position de la souris

                         if (CheckCollisionPointRec(mousePoint, nextButton.rect)) {
                 
                            chronometre.reinitialiser();//reinitialiser le chronometre
                            isPlaying = false;//arreter le jeu
                            abeille.possistionabb();//remettre l'abeille au debut
                            victoire = false;//arreter le message de victoire
                            menu2= true;//afficher le menu de choix de niveau
                            chronometre.demarrer(); 
                            niv.miseAJourNiveau();  //mise a jour du niveau
                            StopSound(victoireSound);//arreter le son de victoire
                            PlaySound(introSound);//jouer le son de l'intro
                 
                            }
                  
                  
                   }
                
            }
            
        }
       
        
        EndDrawing();
    }
    // Déchargement des ressources
    UnloadSound(introSound);
    UnloadSound(jeuSound);
    UnloadSound(collisionSound);
    UnloadSound(victoireSound);
    UnloadTexture(background1);
    UnloadTexture(background2);
    UnloadTexture(playButton.texture);
    UnloadTexture(exitButton.texture);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}


