#ifndef EVENT_H
#define EVENT_H

#include <irrlicht.h>
#include <stdio.h>
#include <iostream>
#include "gui_ids.h"

class MyEventReceiver : public irr::IEventReceiver
{
public:
  bool release_escape = true;
  bool fenetre_visible = false;
  bool fin = false;
  bool debut = true;
  bool reset = false;
  bool avance = false;
  bool recule = false;
  bool droite = false;
  bool gauche = false;
  bool rot_gauche = false;
  bool rot_droite = false;
  bool courir = false;
  bool sauter = false;
  bool crouch = false;
  bool release = true;
  bool release_tir = true;
  bool shoot=false;
  int  old_x=0, old_y=0;
  bool zoom = false;
  int deplacement_ok = 0;
  int nb_grille;
 
  bool OnEvent(const irr::SEvent &event);
  bool mouse_handler(const irr::SEvent &event);
  bool keyboard_handler(const irr::SEvent &event);
  bool gui_handler(const irr::SEvent &event);

  void Deplacement();
  bool is_mouse_pressed(int &x, int &y);

  void set_camera(irr::scene::ICameraSceneNode *n);
  void set_arme(irr::scene::ISceneNode *n);
  void set_grille(irr::scene::IAnimatedMeshSceneNode **n);
  irr::scene::ICameraSceneNode *camera;
  irr::scene::ISceneNode *arme;
  irr::scene::IAnimatedMeshSceneNode **grilles;

private:
  
};

#endif