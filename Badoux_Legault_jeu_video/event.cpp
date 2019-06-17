#include "event.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


bool MyEventReceiver::keyboard_handler(const SEvent &event)
{
 
  ic::vector3df position = camera->getPosition();
  
  if (event.EventType == EET_KEY_INPUT_EVENT)
  {
    switch (event.KeyInput.Key)
    {
    case KEY_ESCAPE:
      if(event.KeyInput.PressedDown && release_escape && !fin && !debut)
      {
	fenetre_visible = !fenetre_visible;
	release_escape = false;
	gauche = false;
        droite = false;
        avance = false;
        recule = false;
      }
      if(!event.KeyInput.PressedDown)
	release_escape = true;
      break;
    case KEY_KEY_Z: // Avance
      if(!fenetre_visible && !fin && !debut)
	avance = event.KeyInput.PressedDown;
      break;
    case KEY_KEY_S: // Recule
      if(!fenetre_visible && !fin && !debut)
	recule = event.KeyInput.PressedDown;
      break;
    case KEY_KEY_D: // Tourne à droite
      if(!fenetre_visible && !fin && !debut)
	droite = event.KeyInput.PressedDown;
      break;
    case KEY_KEY_Q: // Tourne à gauche
      if(!fenetre_visible && !fin && !debut)
	gauche = event.KeyInput.PressedDown;
      break;
    case KEY_LSHIFT: // Courir
	courir = event.KeyInput.PressedDown;
      break;
    case KEY_SPACE:
      if(!fenetre_visible && !fin && !debut)
	sauter = event.KeyInput.PressedDown;
      break;
    case KEY_KEY_C:
      if(event.KeyInput.PressedDown && release && !fin && !debut && !fenetre_visible && !(
	 position.X < (grilles[12]->getPosition()).X + 20 && position.X > (grilles[12]->getPosition()).X - 20 &&
	 position.Z < (grilles[12]->getPosition()).Z + 50 && position.Z > (grilles[12]->getPosition()).Z - 50) && !(
	 position.X < (grilles[14]->getPosition()).X + 50 && position.X > (grilles[14]->getPosition()).X - 50 &&
	 position.Z < (grilles[14]->getPosition()).Z + 20 && position.Z > (grilles[14]->getPosition()).Z - 20)
      ){
        crouch = !crouch;
	release = false;
      } 
      if(!event.KeyInput.PressedDown)
	release = true;
      break;
	
      
    default:;
    }
  }
  return false;
}


bool MyEventReceiver::mouse_handler(const SEvent &event)
{
    if (event.EventType == EET_MOUSE_INPUT_EVENT)
  {
    switch (event.MouseInput.Event)
    {
      case EMIE_LMOUSE_PRESSED_DOWN:
	if(release_tir){
	  old_x = event.MouseInput.X;
	  old_y = event.MouseInput.Y;
	  shoot = true;
	  release_tir = false;
	}
	break; 
      case EMIE_RMOUSE_PRESSED_DOWN:
	zoom = true;
	break; 
      case EMIE_RMOUSE_LEFT_UP:
	zoom = false;
	break; 
      default:;
    }    
  }
  return false;
}


bool MyEventReceiver::gui_handler(const SEvent &event)
{
  
  //switch(event.GUIEvent.EventType)
  //{
  
    if(event.GUIEvent.EventType == ig::EGET_BUTTON_CLICKED && (fenetre_visible || fin || debut))
    {
      s32 id = event.GUIEvent.Caller->getID();
      switch( id )
      {
	case WINDOW_QUIT:
	  exit(0);
	  break;
	case WINDOW_RESUME:
	  fenetre_visible = !fenetre_visible;
	  break;
	case WINDOW_RESET:
	  fenetre_visible = !fenetre_visible;
	  reset = true;
	  break;
	case WINDOW_FIN_QUIT:
	  exit(0);
	  break;
	case WINDOW_FIN_RESET:
	  fin = !fin;
	  reset = true;
	  break;
	case WINDOW_PLAY:
	  debut = false;
	  break;	  
	default:;
      }
  
    }
    
    return false;
  
  //}
}


bool MyEventReceiver::OnEvent(const SEvent &event)
{
  switch (event.EventType)
  {
    case EET_KEY_INPUT_EVENT:
      return keyboard_handler(event);
    case EET_MOUSE_INPUT_EVENT:
      return mouse_handler(event);
    case EET_GUI_EVENT:
      return gui_handler(event);
    default:;
  }

  return false; 
}


void MyEventReceiver::Deplacement()
{
    ic::vector3df position = camera->getPosition();
    ic::vector3df rotation = camera->getRotation();
    
    int i=0;
    
    if (gauche && !fenetre_visible && !fin)
    {
      for(i=0;i<nb_grille;i+=2)
      {
	if((grilles[i]->getRotation()).Y == 0.0)
	{
	  if(!(
	  (position.X + -4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 50) &&
	  (position.X + -4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 50) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + 4 * sin(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 20) &&
	  (position.Z + 4 * sin(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 20)))
	    deplacement_ok ++;
	}
	else
	{
	  if(!(
	  (position.X + -4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 20) &&
	  (position.X + -4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 20) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + 4 * sin(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 50) &&
	  (position.Z + 4 * sin(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 50)))
	    deplacement_ok ++;
	}
      }
 
      if(deplacement_ok == nb_grille/2)
      {
	if(zoom)
	{
	  position.X += -1 * cos(rotation.Y * M_PI / 180.0);
	  position.Z += 1 * sin(rotation.Y * M_PI / 180.0);
	}
	else
	{
	  position.X += -2 * cos(rotation.Y * M_PI / 180.0);
	  position.Z += 2 * sin(rotation.Y * M_PI / 180.0);
	}
      }
      deplacement_ok = 0;
	
    }
    if (droite && !fenetre_visible && !fin)
    {
      for(i=0;i<nb_grille;i+=2)
      {
	if((grilles[i]->getRotation()).Y == 0.0)
	{
	  if(!(
	  (position.X + 4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 50) &&
	  (position.X + 4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 50) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + -4 * sin(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 20) &&
	  (position.Z + -4 * sin(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 20)))
	    deplacement_ok ++;
	}
	else
	{
	  if(!(
	  (position.X + 4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 20) &&
	  (position.X + 4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 20) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + -4 * sin(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 50) &&
	  (position.Z + -4 * sin(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 50)))
	    deplacement_ok ++;
	}
      }      
      
      if(deplacement_ok == nb_grille/2)
      {
	if(zoom)
	{
	  position.X += 1 * cos(rotation.Y * M_PI / 180.0);
	  position.Z += -1 * sin(rotation.Y * M_PI / 180.0);
	}
	else
	{
	  position.X += 2 * cos(rotation.Y * M_PI / 180.0);
	  position.Z += -2 * sin(rotation.Y * M_PI / 180.0);
	}
      }
      
      deplacement_ok = 0;
    }
    if (avance && !fenetre_visible && !fin)
    {
      for(i=0;i<nb_grille;i+=2)
      {
	if((grilles[i]->getRotation()).Y == 0.0)
	{
	  if(!(
	  (position.X + -4 * sin(-rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 50) &&
	  (position.X + -4 * sin(-rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 50) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + 4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 20) &&
	  (position.Z + 4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 20)))
	    deplacement_ok ++;
	}
	else
	{
	  if(!(
	  (position.X + -4 * sin(-rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 20) &&
	  (position.X + -4 * sin(-rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 20) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + 4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 50) &&
	  (position.Z + 4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 50)))
	    deplacement_ok ++;
	}
      }
      
      if(deplacement_ok == nb_grille/2)
      {
	if(zoom)
	{
	  position.X += -1 * sin(-rotation.Y * M_PI / 180.0);
	  position.Z += 1 * cos(rotation.Y * M_PI / 180.0);
	}
	else
	{
	  if(courir)
	  {
	    position.X += -4 * sin(-rotation.Y * M_PI / 180.0);
	    position.Z += 4 * cos(rotation.Y * M_PI / 180.0); 
	  }
	  else
	  {
	    position.X += -2 * sin(-rotation.Y * M_PI / 180.0);
	    position.Z += 2 * cos(rotation.Y * M_PI / 180.0);   
	  }   
	}
      }
      
      deplacement_ok = 0;
    }
    if (recule && !fenetre_visible && !fin)
    {
      for(i=0;i<nb_grille;i+=2)
      {
	if((grilles[i]->getRotation()).Y == 0.0)
	{
	  if(!(
	  (position.X + 4 * sin(-rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 50) &&
	  (position.X + 4 * sin(-rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 50) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + -4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 20) &&
	  (position.Z + -4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 20)))
	    deplacement_ok ++;
	}
	else
	{
	  if(!(
	  (position.X + 4 * sin(-rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).X + 20) &&
	  (position.X + 4 * sin(-rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).X - 20) &&
	  (position.Y < (grilles[i]->getPosition()).Y + 100) &&
	  (position.Y > (grilles[i]->getPosition()).Y - 170) &&
	  (position.Z + -4 * cos(rotation.Y * M_PI / 180.0)) < ((grilles[i]->getPosition()).Z + 50) &&
	  (position.Z + -4 * cos(rotation.Y * M_PI / 180.0)) > ((grilles[i]->getPosition()).Z - 50)))
	    deplacement_ok ++;
	}
      }
      
      
      if(deplacement_ok == nb_grille/2)
      {
	if(zoom)
	{
	  position.X += 1 * sin(-rotation.Y * M_PI / 180.0);
	  position.Z += -1 * cos(rotation.Y * M_PI / 180.0);
	}
	else
	{
	  if(courir)
	  {
	    position.X += 4 * sin(-rotation.Y * M_PI / 180.0);
	    position.Z += -4 * cos(rotation.Y * M_PI / 180.0);
	  }
	  else
	  {
	    position.X += 2 * sin(-rotation.Y * M_PI / 180.0);
	    position.Z += -2 * cos(rotation.Y * M_PI / 180.0);
	  }     
	} 
      }
      
      deplacement_ok = 0;
    }
    camera->setPosition(position);
    
}


/**************************************************************************\
 * EventReceiver::is_mouse_pressed                                        *
\**************************************************************************/
bool MyEventReceiver::is_mouse_pressed(int &x, int &y)
{
  if (shoot)
  {
    x = old_x;
    y = old_y;
    shoot = false;
    return true;
  }
  return false;
}


/**************************************************************************\
 * EventReceiver::set_node                                                *
\**************************************************************************/
void MyEventReceiver::set_camera(irr::scene::ICameraSceneNode *n)
{
  camera = n;
}

void MyEventReceiver::set_arme(irr::scene::ISceneNode *n)
{
  arme = n;
}

void MyEventReceiver::set_grille(irr::scene::IAnimatedMeshSceneNode **n)
{
  grilles = n;
}