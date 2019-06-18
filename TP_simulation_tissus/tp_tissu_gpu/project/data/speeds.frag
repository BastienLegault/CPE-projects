#version 120

uniform sampler2D positions;
uniform sampler2D speeds;
uniform sampler2D normals;

const float SIZE = 128.0;
#define SQRT2     (1.4142136)

const float DELTA  = (1.0 / SIZE);
#define GRID      (4.0 / SIZE)     //cloth has size 4x4

#define DT 0.005
#define damping 50

const float GRAVITY = 9.81;


void main (void)
{

  float u = gl_TexCoord[0].s;
  float v = gl_TexCoord[0].t;
  vec2 uv = gl_TexCoord[0].st;

  vec3 speed  = texture2D (speeds   ,uv).xyz;
  vec3 pos    = texture2D (positions,uv).xyz;
  vec3 normal = texture2D (normals  ,uv).xyz;

 // vec3 force =vec3(0,0,0);

  float longueur_repos = GRID;
  speed = (1-damping*DT)*speed;

  speed.y -= DT*GRAVITY;

  //verifie que les positions dans dans les limites attendues
  bool ok[4];
  ok[0] = u<(1-DELTA);  ok[1] = u>DELTA; ok[2] = v<(1-DELTA);  ok[3] = v>DELTA;

      if( ok[0])
      {
          vec3 vecteur_ressort_1 = texture2D(positions,uv+(1,0)*DELTA).xyz-pos;
          speed -= DT * 4000.0 * (longueur_repos-length(vecteur_ressort_1)) * normalized(vecteur_ressort_1);
      }
      if( ok[1])
      {
          vec3 vecteur_ressort_2 = texture2D(positions,uv+(-1,0)*DELTA).xyz-pos;
          speed -= DT * 4000.0 * (longueur_repos-length(vecteur_ressort_2)) * normalized(vecteur_ressort_2);
      }
      if( ok[2])
      {
          vec3 vecteur_ressort_3 = texture2D(positions,uv+(0,1)*DELTA).xyz-pos;
          speed -= DT * 4000.0 * (longueur_repos-length(vecteur_ressort_3)) * normalized(vecteur_ressort_3);
      }
      if( ok[3])
      {
          vec3 vecteur_ressort_4 = texture2D(positions,uv+(0,-1)*DELTA).xyz-pos;
          speed -= DT * 4000.0 * (longueur_repos-length(vecteur_ressort_4)) * normalized(vecteur_ressort_4);
      }

      //speed += (1 - 0.2 * DT)*speed + DT*force ;
      //vertex(i,j) = vertex(i,j) + DT*speed(i,j);

      //calculer ressorts et ajouter les forces à la vitesse
      // ex: vecteur_ressort_1 = texture2D(positions,uv+(1,0)*DELTA)-pos; ...
      // speed += DT * K * (longueur_repos-length(vecteur_ressort_1)) * vecteur_unitaire ...
/*
      vec3 vecteur_ressort_5 = texture2D(positions,uv+(1,1)*DELTA)-pos;
      vec3 vecteur_ressort_6 = texture2D(positions,uv+(1,-1)*DELTA)-pos;
      vec3 vecteur_ressort_7 = texture2D(positions,uv+(-1,-1)*DELTA)-pos;
      vec3 vecteur_ressort_8 = texture2D(positions,uv+(-1,1)*DELTA)-pos;

      vec3 vecteur_ressort_9 = texture2D(positions,uv+(0,2)*DELTA)-pos;
      vec3 vecteur_ressort_10 = texture2D(positions,uv+(0,-2)*DELTA)-pos;
      vec3 vecteur_ressort_11 = texture2D(positions,uv+(2,0)*DELTA)-pos;
      vec3 vecteur_ressort_12 = texture2D(positions,uv+(-2,0)*DELTA)-pos;

      speed += DT * 8 * (SQRT2*longueur_repos-length(vecteur_ressort_5)) * (vec3(1,1,0)/length(vecteur_ressort_5));
      speed += DT * 8 * (SQRT2*longueur_repos-length(vecteur_ressort_6)) * (vec3(1,-1,0)/length(vecteur_ressort_6));
      speed += DT * 8 * (SQRT2*longueur_repos-length(vecteur_ressort_7)) * (vec3(-1,-1,0)/length(vecteur_ressort_7));
      speed += DT * 8 * (SQRT2*longueur_repos-length(vecteur_ressort_8)) * (vec3(-1,1,0)/length(vecteur_ressort_8));

      speed += DT * 8 * (2*longueur_repos-length(vecteur_ressort_9)) * (vec3(0,2,0)/length(vecteur_ressort_9));
      speed += DT * 8 * (2*longueur_repos-length(vecteur_ressort_10)) * (vec3(0,-2,0)/length(vecteur_ressort_10));
      speed += DT * 8 * (2*longueur_repos-length(vecteur_ressort_11)) * (vec3(2,0,0)/length(vecteur_ressort_11));
      speed += DT * 8 * (2*longueur_repos-length(vecteur_ressort_12)) * (vec3(-2,0,0)/length(vecteur_ressort_12));
*/




  gl_FragColor = vec4(speed, 0.0);
}
