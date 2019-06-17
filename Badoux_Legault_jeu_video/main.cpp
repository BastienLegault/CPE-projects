#include <irrlicht.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "event.h"
#include "gui_ids.h"

using namespace irr;

namespace ic = irr::core;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ig = irr::gui;

const int ENEMY_ID = 1;
const int WALL_ID = 0;

is::ICameraSceneNode * Reset_camera(is::ISceneManager *smgr, is::ICameraSceneNode * camera_del, is::ISceneNodeAnimatorCollisionResponse *anim_new)//, is::IAnimatedMeshSceneNode *arme)
{
  camera_del->remove();
  is::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS(nullptr, 70, 0.3, -1, nullptr, 0, true, 0);
  camera->setTarget(ic::vector3df(-500,50,95));//endroit vers lequel pointe la caméra au départ
  camera->setPosition(ic::vector3df(50,40,95));//position de départ
  camera->addAnimator(anim_new);

  return camera;
}

inline wchar_t *f2wchar(float f) // convert float to wchar_t 
{ 
   wchar_t *t = new wchar_t[6]; 
     swprintf(t, 5, L"%2.2f", f); 
   return t; 
}

int main()
{
  // Le gestionnaire d'événements
  MyEventReceiver receiver;
  // Création de la fenêtre et du système de rendu.
  //
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
                                        ic::dimension2d<u32>(1080, 720),//(720, 640),//(640, 480)
                                        16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();
  ig::IGUIEnvironment *gui = device->getGUIEnvironment();

  

  // Ajout de l'archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");

  // On charge un bsp (un niveau) en particulier :
  is::IAnimatedMesh *mesh = smgr->getMesh("20kdm2.bsp");
  is::IMeshSceneNode *decors;
  decors = smgr->addOctreeSceneNode(mesh->getMesh(0));//, nullptr, -1, 1024);
  
  // Translation pour que nos personnages soient dans le décor
  decors->setPosition(core::vector3df(-1300,-104,-1249));//(-1300,-104,-1249) 
  decors->setID(WALL_ID);
  
  device->getCursorControl()->setActiveIcon(ig::ECURSOR_ICON(1));
   
  //chargement de l'arme
  is::IAnimatedMesh *mesh_arme = smgr->getMesh("data/M14_Rifle/M14.obj");

  // Attachement de notre personnage dans la scène
  is::IAnimatedMeshSceneNode *arme = smgr->addAnimatedMeshSceneNode(mesh_arme);
  receiver.set_arme(arme);  
  
  // Pour ajouter la texture et la lumière
  arme->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  arme->setMaterialTexture(0, driver->getTexture("data/M14_Rifle/M14_d.png"));
  //arme->setScale(ic::vector3df(20.0,20.0,20.0)); 
  
  
  //chargement grille
  is::IAnimatedMesh *mesh_grille = smgr->getMesh("data/barre_fer/obj_vent01.dae");
  
  int nb_grille = 16;
  is::IAnimatedMeshSceneNode *grilles[nb_grille];
  receiver.nb_grille = nb_grille;
  
  //premiere salle
  grilles[0] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[0]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[0]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[0]->setPosition(ic::vector3df(110,120,340));
  grilles[0]->setRotation(ic::vector3df(90.0,0.0,0.0));
  grilles[0]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[1] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[1]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[1]->setPosition(ic::vector3df(110,120,355));
  grilles[1]->setRotation(ic::vector3df(90.0,180.0,0.0));
  grilles[1]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  //2eme salle
  grilles[2] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[2]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[2]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[2]->setPosition(ic::vector3df(-190,220,-290));
  grilles[2]->setRotation(ic::vector3df(90.0,90.0,0.0));
  grilles[2]->setScale(ic::vector3df(1.3,2.0,5.0));
  
  grilles[3] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[3]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[3]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[3]->setPosition(ic::vector3df(-175,220,-290));
  grilles[3]->setRotation(ic::vector3df(90.0,-90.0,0.0));
  grilles[3]->setScale(ic::vector3df(1.3,2.0,5.0));
  
  //2eme salle haut
  grilles[4] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[4]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[4]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[4]->setPosition(ic::vector3df(380,380,-830));
  grilles[4]->setRotation(ic::vector3df(90.0,90.0,0.0));
  grilles[4]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[5] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[5]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[5]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[5]->setPosition(ic::vector3df(395,380,-830));
  grilles[5]->setRotation(ic::vector3df(90.0,-90.0,0.0));
  grilles[5]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  //
  grilles[6] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[6]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[6]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[6]->setPosition(ic::vector3df(110,220,700));
  grilles[6]->setRotation(ic::vector3df(90.0,0.0,0.0));
  grilles[6]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[7] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[7]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[7]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[7]->setPosition(ic::vector3df(110,220,715));
  grilles[7]->setRotation(ic::vector3df(90.0,180.0,0.0));
  grilles[7]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  //
  grilles[8] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[8]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[8]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[8]->setPosition(ic::vector3df(835,220,480));
  grilles[8]->setRotation(ic::vector3df(90.0,90.0,0.0));
  grilles[8]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[9] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[9]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[9]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[9]->setPosition(ic::vector3df(850,220,480));
  grilles[9]->setRotation(ic::vector3df(90.0,-90.0,0.0));
  grilles[9]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  //en haut 
  grilles[10] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[10]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[10]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[10]->setPosition(ic::vector3df(-410,450,-70));
  grilles[10]->setRotation(ic::vector3df(90.0,0.0,0.0));
  grilles[10]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[11] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[11]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[11]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[11]->setPosition(ic::vector3df(-410,450,-55));
  grilles[11]->setRotation(ic::vector3df(90.0,180.0,0.0));
  grilles[11]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  //grilles sous lesquelle on passe
  grilles[12] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[12]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[12]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[12]->setPosition(ic::vector3df(385,320,480));
  grilles[12]->setRotation(ic::vector3df(90.0,90.0,0.0));
  grilles[12]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[13] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[13]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[13]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[13]->setPosition(ic::vector3df(400,320,480));
  grilles[13]->setRotation(ic::vector3df(90.0,-90.0,0.0));
  grilles[13]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[14] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[14]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[14]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[14]->setPosition(ic::vector3df(620,320,250));
  grilles[14]->setRotation(ic::vector3df(90.0,0.0,0.0));
  grilles[14]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  grilles[15] = smgr->addAnimatedMeshSceneNode(mesh_grille);
  grilles[15]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  grilles[15]->setMaterialTexture(0, driver->getTexture("data/barre_fer/obj_vent01_01.png"));
  grilles[15]->setPosition(ic::vector3df(620,320,265));
  grilles[15]->setRotation(ic::vector3df(90.0,180.0,0.0));
  grilles[15]->setScale(ic::vector3df(1.3,2.0,3.0));
  
  receiver.set_grille(grilles);

  //une caméra "jeu video à la première personne"
  is::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS(nullptr, 70, 0.0, -1, nullptr, 0, true, 0);
  //                                         (Parent,RotateSpeed(sensitivty),MoveSpeed,id,KeyMapArray,KeyMapSize,NoVerticalMovement,JumpSpeed)
  camera->setTarget(ic::vector3df(-500,50,95));//endroit vers lequel pointe la caméra au départ
  camera->setPosition(ic::vector3df(50,40,95));//position de départ
  arme->setParent(camera);
  arme->setPosition(ic::vector3df(10,-15,0));
  arme->setRotation(ic::vector3df(0,85,0));
  receiver.set_camera(camera);
  
  
  //ajout de widgets
  ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(70,100, 1010,620), false, L"Paramètres");
  window->setDraggable(false);
  gui->addStaticText(L"Bienvenu dans [Nom du jeu], votre mission est d'éliminer toutes le cibles en un temps record !",
		     ic::rect<s32>(20,40, 900,70), false, false, window);
  
  gui->addStaticText(L"Le meilleur score de cette session est : ",ic::rect<s32>(20,140, 270,170), false, false, window);
  ig::IGUIStaticText* meilleur_score_minute = gui->addStaticText(L"--",ic::rect<s32>(270,140, 380,170), false, false, window);
  gui->addStaticText(L"min",ic::rect<s32>(300,140, 380,170), false, false, window);
  ig::IGUIStaticText* meilleur_score_seconde = gui->addStaticText(L"--",ic::rect<s32>(330,140, 380,170), false, false, window);
  gui->addStaticText(L"sec",ic::rect<s32>(360,140, 380,170), false, false, window);
  
  gui->addButton(ic::rect<s32>(20,470, 120,500), window, WINDOW_QUIT, L"Quitter");
  gui->addButton(ic::rect<s32>(420,470, 520,500), window, WINDOW_RESUME, L"Reprendre");
  gui->addButton(ic::rect<s32>(820,470, 920,500), window, WINDOW_RESET, L"Recommencer");
  window->setDrawTitlebar(false);  

  
  ig::IGUIWindow *window_fin = gui->addWindow(ic::rect<s32>(70,100, 1010,620), false, L"Fin");
  window_fin->setDraggable(false);
  gui->addStaticText(L"Bravo ! Tu as réussi à toucher toutes les cibles ! Tu peux recommencer pour essayer de t'améliorer",
		     ic::rect<s32>(20,40, 900,70), false, false, window_fin);
  
  gui->addStaticText(L"Votre score est de : ",ic::rect<s32>(20,90, 300,120), false, false, window_fin);
  ig::IGUIStaticText* score_minute = gui->addStaticText(L"--",ic::rect<s32>(150,90, 380,120), false, false, window_fin);
  gui->addStaticText(L"min",ic::rect<s32>(180,90, 380,120), false, false, window_fin);
  ig::IGUIStaticText* score_seconde = gui->addStaticText(L"--",ic::rect<s32>(210,90, 380,120), false, false, window_fin);
  gui->addStaticText(L"sec",ic::rect<s32>(240,90, 380,120), false, false, window_fin);
  
  gui->addStaticText(L"Le meilleur score de cette session est : ",ic::rect<s32>(20,140, 270,170), false, false, window_fin);
  ig::IGUIStaticText* meilleur_score_minute_fin = gui->addStaticText(L"--",ic::rect<s32>(270,140, 380,170), false, false, window_fin);
  gui->addStaticText(L"min",ic::rect<s32>(300,140, 380,170), false, false, window_fin);
  ig::IGUIStaticText* meilleur_score_seconde_fin = gui->addStaticText(L"--",ic::rect<s32>(330,140, 380,170), false, false, window_fin);
  gui->addStaticText(L"sec",ic::rect<s32>(360,140, 380,170), false, false, window_fin);
  
  gui->addButton(ic::rect<s32>(20,470, 120,500), window_fin, WINDOW_FIN_QUIT, L"Quitter");
  gui->addButton(ic::rect<s32>(820,470, 920,500), window_fin, WINDOW_FIN_RESET, L"Recommencer");
  window_fin->setDrawTitlebar(false);
  
  
  
  ig::IGUIWindow *window_debut = gui->addWindow(ic::rect<s32>(70,100, 1010,620), false, L"Début");
  window_debut->setDraggable(false);
  gui->addStaticText(L"Bienvenu dans Hell's skulls",
		     ic::rect<s32>(380,40, 900,70), false, false, window_debut);
  gui->addStaticText(L"Votre mission est d'éliminer toutes le cibles en un temps record !",
		     ic::rect<s32>(20,100, 900,130), false, false, window_debut);
  gui->addStaticText(L"Utilisez ZQSD pour vous déplacer, espace pour sauter, maj pour sprinter et C pour vous accroupir et passer dans les endroits étroits !",
		     ic::rect<s32>(20,160, 900,190), false, false, window_debut);
  gui->addStaticText(L"Appuyez sur le bouton gauche de la souris pour tirer et visez avec le bouton droit pour avoir plus de précision",
		     ic::rect<s32>(20,220, 900,250), false, false, window_debut);
  gui->addStaticText(L"Attention, certains énemis peuvent être difficile à trouver mais le compteur vous indique combien il en reste",
		     ic::rect<s32>(20,280, 900,310), false, false, window_debut);
  gui->addButton(ic::rect<s32>(420,470, 520,500), window_debut, WINDOW_PLAY, L"Jouer");
  
  
  
  
  
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("data/fontlucida.png");
  skin->setFont(font);
  
    
  // Chargement des textures pour les chiffres
  iv::ITexture *digits[10];
  digits[0] = driver->getTexture("data/0.png");
  digits[1] = driver->getTexture("data/1.png");
  digits[2] = driver->getTexture("data/2.png");
  digits[3] = driver->getTexture("data/3.png");
  digits[4] = driver->getTexture("data/4.png");
  digits[5] = driver->getTexture("data/5.png");
  digits[6] = driver->getTexture("data/6.png");
  digits[7] = driver->getTexture("data/7.png");
  digits[8] = driver->getTexture("data/8.png");
  digits[9] = driver->getTexture("data/9.png");
  iv::ITexture *slash = driver->getTexture("data/slash.png");

  // Création des places pour les chiffres
  ig::IGUIImage *score_10     = gui->addImage(ic::rect<s32>(10,20, 50,60)); score_10->setScaleImage(true);
  ig::IGUIImage *score_1      = gui->addImage(ic::rect<s32>(50,20, 90,60)); score_1->setScaleImage(true);
  ig::IGUIImage *slash_im     = gui->addImage(ic::rect<s32>(90,20,  130,60)); slash_im->setScaleImage(true);
  ig::IGUIImage *score_10_tot = gui->addImage(ic::rect<s32>(130,20, 170,60)); score_10_tot->setScaleImage(true);
  ig::IGUIImage *score_1_tot  = gui->addImage(ic::rect<s32>(170,20, 210,60)); score_1_tot->setScaleImage(true);

  //collision avec le décors
  is::ITriangleSelector *selector = smgr->createTriangleSelector(decors->getMesh(),decors);
  decors->setTriangleSelector(selector);
  selector->drop();   
  
  is::ISceneCollisionManager *collision_manager = smgr->getSceneCollisionManager();  
  
  //Gestion des collisions
  selector = smgr->createOctreeTriangleSelector( decors->getMesh(), decors);
  decors->setTriangleSelector(selector);
  is::ISceneNodeAnimatorCollisionResponse *anim ;
  anim = smgr->createCollisionResponseAnimator(selector, camera,
						ic::vector3df(30, 50, 30),
						ic::vector3df(0, -10, 0),
						ic::vector3df(0, 30, 0));
  camera->addAnimator(anim);
  

  //Création des cibles
  int nb_cible = 17;
  
  is::IAnimatedMeshSceneNode *cibles[nb_cible];
  
  ic::vector3df nord = ic::vector3df(0.0,0.0,0.0);
  ic::vector3df ouest = ic::vector3df(0.0,90.0,0.0);
  ic::vector3df sud = ic::vector3df(0.0,180.0,0.0);
  ic::vector3df est = ic::vector3df(0.0,-90.0,0.0);
    
  ic::vector3df rotation_cible[nb_cible];
  ic::vector3df position_cible[nb_cible];
  //ceux du début
  position_cible[0] = ic::vector3df(333,10,200);
  rotation_cible[0] = sud;
  position_cible[1] = ic::vector3df(333,10,-6);
  rotation_cible[1] = sud;
  position_cible[2] = ic::vector3df(470,10,100);
  rotation_cible[2] = sud;
  //salle a droite
  position_cible[3] = ic::vector3df(108,138,-444);  
  rotation_cible[3] = est;
  position_cible[4] = ic::vector3df(350,138,-287);
  rotation_cible[4] = sud;
  position_cible[5] = ic::vector3df(110,202,-130);
  rotation_cible[5] = ouest;
  position_cible[6] = ic::vector3df(349,362,-292);
  rotation_cible[6] = sud;
  position_cible[7] = ic::vector3df(-132,362,-290);
  rotation_cible[7] = nord;
  position_cible[8] = ic::vector3df(100,202,-767);
  rotation_cible[8] = ouest;
  position_cible[9] = ic::vector3df(100,202,-899);
  rotation_cible[9] = est;
  
  position_cible[10] = ic::vector3df(-582,138,-284);
  rotation_cible[10] = nord;
  position_cible[11] = ic::vector3df(-582,362,-284);
  rotation_cible[11] = nord;
  position_cible[12] = ic::vector3df(-221,362,-284);
  rotation_cible[12] = sud;
  
  position_cible[13] = ic::vector3df(-408,138,623);
  rotation_cible[13] = nord;
  position_cible[14] = ic::vector3df(-580,138,482);
  rotation_cible[14] = est;
  
  position_cible[15] = ic::vector3df(-400,362,-100);
  rotation_cible[15] = ouest;
  
  position_cible[16] = ic::vector3df(600,138,-300);
  is::IAnimatedMesh *mesh_cible = smgr->getMesh("data/tris.md2");
  
  for(int i = 0;i<nb_cible;i++)
  {
    cibles[i] = smgr->addAnimatedMeshSceneNode(mesh_cible);
    cibles[i]->setMaterialFlag(iv::EMF_LIGHTING, false);
    cibles[i]->setMD2Animation(is::EMAT_STAND);
    cibles[i]->setMaterialTexture(0, driver->getTexture("data/blue_texture.pcx"));
    cibles[i]->setPosition(position_cible[i]);//ic::vector3df(108,138,-444)
    cibles[i]->setRotation(rotation_cible[i]);
    cibles[i]->setScale(ic::vector3df(2.0,2.0,2.0));
    cibles[i]->setID(ENEMY_ID);
    
    if(i == 13)
    {
      is::ISceneNodeAnimator *anim_13 =
		  smgr->createFlyStraightAnimator(ic::vector3df(-500,138,623),
		  ic::vector3df(-300,138,623), 2000, true,true);
	cibles[i]->addAnimator(anim_13);
	cibles[i]->setMD2Animation(is::EMAT_RUN);
    }
    
    if(i == 14)
    {
      is::ISceneNodeAnimator *anim_14 =
		  smgr->createFlyStraightAnimator(ic::vector3df(-550,138,350),
		  ic::vector3df(-550,138,600), 2000, true,true);
	//createFlyStraightAnimator(position de départ, position d'arrivé, vitesse (grd= lent))
	cibles[i]->addAnimator(anim_14);
	cibles[i]->setMD2Animation(is::EMAT_RUN);
    }
    
    if(i == 16)
    {
      cibles[i]->setMD2Animation(is::EMAT_JUMP);
      cibles[i]->setMaterialTexture(0, driver->getTexture("data/blue_texture.pcx"));
      is::ISceneNodeAnimator *anim_16 =
		smgr->createFlyCircleAnimator(ic::vector3df(600,138,-300), 100.0f, 0.004);
      cibles[i]->addAnimator(anim_16);
    }
    
    
    is::ITriangleSelector *selector = smgr->createTriangleSelector(cibles[i]->getMesh(),cibles[i]);
    cibles[i]->setTriangleSelector(selector);
    selector->drop();
    
    selector = smgr->createOctreeTriangleSelector( decors->getMesh(), decors);
    decors->setTriangleSelector(selector);
    is::ISceneNodeAnimatorCollisionResponse *anim ;
    anim = smgr->createCollisionResponseAnimator(selector, cibles[i],
						ic::vector3df(30, 50, 30),
						ic::vector3df(0, -10, 0),
						ic::vector3df(0, 0, 0));
    cibles[i]->addAnimator(anim);
  }
  
  
  bool isCrouch = false;
  int nb_cible_touchee = 0;
  bool cible_touchee = false;
  int temps_courant, temps_courant_seconde, temps_courant_minute;
  int temps_record = FLT_MAX, temps_record_seconde, temps_record_minute;
  bool vrai_debut = true;
  
  ITimer *timer = device->getTimer();
  timer->setTime(0);
  int tps_crouch_1, tps_crouch_2;

  while(device->run())
  {
    //gestion du déplacement du perso
    receiver.Deplacement();
    
    
    ic::vector3df cam_position = camera->getPosition();
    
    if(!receiver.fenetre_visible && !receiver.fin && !receiver.debut)
    {
      if (receiver.sauter)
      {
	cam_position.Y += 4.0;
	if(isCrouch)
	{
	  anim->setEllipsoidTranslation(ic::vector3df(0.0,30.0,0.0));
	  anim->setEllipsoidRadius(ic::vector3df(30.0,50.0,30.0));
	  isCrouch = false;
	  receiver.crouch = false;
	}
      }
      
      
      if (receiver.crouch && !isCrouch)
      {
	anim->setEllipsoidTranslation(ic::vector3df(0.0,10.0,0.0));
	anim->setEllipsoidRadius(ic::vector3df(30.0,30.0,30.0));
	isCrouch = true;
	tps_crouch_1 = timer->getTime();
      }
      else if(!receiver.crouch && isCrouch)
      {
	tps_crouch_2 = timer->getTime();
	if(tps_crouch_2 - tps_crouch_1 > 500)
	{
	  cam_position.Y += 40.0;
	  anim->setEllipsoidTranslation(ic::vector3df(0.0,30.0,0.0));
	  anim->setEllipsoidRadius(ic::vector3df(30.0,50.0,30.0));
	  isCrouch = false;
	}
      }

      camera->setPosition(cam_position);

      int mouse_x, mouse_y;
      if (receiver.is_mouse_pressed(mouse_x, mouse_y))
      {
	ic::line3d<f32> ray;
	ray = collision_manager->getRayFromScreenCoordinates(ic::position2d<s32>(mouse_x, mouse_y));
	ic::vector3df intersection_cible, intersection_mur;
	ic::triangle3df hit_triangle_cible,hit_triangle_mur;

	is::ISceneNode *selected_scene_node_cible = collision_manager->getSceneNodeAndCollisionPointFromRay(
		    ray,
		    intersection_cible, // On récupère ici les coordonnées 3D de l'intersection
		    hit_triangle_cible, // et le triangle intersecté
		    ENEMY_ID); // On ne veut que des noeuds avec cet identifiant
	      
	if(intersection_cible != ic::vector3df(0,0,0))
	{
	    is::ISceneNode *selected_scene_node_mur = collision_manager->getSceneNodeAndCollisionPointFromRay(
		    ray,
		    intersection_mur, // On récupère ici les coordonnées 3D de l'intersection
		    hit_triangle_mur, // et le triangle intersecté
		    WALL_ID); // On ne veut que des noeuds avec cet identifiant
	    ic::vector3df ray_mur = intersection_mur - camera->getPosition();
	    ic::vector3df ray_cible = intersection_cible - camera->getPosition();
	    float dist_ray_mur = sqrt(ray_mur.X*ray_mur.X + ray_mur.Y*ray_mur.Y + ray_mur.Z*ray_mur.Z);
	    float dist_ray_cible = sqrt(ray_cible.X*ray_cible.X + ray_cible.Y*ray_cible.Y + ray_cible.Z*ray_cible.Z);

	    if(dist_ray_cible <= dist_ray_mur)
	      cible_touchee = true;
	}
	
	
	if(selected_scene_node_cible && cible_touchee)
	{
	  selected_scene_node_cible->setMaterialTexture(0,driver->getTexture("data/red_texture.pcx"));
	  selected_scene_node_cible->setID(WALL_ID);
	  nb_cible_touchee += 1;
	  cible_touchee = false;
	}
	receiver.release_tir = true;
	receiver.shoot = false;
      }
      
      if(receiver.zoom)
      {
	arme->setPosition(ic::vector3df(0.0,-11.0,0.0));
	arme->setRotation(ic::vector3df(0.0,90.0,0.0));
	camera->setFOV(M_PI/4.0f);
      }
      else
      {
	arme->setPosition(ic::vector3df(10,-15,0));
	arme->setRotation(ic::vector3df(0,85,0));
	camera->setFOV(M_PI / 2.5f);
      }

    }
    
    
    window->setVisible(receiver.fenetre_visible);
    window_fin->setVisible(receiver.fin);
    window_debut->setVisible(receiver.debut);
    camera->setInputReceiverEnabled(!receiver.fenetre_visible && !receiver.fin && !receiver.debut);
    
    if(receiver.reset)
    {
      for(int i = 0; i<nb_cible ; i++)
      {
	cibles[i]->setMaterialTexture(0,driver->getTexture("data/blue_texture.pcx"));
	cibles[i]->setID(ENEMY_ID);
      }
      receiver.gauche = false;
      receiver.droite = false;
      receiver.avance = false;
      receiver.recule = false;
      nb_cible_touchee = 0;
      arme->setParent(decors);
      camera = Reset_camera(smgr, camera, anim);
      receiver.set_camera(camera);
      arme->setParent(camera);
      receiver.reset = false;
      timer->setTime(0);
      receiver.fin = false;
    }
    
    if(nb_cible_touchee == nb_cible && !timer->isStopped())
    {
      timer->stop();
      temps_courant = timer->getTime();
      if(temps_courant < temps_record)
	temps_record = temps_courant;
      receiver.fin = true;
      receiver.gauche = false;
      receiver.droite = false;
      receiver.avance = false;
      receiver.recule = false;
      temps_courant_seconde = (temps_courant / 1000) % 60;      
      temps_courant_minute = temps_courant / 60000;
      temps_record_seconde = (temps_record / 1000) % 60;      
      temps_record_minute = temps_record / 60000;
      score_seconde->setText(f2wchar(temps_courant_seconde));
      score_minute->setText(f2wchar(temps_courant_minute));
      meilleur_score_seconde->setText(f2wchar(temps_record_seconde));
      meilleur_score_minute->setText(f2wchar(temps_record_minute));
      meilleur_score_seconde_fin->setText(f2wchar(temps_record_seconde));
      meilleur_score_minute_fin->setText(f2wchar(temps_record_minute));
    }
    
    
    if(!receiver.debut && vrai_debut)
    {
      timer->setTime(0);
      vrai_debut = false;
    }
    
    if(receiver.fenetre_visible && !timer->isStopped())
      timer->stop();
    
    if (timer->isStopped() && !receiver.fenetre_visible && nb_cible_touchee != nb_cible)
      timer->start();
     

     
 
    driver->beginScene(true, true, iv::SColor(100,88,77,166 ));
    
    // Dessin de la scène :
    smgr->drawAll();
    
    
    score_10->setImage(digits[(nb_cible_touchee / 10) % 10]);
    score_1->setImage(digits[(nb_cible_touchee / 1) % 10]);
    slash_im->setImage(slash);
    score_10_tot->setImage(digits[(nb_cible / 10) % 10]);
    score_1_tot->setImage(digits[(nb_cible / 1) % 10]);
    
    //dessin des widgets
    gui->drawAll();

    
    driver->endScene();
  }
  device->drop();

  return 0;
}
