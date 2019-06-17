#version 330 core

// Données en provenance du vertex shader :
in vec3 ver_color; // inutilisée pour l'instant

// nom de la variable de sortie (couleur, vec4)
out vec4 out_color;

void main(void)
{
  out_color = vec4(1., 1., 1., 1.);
  // décommenter à partir de la question sur les couleurs :
  out_color = vec4(ver_color, 1.);
}
