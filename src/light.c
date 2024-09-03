#include "../inc/minirt.h"

t_material  material(t_scene *scene, int i)
{
    t_material material;

    material.color[0] = &scene->sp[i].color[0];
    material.color[1] = &scene->sp[i].color[1];
    material.color[2] = &scene->sp[i].color[2];
    material.ambient = scene->alightr;
    material.diffuse = 0.9;
    material.specular = 0.9;
    material.shininess = 200.0;
    return (material);
}

void    free_lightutils(t_lightdot *light)
{
    free(light->ambient);
    free(light->diffuse);
    free(light->specular);
    free(light->effective_color);
    free(light->lightv);
    free(light->temp);
    free(light->reflectv);
}

int *fill_color(int rgbvalue)
{
    int *result;
    result = malloc(3 * sizeof(int));
    if (!result)
    {
        printf("fatal error in fill color function\n");
        exit(1);
    }
    result[0] = rgbvalue;
    result[1] = rgbvalue;
    result[2] = rgbvalue;
    return (result);
}

int    *lighting(t_scene *scene, float *point, float *eyev, float *normalv)
{
    scene->lightdot.effective_color = combine_colors(scene->sp[0].color, scene->light.color);
    if (!scene->lightdot.effective_color)
        exit (1);
//printf("ligh values: %f %f %f %f\n", scene->light.position[0], scene->light.position[1], scene->light.position[2], scene->light.position[3]);	
    scene->lightdot.lightv = normalize(tuple_subs(scene->light.position, point));
    scene->lightdot.ambient = multiply_scale(scene->lightdot.effective_color, scene->material.ambient);
    scene->lightdot.light_dot_normal = dot_product(normalv, scene->lightdot.lightv);
    if (scene->lightdot.light_dot_normal < 0)
    {
        scene->lightdot.diffuse = fill_color(0);
        scene->lightdot.specular = fill_color(0);
    }
    else
    {
    scene->lightdot.temp = multiply_scale(scene->lightdot.effective_color, scene->material.diffuse);
    scene->lightdot.diffuse = multiply_scale(scene->lightdot.temp, scene->lightdot.light_dot_normal);
    free (scene->lightdot.temp);
    }
//    printf("halfway there the lightv is %f %f %f %f\n", scene->lightdot.lightv[0], scene->lightdot.lightv[1], scene->lightdot.lightv[2], scene->lightdot.lightv[3]);
    scene->lightdot.reflectv = reflect(negate_vector(scene->lightdot.lightv), normalv);
    scene->lightdot.reflect_dot_eye = dot_product(scene->lightdot.reflectv, eyev);
    if (scene->lightdot.reflect_dot_eye <= 0)
        scene->lightdot.specular = fill_color(0);
    else 
    {
    scene->lightdot.factor = pow(scene->lightdot.reflect_dot_eye, scene->material.shininess);
    scene->lightdot.temp = multiply_scale(scene->light.color, scene->material.specular);
    scene->lightdot.specular = multiply_scale(scene->lightdot.temp, scene->lightdot.factor);
    }
    scene->lightdot.result[0] = scene->lightdot.ambient[0] + scene->lightdot.diffuse[0] + scene->lightdot.specular[0];
    scene->lightdot.result[1] = scene->lightdot.ambient[1] + scene->lightdot.diffuse[1] + scene->lightdot.specular[1];
    scene->lightdot.result[2] = scene->lightdot.ambient[2] + scene->lightdot.diffuse[2] + scene->lightdot.specular[2];
    free_lightutils(&scene->lightdot);
    return(scene->lightdot.result);
}
/*
t_light	*point_light(float *pos, float *intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = pos;
	light->color = conv_color_for(intensity);
	return (light);
}

float	*lighting(t_material	*m, t_light *l, float *point, t_vectors v)
{
	t_lighting	lighting;
	
	lighting.eff_color = 
}
*/